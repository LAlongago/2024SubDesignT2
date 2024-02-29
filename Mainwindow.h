#pragma once

#include <QtWidgets/QMainWindow>
#include <QMainWindow>
#include <QFileDialog>
#include <QTextBrowser>
#include <QLabel>
#include "KeywordStatistics.h"
#include "qstring.h"
#include "ui_Mainwindow.h"

class Mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    Mainwindow(QWidget *parent = nullptr);
    ~Mainwindow();

private:
    Ui::MainwindowClass ui;
    HashTable hashTable;
    BinarySearch binarySearch;
    QString currentFilePath = "test.c"; // 指向待查找文件路径
    void updateCodePreviewer(const QString& filePath); // 更新代码预览器内容
    void updateResultsViewer(); // 更新结果展示器内容

private slots:
    void on_fileChoose_clicked();
    void on_startSearch_clicked();
};
