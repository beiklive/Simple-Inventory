#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QUrl>
// 定时器头文件
#include <QTimer>
#include <QMessageBox>
#include "Common.hpp"
#include "InventoryWidgetItem.h"
MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_Timer = new QTimer(this);
    setAcceptDrops(true);
    ui->setupUi(this);
    ReadAllItems();

    connect(ui->tableWidget, &QTableWidget::itemDoubleClicked, this, &MainWindow::on_tableWidget_itemDoubleClicked);
    connect(ui->tableWidget, &QTableWidget::itemPressed, this, &MainWindow::on_tableWidget_itemPressed);


    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->collect_btn, &QPushButton::clicked, this, &MainWindow::on_collect_btn_clicked);
    
    inventorySystem = new InventorySystem(8, 500);
    ui->widget->initWidget(8);
    ui->pushButton->setEnabled(false);

    this->hide();
    // 定时器 等待窗口大小初始化完成
    connect(m_Timer, &QTimer::timeout, this, &MainWindow::onTimeOut);
    m_Timer->start(50);
}

void MainWindow:: resizeEvent(QResizeEvent* event)
{

    bagInitPos.setX(ui->groupBox->width() + 24);
    bagInitPos.setY(ui->groupBox_4->height() + 105);
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
        // widgetUnderMouse->move(event->pos().x() - widgetUnderMouse->width() / 2, event->pos().y() - widgetUnderMouse->height() / 2);
        widgetUnderMouse->show();
        connect(widgetUnderMouse, &QPushButton::clicked, this, &MainWindow::on_groundItem_clicked);

        widgetsInGroundList.emplace_back(widgetUnderMouse);
        listcount++;

        widgetUnderMouse = nullptr;

    }
}


void MainWindow::on_groundItem_clicked()
{
//     QPushButton* button = qobject_cast<QPushButton*>(sender());
//     if (button) {
//         QString buttonName = button->text();
//         StatusBarMessage(QStringLiteral("Clicked: ") + buttonName);

//         // 使被点击的按钮浮动到父对象层级
//         if(button->parent() == ui->ground)
//         {
//             if(!inventorySystem->is_bag_full())
//             {
//                 int x = button->x();
//                 int y = button->y();
//                 button->setParent(this);
//                 button->move(x + ui->groupBox->width() + 12, y  + 27);
//                 button->show();

//                 int index = inventorySystem->add_item_to_bag(itemManager->getItem(buttonName.toStdString()));
//                 QPoint target_pos = ui->widget->calWidgetItemPos(index);
//                 QPoint global_target_pos = target_pos + bagInitPos;// + QPoint(ui->widget->getWidgetItemSize().width()/2, ui->widget->getWidgetItemSize().height()/2);
//                 positionAnimation = new QPropertyAnimation(button, "pos", this);
//                 positionAnimation->setDuration(500);  // 设置动画持续时间为500毫秒
//                 positionAnimation->setEasingCurve(QEasingCurve::InOutBack);
//                 positionAnimation->setEndValue(global_target_pos);
//                 connect(positionAnimation, &QPropertyAnimation::finished, this, [=]() {
//                     button->hide();
//                     Item it = inventorySystem->get_item_in_bag_by_pos(index);
//                     ui->widget->resetWidgetItem(index, it);
//                     button->hide();
//                     delete button;
//                     button = nullptr;
//                     delete positionAnimation;
//                     positionAnimation = nullptr;
//                 }
//                     );
//                 positionAnimation->start();
//             }
//         }
//     }
}

void MainWindow:: on_pushButton_clicked()
{
    ui->widget->addWidgetItem();
}

void MainWindow:: on_collect_btn_clicked()
{
    int index_count = 0;
    for (auto button : widgetsInGroundList)
    {
        if(!inventorySystem->is_bag_full() && button->text() != "NULL")
        {
                int x = button->x();
                int y = button->y();
                button->setParent(this);
                button->move(x + ui->groupBox->width() + 12, y  + 27);
                button->show();
                QString buttonName = button->text();
                int index = inventorySystem->add_item_to_bag(itemManager->getItem(buttonName.toStdString()));
                QPoint target_pos = ui->widget->calWidgetItemPos(index);
                QPoint global_target_pos = target_pos + bagInitPos;// + QPoint(ui->widget->getWidgetItemSize().width()/2, ui->widget->getWidgetItemSize().height()/2);
                positionAnimation = new QPropertyAnimation(button, "pos", this);
                positionAnimation->setDuration(500);  // 设置动画持续时间为500毫秒
                positionAnimation->setEasingCurve(QEasingCurve::InOutBack);
                positionAnimation->setEndValue(global_target_pos);
                connect(positionAnimation, &QPropertyAnimation::finished, this, [this, index, index_count]() {
                    
                    Item it = inventorySystem->get_item_in_bag_by_pos(index);
                    ui->widget->resetWidgetItem(index, it);
                    widgetsInGroundList[index_count]->hide();
                    widgetsInGroundList[index_count]->setText("NULL");
                    delete positionAnimation;
                    positionAnimation = nullptr;
                    listcount--;
                    if(listcount== 0)
                    {
                        widgetsInGroundList.clear();    
                    }
                }
                    );
                positionAnimation->start();
        }
        index_count++;
    }


}

void MainWindow::onTimeOut() {
    m_Timer->stop();
    bagInitPos.setX(ui->groupBox->width() + 24);
    bagInitPos.setY(ui->groupBox_4->height() + 105);
    this->resize(1200, 800);
    this->show();
}
