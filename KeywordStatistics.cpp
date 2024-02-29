#include "KeywordStatistics.h"
#include <QRegularExpression>

const QVector<QString> KeywordStatistics::keywords = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
    "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return",
    "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned",
    "void", "volatile", "while", "inline", "restrict", "_Bool", "_Complex", "_Imaginary",
    "_Alignas", "_Alignof", "_Atomic", "_Static_assert"
};

HashTable::HashTable() {
    table.resize(41); // 根据哈希函数的模数
}

HashTable::~HashTable() {}

int HashTable::hash(const QString& key) {
    int firstLetter = key[0].unicode() - 'a';
    int lastLetter = key[key.length() - 1].unicode() - 'a';
    return (firstLetter * 100 + lastLetter) % 41;
}

void HashTable::insert(const QString& key) {
    int index = hash(key);
    while (!table[index].key.isEmpty() && table[index].key != key) {
        index = (index + 1) % 41;
    }
    if (table[index].key.isEmpty()) {
        table[index] = HashNode(key, 1);
    }
    else {
        table[index].count++;
    }
}

void HashTable::statistic(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QRegularExpression wordRegex("\\b[A-Za-z_]+\\b");
    while (!in.atEnd()) {
        QString line = in.readLine();
        QRegularExpressionMatchIterator it = wordRegex.globalMatch(line);
        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            QString word = match.captured(0);
            if (keywords.contains(word)) {
                insert(word);
            }
        }
    }

    // 输出统计结果
    for (const auto& node : table) {
        if (!node.key.isEmpty()) { // 非空槽位
            qDebug() << node.key << ":" << node.count;
        }
    }
}

BinarySearch::BinarySearch() {
    sortedKeywords = keywords;
    std::sort(sortedKeywords.begin(), sortedKeywords.end());
}

BinarySearch::~BinarySearch() {}

void BinarySearch::statistic(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QRegularExpression wordRegex("\\b[A-Za-z_]+\\b");

    // 初始化关键字计数器
    for (const auto& keyword : keywords) {
        keywordCounts[keyword] = 0;
    }

    while (!in.atEnd()) {
        QString line = in.readLine();
        QRegularExpressionMatchIterator it = wordRegex.globalMatch(line);
        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            QString word = match.captured(0);
            if (keywords.contains(word)) {
                // 使用二分查找确定是否为关键字并计数
                if (binarySearch(word) != -1) {
                    keywordCounts[word]++;
                }
            }
        }
    }

    // 输出统计结果
    for (const auto& keyword : keywords) {
        if (keywordCounts[keyword] > 0) {
            qDebug() << keyword << ":" << keywordCounts[keyword];
        }
    }
}

// BinarySearch类中的binarySearch方法
int BinarySearch::binarySearch(const QString& key) {
    int low = 0;
    int high = sortedKeywords.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (sortedKeywords[mid] < key) {
            low = mid + 1;
        }
        else if (sortedKeywords[mid] > key) {
            high = mid - 1;
        }
        else {
            return mid; // 找到关键字
        }
    }
    return -1; // 未找到关键字
}
