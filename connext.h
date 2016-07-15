#ifndef CONNEXT_H
#define CONNEXT_H

#include <QWidget>
#include "client/client.h"
#include "client/clientstic.h"

namespace Ui {
    class connext;
}

class connext : public QWidget
{
    Q_OBJECT

public:
    explicit connext(QWidget *parent = 0);
    ~connext();
signals:
    void connected();

private slots:
    void on_pushButton_clicked();
    void connectedSlot();

private:
    Ui::connext *ui;
};

#endif // CONNEXT_H
