#ifndef MAINUI_GROUPCHAT_H
#define MAINUI_GROUPCHAT_H

#include <QWidget>
#include <QStandardItemModel>
#include <QFont>
#include <QColor>
#include <QKeyEvent>
#include <QUdpSocket>
#include "chatdb.h"
#include <QVector>

namespace Ui {
    class GroupChat;
}

class GroupChat : public QWidget
{
    Q_OBJECT

public:
    explicit GroupChat(QWidget *parent = 0);
    ~GroupChat();
    void paintEvent(QPaintEvent *e);

private slots:
    void on_send_clicked(void);

    void on_pushButton_clicked(void);

    void on_pushButton_2_clicked(void);

    void on_pushButton_3_clicked(void);

    void on_pushButton_4_clicked(void);
    void textChangeSlot(void);

    void sendMessage(QByteArray  a);  //调用时将a群发送到各个接收者
    QByteArray processPendingDatagram();  //有信息传来时会自动接收，返回值为接受的QBteArry信息

    void updateFriendlistSlot(void);



private:
    Ui::GroupChat *ui;
    QStandardItemModel *model;
    int j;
    QFont font;
    QColor color;
    QUdpSocket *receiver;
    QUdpSocket *sender;
    ChatDB *cdb;
    QVector<QString>* v_userName;
};

#endif // MAINUI_GROUPCHAT_H
