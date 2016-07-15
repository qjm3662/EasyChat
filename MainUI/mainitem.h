#ifndef MAINITEM_H
#define MAINITEM_H

#include <QWidget>
#include "user.h"

namespace Ui {
    class MainItem;
}

class MainItem : public QWidget
{
    Q_OBJECT

public:
    explicit MainItem(User user, QWidget *parent = 0);
    ~MainItem();

private:
    Ui::MainItem *ui;
};

#endif // MAINITEM_H
