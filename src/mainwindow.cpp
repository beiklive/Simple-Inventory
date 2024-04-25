#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QUrl>
#include "Common.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ReadAllItems();
}



void MainWindow::ReadAllItems()
{
    std::string projectRootDir = beiklive::filesystem::getProjectRootDirectory();
    std::string path = "/res/items.csv";

    // 读取 CSV 文件
    CSVReader reader(projectRootDir + path);
    vector<Item> items = reader.readCSV();

    // 输出读取的物品信息
    cout << "读取到的物品信息：" << endl;
    ui->tableWidget->setColumnCount(ITEM_TYPES_COUNT);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "ID" << "名称" << "价值" << "重量" << "数量" << "种类");
    for (const auto& item : items) {
        // qDebug() << "ID: " << QString::number(item.id) << ", 名称: " <<QString::fromStdString(item.name) << ", 价值: " << QString::number(item.value) << ", 重量: " << QString::number(item.weight) << ", 数量: " << QString::number(item.quantity);
        // cout << "ID: " << item.id << ", 名称: " << item.name << ", 价值: " << item.value << ", 重量: " << item.weight << ", 数量: " << item.quantity << endl;
        // 显示到界面上
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(QString::number(item.id)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(QString::fromStdString(item.name)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(QString::number(item.value)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(QString::number(item.weight)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, new QTableWidgetItem(QString::number(item.quantity)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 5, new QTableWidgetItem(QString::fromStdString(item.type)));
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}
