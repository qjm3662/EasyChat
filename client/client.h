#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QAbstractSocket>
#include "cr.h"
#include "chatdb.h"

class QTcpSocket;


//规定 1注册信号 包含姓名，密码  2登录信号 包含姓名 密码 3私聊信号 senderName receiverName content


class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

signals:
    void connected();
    void loginSuccess();
    void privateMessage(CR cr);
    void closeLoginUI();
    void updateFriendList();
    void registerSuccess();
public:
    QTcpSocket *tcpclient;
    QString message;
    // 用来存放数据的大小信息
    quint16 blockSize;
    bool isConnected;
    ChatDB *cdb;

public slots:
    void newConnect(QString ip, int port);
    QString readMessage();
    void sendMessage(QString flag, QString id, QString senderName, QString receiverName, QString key);
    void displayError(QAbstractSocket::SocketError);
    void connectedSlot();
    void loginSuccessSlot();
//    void on_connectButton_clicked();
//    void on_pushButton_clicked();
};

#endif // CLIENT_H
