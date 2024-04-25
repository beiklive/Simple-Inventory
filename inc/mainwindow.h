#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include "MyTableWidget.hpp"

#include "CSVReader.hpp"
#include "ItemManager.h"

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

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void dropEvent(QDropEvent* event) ;
    void dragEnterEvent(QDragEnterEvent* event) ;

public:
    void on_tableWidget_itemDoubleClicked(QTableWidgetItem *item);
    void on_tableWidget_itemPressed(QTableWidgetItem *item);


private:
    Ui::MainWindow *ui;
    ItemManager *itemManager;
    CSVReader *csvReader;

    bool isMousePressed;

    QWidget *widgetUnderMouse{nullptr};
};

#endif // MAINWINDOW_H
