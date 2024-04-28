// Copyright (c) RealCoolEngineer. 2024. All rights reserved.
// Author: beiklive
// Date: 2024-04-26
#ifndef INC_INVENTORYWIDGETITEM_H_
#define INC_INVENTORYWIDGETITEM_H_
#include <QWidget>
#include "ItemManager.h"

/*
    InventoryWidgetItem *item = new InventoryWidgetItem(ui->widget);
    item->init(QSize(100,100),QPoint(10,10));
    item->SetWidgetItemName("Item1");
    item->show();

    InventoryWidgetItem *item2 = new InventoryWidgetItem(ui->widget);
    item2->init(QSize(100,500),QPoint(200,10));
    item2->SetWidgetItemName("Item2");
    item2->show();
*/



namespace Ui
{
    class WidgetItem;
} // namespace Ui

class InventoryWidgetItem : public QWidget
{


public:
    explicit InventoryWidgetItem(QWidget *parent = nullptr);
    ~InventoryWidgetItem();


    void init(QSize size, QPoint pos);
    void init(QSize size, QPoint pos, Item item);
    void init(int width, int height, int x, int y, Item item);

    void SetSize(QSize size);
    void SetPos(QPoint pos);
    void SetItem();
    void SetWidgetItemName(QString name);
    void SetWidgetItemID(int id);


    int GetWidgetItemID();
private:
    //   void paintEvent(QPaintEvent* event) override;

private:
    Ui::WidgetItem *ui;
    Item _item;
    int _id;
};

#endif // INC_INVENTORYWIDGETITEM_H_
