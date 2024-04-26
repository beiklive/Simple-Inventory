// Copyright (c) RealCoolEngineer. 2024. All rights reserved.
// Author: beiklive
// Date: 2024-04-26
#ifndef INC_INVENTORYWIDGET_H_
#define INC_INVENTORYWIDGET_H_
#include <QWidget>


class InventoryWidget : public QWidget {
  Q_OBJECT

 public:
  explicit InventoryWidget(QWidget* parent = nullptr);
  ~InventoryWidget() override;

 private:
  void initUI();



};






#endif  // INC_INVENTORYWIDGET_H_
