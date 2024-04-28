#include "InventoryWidgetItem.h"
#include "ui_WidgetItem.h"

InventoryWidgetItem::InventoryWidgetItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetItem)
{
    ui->setupUi(this);
}

InventoryWidgetItem::~InventoryWidgetItem()
{
    delete ui;
}

void InventoryWidgetItem:: SetSize(QSize size)
{
    this->resize(size);
}

void InventoryWidgetItem:: SetPos(QPoint pos)
{
    this->move(pos);
}

void InventoryWidgetItem:: init(QSize size, QPoint pos)
{
    SetSize(size);
    SetPos(pos);
}

void InventoryWidgetItem:: init(QSize size, QPoint pos, Item item)
{
    _item = item;
    SetItem();
    init(size, pos);
}

void InventoryWidgetItem:: init(int width, int height, int x, int y, Item item)
{
    init(QSize(width, height), QPoint(x, y), item);
}

void InventoryWidgetItem::SetItem()
{
    ui->name_label->setText(QString::fromStdString(_item.name));
    ui->count_label->setText(QString::number(_item.quantity));
}

void InventoryWidgetItem::SetItem(Item item)
{
    ui->name_label->setText(QString::fromStdString(item.name));
    ui->count_label->setText(QString::number(item.quantity));
}

void InventoryWidgetItem:: SetWidgetItemName(QString name)
{
    ui->groupBox->setTitle(name);
}

void InventoryWidgetItem:: SetWidgetItemID(int id)
{
    _id = id;
}

int InventoryWidgetItem:: GetWidgetItemID()
{
    return _id;

}
