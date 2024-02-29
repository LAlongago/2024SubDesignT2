#include "Mainwindow.h"

Mainwindow::Mainwindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

Mainwindow::~Mainwindow()
{}

void Mainwindow::on_fileChoose_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("C Files (*.c)"));
    if (!fileName.isEmpty()) {
        currentFilePath = fileName;
        ui.showFileDir->setText(fileName);
        updateCodePreviewer(fileName);
    }
}

void Mainwindow::on_startSearch_clicked()
{
    if (!currentFilePath.isEmpty()) {
        hashTable.statistic(currentFilePath);
        binarySearch.statistic(currentFilePath);
        updateResultsViewer();
    }
}

void Mainwindow::updateCodePreviewer(const QString& filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) 
    {
        QTextStream in(&file);
        ui.codePreviewer->setText(in.readAll());
    }
}

void Mainwindow::updateResultsViewer()
{
    // 获取HashTable的结果
    auto hashResults = hashTable.getResults();
    int hashSearchCount = hashTable.getSearchCount();
    qint64 hashElapsedTime = hashTable.getElapsedTime();

    QString hashResultsStr = "HashTable Results:\n";
    hashResultsStr += "Search Count: " + QString::number(hashSearchCount) + "\n";
    hashResultsStr += "Elapsed Time: " + QString::number(hashElapsedTime) + " ms\n";
    hashResultsStr += "Keywords and Frequencies:\n";
    for (auto it = hashResults.constBegin(); it != hashResults.constEnd(); ++it)
    {
        hashResultsStr += it.key() + ": " + QString::number(it.value()) + "\n";
    }

    // 获取BinarySearch的结果
    auto binaryResults = binarySearch.getResults();
    int binarySearchCount = binarySearch.getSearchCount();
    qint64 binaryElapsedTime = binarySearch.getElapsedTime();

    QString binaryResultsStr = "BinarySearch Results:\n";
    binaryResultsStr += "Search Count: " + QString::number(binarySearchCount) + "\n";
    binaryResultsStr += "Elapsed Time: " + QString::number(binaryElapsedTime) + " ms\n";
    binaryResultsStr += "Keywords and Frequencies:\n";
    for (auto it = binaryResults.constBegin(); it != binaryResults.constEnd(); ++it) 
    {
        if (it.value() == 0) continue;
        binaryResultsStr += it.key() + ": " + QString::number(it.value()) + "\n";
    }

    // 更新UI组件
    ui.hashResultViewer->setText(hashResultsStr);
    ui.binaryResultViewer->setText(binaryResultsStr);
}
