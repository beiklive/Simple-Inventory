#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QPushButton>
#include "MyTableWidget.hpp"

#include "CSVReader.hpp"
#include "ItemManager.h"
#include "InventoryWidget.h"
#include "InventorySystem.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void ReadAllItems();
    void StatusBarMessage(QString message);


    bool isInGround(QPoint pos);
    void CreateDropItem(QDropEvent* event);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void dropEvent(QDropEvent* event) ;
    void dragEnterEvent(QDragEnterEvent* event) ;

public:
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);
    void on_tableWidget_itemPressed(QTableWidgetItem *item);
    void on_groundItem_clicked();
    void on_pushButton_clicked();
    void on_collect_btn_clicked();
private:
    Ui::MainWindow *ui;
    ItemManager *itemManager;
    CSVReader *csvReader;
    InventorySystem *inventorySystem;

    bool isMousePressed;

    QPushButton *widgetUnderMouse{nullptr};
    std::vector<QPushButton*> widgetsInGroundList;
    int listcount{0};
};

#endif // MAINWINDOW_H
