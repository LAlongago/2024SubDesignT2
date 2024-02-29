#pragma once

#ifndef KEYWORDSTATISTICS_H
#define KEYWORDSTATISTICS_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QElapsedTimer>
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
    QMap<QString, int> getResults() const;
    int getSearchCount() const;
    qint64 getElapsedTime() const;

private:
    struct HashNode {
        QString key;
        int count;
        HashNode() : count(0) {}
        HashNode(QString k, int c) : key(k), count(c) {}
    };

    QVector<HashNode> table;
    int searchCount; // 新增查找次数计数器
    QElapsedTimer timer; // 新增计时器
    QMap<QString, int> results; // 关键字和频次的映射
    int hash(const QString& key);
    void insert(const QString& key);
};

// 二分查找类
class BinarySearch : public KeywordStatistics {
public:
    BinarySearch();
    ~BinarySearch();
    void statistic(const QString& filename) override;
    QMap<QString, int> getResults() const;
    int getSearchCount() const;
    qint64 getElapsedTime() const;

private:
    QVector<QString> sortedKeywords;
    int searchCount; // 新增查找次数计数器
    QElapsedTimer timer; // 新增计时器
    QMap<QString, int> keywordCounts; // 关键字和频次的映射
    int binarySearch(const QString& key);
};

#endif // KEYWORDSTATISTICS_H
