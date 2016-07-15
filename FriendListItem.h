#ifndef FRIENDLISTITEM_H
#define FRIENDLISTITEM_H

#include <QWidget>
#include <cr.h>
#include <QFont>
#include <QColor>

namespace Ui {
    class FriendListItem;
}

class FriendListItem : public QWidget
{
    Q_OBJECT

public:
    explicit FriendListItem(CR& cr, QFont font, QColor color, QWidget *parent = 0);
    ~FriendListItem();

private:
    Ui::FriendListItem *ui;
};

#endif // FRIENDLISTITEM_H
