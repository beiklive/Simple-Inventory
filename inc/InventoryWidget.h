// Copyright (c) RealCoolEngineer. 2024. All rights reserved.
// Author: beiklive
// Date: 2024-04-26
#ifndef INC_INVENTORYWIDGET_H_
#define INC_INVENTORYWIDGET_H_
#include <QWidget>
#include <vector>
#include <QResizeEvent>

#include "InventoryWidgetItem.h"

class InventoryWidget : public QWidget {
  Q_OBJECT

 public:
  explicit InventoryWidget(QWidget* parent = nullptr);
  ~InventoryWidget() override;

// Widget Functions
    void resizeEvent(QResizeEvent* event) override;
    void initWidget(int count);
    QPoint calWidgetItemPos(int id);


// WidgetItem Functions

    void createWidgetItems(int id, QString WidgetName, QSize WidgetSize, QPoint WidgetPos, Item item);
    void showAllWidgetItems(bool show);
    
    void setWidgetItemSize(QSize size);
    void setWidgetItemPos(QPoint pos);
    void addWidgetItem();
    void resetWidgetItem(int id, Item item);

//    connect(itemWidget, SIGNAL(itemClick(int)), this, SLOT(onWidgetItemClick(int)));


 signals:
    void itemClick(int id);

 public slots:
    void onWidgetItemClick(int id);



 private:
    std::vector<InventoryWidgetItem*> _widgetItems;
    int _widgetItemNumber;

    bool isItemResize{false};

    int _basicItemWidth{120};
    int _basicItemHeight{80};
    int _basicItemSpace{10};
};






#endif  // INC_INVENTORYWIDGET_H_
