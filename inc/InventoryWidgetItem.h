// Copyright (c) RealCoolEngineer. 2024. All rights reserved.
// Author: beiklive
// Date: 2024-04-26
#ifndef INC_INVENTORYWIDGETITEM_H_
#define INC_INVENTORYWIDGETITEM_H_
#include <QWidget>

namespace Ui
{
    class WidgetItem;
} // namespace Ui

class InventoryWidgetItem : public QWidget
{

    Q_OBJECT

public:
    explicit InventoryWidgetItem(QWidget *parent = nullptr);
    ~InventoryWidgetItem();

    void init(int width, int height, int x, int y, QString name, int count);
    void init(QSize size, QPoint pos, QString name, int count);

private:
    //   void paintEvent(QPaintEvent* event) override;

private:
    Ui::WidgetItem *ui;
};

#endif // INC_INVENTORYWIDGETITEM_H_
