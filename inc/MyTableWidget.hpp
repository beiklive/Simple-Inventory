// Copyright (c) RealCoolEngineer. 2024. All rights reserved.
// Author: beiklive
// Date: 2024-04-25
#ifndef INC_MYTABLEWIGET_HPP_
#define INC_MYTABLEWIGET_HPP_

#include <QApplication>
#include <QTableWidget>
#include <QMimeData>
#include <QDrag>
#include <QMouseEvent>
class MyTableWidget : public QTableWidget {
public:
    MyTableWidget(QWidget* parent = nullptr) : QTableWidget(parent) {
        setSelectionMode(QAbstractItemView::SingleSelection);
        setDragEnabled(true);
        setDragDropMode(QAbstractItemView::DragOnly);
    }

protected:

    void dragMoveEvent(QDragMoveEvent *event) {
    }

    void mousePressEvent(QMouseEvent *event)  {
        QTableWidget::mousePressEvent(event);
        if (event->button() == Qt::LeftButton) {
            QModelIndex index = indexAt(event->pos());
            if (index.isValid()) {


                QDrag* drag = new QDrag(this);
                QMimeData* mimeData = new QMimeData;
                mimeData->setText(item(index.row(), 1)->text());
                drag->setMimeData(mimeData);
                drag->exec(Qt::CopyAction);


            }
        }
    }


private:

};

#endif  // INC_MYTABLEWIGET_HPP_