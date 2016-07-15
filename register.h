#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include "client/client.h"
#include "client/clientstic.h"


namespace Ui {
    class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();
    void paintEvent(QPaintEvent *e);


private slots:
    void on_btn_to_login_clicked();

    void on_btn_cancel_2_clicked();

    void on_btn_register_clicked();

    void registerSuccessSlot();

private:
    Ui::Register *ui;
    Client * client;
};

#endif // REGISTER_H
