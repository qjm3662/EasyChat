#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "client/client.h"
#include "client/clientstic.h"

namespace Ui {
    class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();
    void paintEvent(QPaintEvent *e);

private slots:
    void on_btn_creat_new_account_clicked();

    void on_btn_cancel_clicked();

    void on_btn_login_clicked();

    void closeLoginUISlot();

private:
    Ui::Login *ui;

};

#endif // LOGIN_H
