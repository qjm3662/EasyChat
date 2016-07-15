#ifndef CRITEM_H
#define CRITEM_H

#include <QWidget>
#include "cr.h"

namespace Ui {
    class CRItem;
}

class CRItem : public QWidget
{
    Q_OBJECT

public:
    explicit CRItem(CR cr, QWidget *parent = 0);
    ~CRItem();
    void paintEvent(QPaintEvent *e);

private:
    Ui::CRItem *ui;
};

#endif // CRITEM_H
