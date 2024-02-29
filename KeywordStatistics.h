#pragma once

#ifndef KEYWORDSTATISTICS_H
#define KEYWORDSTATISTICS_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <algorithm>

class KeywordStatistics {
public:
    virtual ~KeywordStatistics() {}
    virtual void statistic(const QString& filename) = 0;
protected:
    static const QVector<QString> keywords;
};

// 哈希表类
class HashTable : public KeywordStatistics {
public:
    HashTable();
    ~HashTable();
    void statistic(const QString& filename) override;

private:
    struct HashNode {
        QString key;
        int count;
        HashNode() : count(0) {}
        HashNode(QString k, int c) : key(k), count(c) {}
    };

    QVector<HashNode> table;
    int hash(const QString& key);
    void insert(const QString& key);
};

// 二分查找类
class BinarySearch : public KeywordStatistics {
public:
    BinarySearch();
    ~BinarySearch();
    void statistic(const QString& filename) override;

private:
    QVector<QString> sortedKeywords;
    QMap<QString, int> keywordCounts;
    int binarySearch(const QString& key);
};

#endif // KEYWORDSTATISTICS_H
