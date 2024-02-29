#include "Mainwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Mainwindow w;
    w.show();
    return a.exec();
}

//#include <QCoreApplication>
//#include <QDebug>
//#include "KeywordStatistics.h" 
//
//int main(int argc, char* argv[]) 
// {
//    QCoreApplication a(argc, argv);
//
//    QString filename = "test.c"; // 指向测试文件路径
//
//    qDebug() << "Testing HashTable:";
//    HashTable hashTable;
//    hashTable.statistic(filename);
//
//    qDebug() << "\nTesting BinarySearch:";
//    BinarySearch binarySearch;
//    binarySearch.statistic(filename);
//
//    return a.exec();
//}