#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QUrl>
#include "Common.hpp"
#include "InventoryWidgetItem.h"
MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setAcceptDrops(true);
    ui->setupUi(this);
    ReadAllItems();

    connect(ui->tableWidget, &QTableWidget::itemDoubleClicked, this, &MainWindow::on_tableWidget_itemDoubleClicked);
    connect(ui->tableWidget, &QTableWidget::itemPressed, this, &MainWindow::on_tableWidget_itemPressed);


    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);

    ui->widget->initWidget(8);

}



void MainWindow::ReadAllItems()
{
    std::string projectRootDir = beiklive::filesystem::getProjectRootDirectory();
    std::string path = "/res/items.csv";

    // 读取 CSV 文件
    csvReader = new CSVReader(projectRootDir + path);
    vector<Item> items = csvReader->readCSV();
    // 构造物品管理器
    itemManager = new ItemManager(items);

    // 输出读取的物品信息
    ui->tableWidget->setColumnCount(ITEM_TYPES_COUNT);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "ID" << "NAME" << ("VALUE") << ("WEIGHT") << ("NUMBER") << ("TYPE"));
    for (const auto& item : items) {
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


// void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);
void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem* item)
{
    int row = item->row();
    int id = ui->tableWidget->item(row, 0)->text().toInt();

    StatusBarMessage(QStringLiteral("DoubleClicked: ") + QString::fromStdString(itemManager->getItem(id).name));
}


void MainWindow::on_tableWidget_itemPressed(QTableWidgetItem* item)
{
    int row = item->row();
    int id = ui->tableWidget->item(row, 0)->text().toInt();

    StatusBarMessage(QStringLiteral("Pressed: ") + QString::fromStdString(itemManager->getItem(id).name));

}

void MainWindow::StatusBarMessage(QString message)
{
    ui->statusBar->showMessage(message);
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{

}


void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{

}


void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    int x = event->x();
    int y = event->y();
    StatusBarMessage(QStringLiteral("Mouse Move: ") + QString::number(x) + ", " + QString::number(y));
}


void MainWindow::dropEvent(QDropEvent* event) {
    if (event->mimeData()->hasText()) {
        StatusBarMessage("Dropped: " + event->mimeData()->text());
        if (isInGround(event->pos()))
        {
            CreateDropItem(event);
            // ui->name_label->setText(event->mimeData()->text());
        }
    }
    event->acceptProposedAction();
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event) {
    event->acceptProposedAction();
}

bool MainWindow::isInGround(QPoint pos)
{
    int GroundPosX = ui->groupBox->width() + 2;
    int GroundPosY = 16;
    int GroundWidth = ui->ground->width();
    int GroundHeight = ui->ground->height();


    if (pos.x() >= GroundPosX && pos.x() <= (GroundPosX + GroundWidth) && pos.y() >= GroundPosY && pos.y() <= (GroundPosY + GroundHeight)) {
        return true;
    }
    return false;
}


void MainWindow::CreateDropItem(QDropEvent* event)
{
    // if (event->mimeData()->hasText()) 
    {
        widgetUnderMouse = new QPushButton(ui->ground);
        widgetUnderMouse->setAttribute(Qt::WA_DeleteOnClose);
        widgetUnderMouse->setText(event->mimeData()->text());
        widgetUnderMouse->resize(100, 30);
        widgetUnderMouse->move(event->pos().x() - ui->groupBox->width() - 2 - 11 - widgetUnderMouse->width() / 2, event->pos().y() - 16 - 11 - widgetUnderMouse->height() / 2);
        widgetUnderMouse->show();
        connect(widgetUnderMouse, &QPushButton::clicked, this, &MainWindow::on_groundItem_clicked);

        widgetsInGroundList.emplace_back(widgetUnderMouse);
        widgetUnderMouse = nullptr;

    }
}


void MainWindow::on_groundItem_clicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString buttonName = button->text();
        StatusBarMessage(QStringLiteral("Clicked: ") + buttonName);
    }
}

void MainWindow:: on_pushButton_clicked()
{
    ui->widget->addWidgetItem();
}