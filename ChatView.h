#ifndef CHATVIEW_H
#define CHATVIEW_H

#include <QWidget>
#include <QStandardItemModel>
#include <QFont>
#include <QColor>
#include <QKeyEvent>
#include "client/client.h"
#include "client/clientstic.h"
#include "cr.h"
#include "user.h"
#include "chatdb.h"
#include <QCloseEvent>
namespace Ui {
    class ChatView;
}

class ChatView : public QWidget
{
    Q_OBJECT

public:
    explicit ChatView(User targetUser, QWidget *parent = 0);
    ~ChatView();

    virtual void keyPressEvent(QKeyEvent *e);
    void closeEvent(QCloseEvent *e);
    void paintEvent(QPaintEvent *e);
signals:
    void closeSig();

private slots:

    void on_send_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();



    void on_pushButton_4_clicked();

    void textChangeSlot();

    void privateMessageSlot(CR cr);

    void closeSigSlot();

private:
    Ui::ChatView *ui;
    QStandardItemModel *model;
    int j;
    QFont font;
    QColor color;
    User targetUser;
    ChatDB *cdb;
};

#endif // CHATVIEW_H
