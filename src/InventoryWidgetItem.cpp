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

