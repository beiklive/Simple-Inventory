#include "InventoryWidget.h"


InventoryWidget::InventoryWidget(QWidget *parent) : QWidget(parent)
{
}

InventoryWidget::~InventoryWidget()
{}

void InventoryWidget:: initWidget(int count)
{
    _widgetItemNumber = count;
    for(int i = 0; i < _widgetItemNumber; i++)
    {
        createWidgetItems(i, QString::number(i + 1), QSize(_basicItemWidth, _basicItemHeight), calWidgetItemPos(i), ItemManager::createEmptyItem());
    }
    showAllWidgetItems(true);
}

void InventoryWidget::addWidgetItem()
{
    int id = _widgetItems.size();
    createWidgetItems(id, QString::number(id + 1), QSize(_basicItemWidth, _basicItemHeight), calWidgetItemPos(id), ItemManager::createEmptyItem());
    showAllWidgetItems(true);
}


// void resizeEvent(QResizeEvent* event) override;
void InventoryWidget::resizeEvent(QResizeEvent* event)
{
    int width = event->size().width();
    int height = event->size().height();
    int itemWidth = _basicItemWidth;
    int itemHeight = _basicItemHeight;
    if(!_widgetItems.empty())
    {
        for (auto item : _widgetItems)
        {
            if(isItemResize){
                item->SetSize(QSize(itemWidth, itemHeight));
            }
            item->SetPos(calWidgetItemPos(item->GetWidgetItemID()));
        }

    }
}

QPoint InventoryWidget:: calWidgetItemPos(int id)
{
    int width = this->width();
    int height = this->height();
    int itemWidth = _basicItemWidth;
    int itemHeight = _basicItemHeight;

    int itemInOneRow = width / (itemWidth + _basicItemSpace);

    if(itemInOneRow == 0)
    {
        itemInOneRow = 1;
    }
    int basicy = id / itemInOneRow;
    int basicx = id % itemInOneRow;

    int x = basicx * (itemWidth + _basicItemSpace);
    int y = basicy * (itemHeight + _basicItemSpace);

    return QPoint(x, y);
}


void InventoryWidget:: setWidgetItemSize(QSize size)
{
    for (auto item : _widgetItems)
    {
        item->SetSize(size);
    }
}

void InventoryWidget:: setWidgetItemPos(QPoint pos)
{
    for (auto item : _widgetItems)
    {
        item->SetPos(pos);
    }
}


void InventoryWidget:: createWidgetItems(int id, QString WidgetName, QSize WidgetSize, QPoint WidgetPos, Item item)
{
    InventoryWidgetItem *itemWidget = new InventoryWidgetItem(this);
    itemWidget->init(WidgetSize, WidgetPos, item);
    itemWidget->SetWidgetItemID(id);
    itemWidget->SetWidgetItemName(WidgetName);
    _widgetItems.emplace_back(itemWidget);
}

void InventoryWidget:: showAllWidgetItems(bool show)
{
    for (auto item : _widgetItems)
    {
        if (show)
        {
            item->show();
        }else
        {
            item->hide();
        }
        
    }
}