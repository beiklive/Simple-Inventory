#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QUrl>
#include "Common.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setAcceptDrops(true);
    ui->setupUi(this);
    ReadAllItems();

    connect(ui->tableWidget, &QTableWidget::itemDoubleClicked, this, &MainWindow::on_tableWidget_itemDoubleClicked);
    connect(ui->tableWidget, &QTableWidget::itemPressed, this, &MainWindow::on_tableWidget_itemPressed);


    int GroundPosX = ui->ground->x();
    int GroundPosY = ui->ground->y();

    ui->info_label->setText(QStringLiteral("Ground����: ") + QString::number(GroundPosX) + ", " + QString::number(GroundPosY));


}



void MainWindow::ReadAllItems()
{
    std::string projectRootDir = beiklive::filesystem::getProjectRootDirectory();
    std::string path = "/res/items.csv";

    // ��ȡ CSV �ļ�
    csvReader = new CSVReader(projectRootDir + path);
    vector<Item> items = csvReader->readCSV();
    // ������Ʒ������
    itemManager = new ItemManager(items);
    
    // �����ȡ����Ʒ��Ϣ
    cout << "��ȡ������Ʒ��Ϣ:\t" << endl;
    ui->tableWidget->setColumnCount(ITEM_TYPES_COUNT);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "ID" << QStringLiteral("����") << QStringLiteral("��ֵ") << QStringLiteral("����") << QStringLiteral("����") << QStringLiteral("����"));
    for (const auto& item : items) {
        qDebug() << "ID: " << QString::number(item.id) << ", ����: " <<QString::fromStdString(item.name) << ", ��ֵ: " << QString::number(item.value) << ", ����: " << QString::number(item.weight) << ", ����: " << QString::number(item.quantity);
        cout << "ID: " << item.id << ", ����: " << item.name << ", ��ֵ: " << item.value << ", ����: " << item.weight << ", ����: " << item.quantity << endl;
        // ��ʾ��������
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
void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem *item)
{
    int row = item->row();
    int id = ui->tableWidget->item(row, 0)->text().toInt();

    StatusBarMessage(QStringLiteral("��ǰѡ��: ") + QString::fromStdString(itemManager->getItem(id).name));
}


void MainWindow::on_tableWidget_itemPressed(QTableWidgetItem *item)
{
    int row = item->row();
    int id = ui->tableWidget->item(row, 0)->text().toInt();

    StatusBarMessage(QStringLiteral("��ǰ����: ") + QString::fromStdString(itemManager->getItem(id).name));

}

void MainWindow::StatusBarMessage(QString message)
{
    ui->statusBar->showMessage(message);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // isMousePressed = true;
    // int x = event->x();
    // int y = event->y();
    // widgetUnderMouse = new QWidget(this);
    // widgetUnderMouse->setAttribute(Qt::WA_DeleteOnClose);
    // widgetUnderMouse->setStyleSheet("background-color: yellow;");
    // // widgetUnderMouse->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    // widgetUnderMouse->setCursor(Qt::CrossCursor);
    // widgetUnderMouse->resize(50, 20);
    // widgetUnderMouse->move(x+5, y+5);
    
    // widgetUnderMouse->show();
}


void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    // isMousePressed = false;

    // if(widgetUnderMouse!= nullptr)
    // {
    //     widgetUnderMouse->close();
    //     delete widgetUnderMouse;
    //     widgetUnderMouse = nullptr;
    // }
}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    widgetUnderMouse = ui->tableWidget->getWidgetUnderMouse();
    // if (isMousePressed) 
    // {
        int x = event->x();
        int y = event->y();
    //     int row = ui->tableWidget->rowAt(y);
    //     int column = ui->tableWidget->columnAt(x);
        StatusBarMessage(QStringLiteral("��ǰ����: ") + QString::number(x) + ", " + QString::number(y));
    
        widgetUnderMouse->move(x, y);

    // }
}


void MainWindow::dropEvent(QDropEvent* event)  {
    if (event->mimeData()->hasText()) {
        // qDebug() << "Dropped: " << event->mimeData()->text();
        StatusBarMessage("Dropped: " + event->mimeData()->text());
        // �����ﴦ���Ϸŵ�����
        if (isInGround(event->pos()))
        {
            ui->name_label->setText(event->mimeData()->text());
        }
        
    }
    event->acceptProposedAction();
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)  {
    event->acceptProposedAction();
}

bool MainWindow::isInGround(QPoint pos)
{
    int GroundPosX = ui->ground->x();
    int GroundPosY = ui->ground->y();
    int GroundWidth = ui->ground->width();
    int GroundHeight = ui->ground->height();


    if (pos.x() >= GroundPosX && pos.x() <= (GroundPosX + GroundWidth) && pos.y() >= GroundPosY && pos.y() <= (GroundPosY + GroundHeight)) {
        return true;
    }
    return false;
}