#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QAbstractSocket>
#include "cr.h"
#include "chatdb.h"

class QTcpSocket;


//�涨 1ע���ź� ��������������  2��¼�ź� �������� ���� 3˽���ź� senderName receiverName content


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
    // ����������ݵĴ�С��Ϣ
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
