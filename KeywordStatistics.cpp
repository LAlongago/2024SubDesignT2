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
    table.resize(41);
    searchCount = 0;
}

HashTable::~HashTable() {}

QMap<QString, int> HashTable::getResults() const { return results; }
int HashTable::getSearchCount() const { return searchCount; }
qint64 HashTable::getElapsedTime() const { return timer.elapsed(); }

int HashTable::hash(const QString& key) {
    int firstLetter = key[0].unicode() - 'a';
    int lastLetter = key[key.length() - 1].unicode() - 'a';
    return (firstLetter * 100 + lastLetter) % 41;
}

void HashTable::insert(const QString& key) {
    int index = hash(key);
    while (!table[index].key.isEmpty() && table[index].key != key) {
        index = (index + 1) % table.size();
        searchCount++; // 增加查找次数
    }
    searchCount++; // 对于最终的查找操作也增加计数
    if (table[index].key.isEmpty()) {
        table[index].key = key;
        table[index].count = 1; // 初始化计数为1
        results[key] = 1; // 更新结果映射
    }
    else {
        table[index].count++; // 已存在的关键字计数增加
        results[key]++; // 更新结果映射
    }
}



void HashTable::statistic(const QString& filename) {
    timer.start(); // 计时开始
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
                searchCount++;
            }
        }
    }

    // 输出统计结果
    //for (const auto& node : table) {
    //    if (!node.key.isEmpty()) { // 非空槽位
    //        qDebug() << node.key << ":" << node.count;
    //    }
    //}
    //qDebug() << "Total search count:" << searchCount;
    //qDebug() << "Elapsed time:" << timer.elapsed() << "milliseconds";
}

BinarySearch::BinarySearch() {
    sortedKeywords = keywords;
    std::sort(sortedKeywords.begin(), sortedKeywords.end());
    searchCount = 0;
}

BinarySearch::~BinarySearch() {}

QMap<QString, int> BinarySearch::getResults() const { return keywordCounts; }
int BinarySearch::getSearchCount() const { return searchCount; }
qint64 BinarySearch::getElapsedTime() const { return timer.elapsed(); }

void BinarySearch::statistic(const QString& filename) {
    timer.start(); // 计时开始
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
    //for (const auto& keyword : keywords) {
    //    if (keywordCounts[keyword] > 0) {
    //        qDebug() << keyword << ":" << keywordCounts[keyword];
    //    }
    //}
    //qDebug() << "Total search count:" << searchCount;
    //qDebug() << "Elapsed time:" << timer.elapsed() << "milliseconds";
}

// BinarySearch类中的binarySearch方法
int BinarySearch::binarySearch(const QString& key) {
    int low = 0;
    int high = sortedKeywords.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        searchCount++; // 每次比较都增加查找次数
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
