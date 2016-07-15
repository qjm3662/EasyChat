#ifndef MAINUI_H
#define MAINUI_H

#include <QWidget>
#include <QModelIndex>
//#include <QStandardItemModel>
//#include <QFont>
//#include <QColor>
//#include <QKeyEvent>

//#include "cr.h"
#include "user.h"
#include <iostream>
#include <vector>
#include "client/client.h"
#include "client/clientstic.h"
#include "chatdb.h"

using namespace std;


namespace Ui {
    class MainUI;
}

class MainUI : public QWidget
{
    Q_OBJECT

public:
    explicit MainUI(QWidget *parent = 0);
    ~MainUI();
    void paintEvent(QPaintEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void closeEvent(QCloseEvent *e);

private slots:
    void on_btn_public_clicked();
    void itemClicked(QModelIndex index);

    void on_btn_private_clicked();

    void updateFriendListSlot();

private:
    Ui::MainUI *ui;
    vector<User>* v;
    ChatDB *cdb;
    int num;
};

#endif // MAINUI_H
