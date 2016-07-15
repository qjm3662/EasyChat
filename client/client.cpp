#include "client.h"
#include <QtNetwork>
#include "ChatView.h"
#include "clientstic.h"
#include "cr.h"
#include "user.h"
#include "MainUI/GroupChat.h"
#include "MainUI/MainUI.h"
#include <iostream>
#include <vector>
#include "clientstic.h"
#include <QMessageBox>
#include <QPixmap>
using namespace std;
Client::Client(QWidget *parent) :
    QDialog(parent)
{
//    ui->setupUi(this);
    tcpclient = new QTcpSocket(this);
    isConnected = false;
    cdb = ClientStic::getInstanceCDB();
    connect(tcpclient, SIGNAL(readyRead()), this, SLOT(readMessage()),Qt::DirectConnection);
    connect(tcpclient, SIGNAL(connected()), this, SLOT(connectedSlot()));
    connect(this, SIGNAL(loginSuccess()), this, SLOT(loginSuccessSlot()));
}

Client::~Client()
{

}
void Client::newConnect(QString ip, int port)
{
    // 初始化数据大小信息为0
    blockSize = 0;
    if(!isConnected)
        {
            tcpclient->abort();
            tcpclient->connectToHost(ip,port);
            isConnected = true;
        }
    // 取消已有的连接
//    tcpSocket->abort();
//    tcpSocket->connectToHost(ui->hostLineEdit->text(),
//                             ui->portLineEdit->text().toInt());
}

QString Client::readMessage()
{
    QDataStream in(tcpclient);
    // 设置数据流版本，这里要和服务器端相同
    in.setVersion(QDataStream::Qt_4_6);
    // 如果是刚开始接收数据
    if (blockSize == 0) {
        //判断接收的数据是否大于两字节，也就是文件的大小信息所占的空间
        //如果是则保存到blockSize变量中，否则直接返回，继续接收数据
        if(tcpclient->bytesAvailable() < (int)sizeof(quint16)) return "";
        in >> blockSize;
    }
    // 如果没有得到全部的数据，则返回，继续接收数据
    if(tcpclient->bytesAvailable() < blockSize) return "";
    // 将接收到的数据存放到变量中
    in >> message;

    // 显示接收到的数据
    qDebug() << message;
    if(message == "sign in success"){
        emit loginSuccess();
        emit closeLoginUI();

    }
    if(message == "register success"){

        emit registerSuccess();

    }
    if(message == "sign in failed"){
        QMessageBox msgBox;
        msgBox.setText("Sign in fail, please check your account and password!!");
        msgBox.setIconPixmap(QPixmap(":src/src/icon.ico"));
        msgBox.exec();

    }
    if(message == "repeat name,please try again"){
        QMessageBox msgBox;
        msgBox.setText("The user name already exist!!");
        msgBox.setIconPixmap(QPixmap(":src/src/icon.ico"));
        msgBox.exec();
    }
    if(message.contains('\n')){

        if(message.contains('\t')){
            vector<User> *v = ClientStic::getInstanceUserList();
//            QVector<QString> *v_userName = ClientStic::getInstanceChatName();
            QString tempName;
            v->clear();

            int i=1;
            while(i<message.size())
            {
               while(message[i]!='\n')
                {
                    tempName+=message[i];
                    i++;
                }
                i++;
                qDebug() << tempName;
                if(!(tempName == ClientStic::getInstanceUser()->getUsername())){
                    v->push_back(User(1, tempName));
//                    if(!v_userName->contains(tempName)){
//                        v_userName->push_back(tempName);
//                    }
                }
                tempName.clear();
            }

            emit updateFriendList();
        }else{

            QString senderName;
            QString content;
            int ii=0;
            while(message[ii] != '\n')
            {
                senderName += message[ii];
                ii++;
            }
            ii++;
            while(ii < message.size()){
                content += message[ii];
                ii++;
            }
            CR cr(01, senderName, ClientStic::getInstanceUser()->getUsername(), content);
            if(!ClientStic::getInstanceChatName()->contains(senderName)){
                ClientStic::getInstanceChatName()->push_back(senderName);
                ChatView* cv = new ChatView(User(1,senderName));
                cv->show();
            }
            emit privateMessage(cr);
        }
    }
    blockSize=0;
    return message;
}

void Client::sendMessage(QString flag, QString id, QString senderName, QString receiverName, QString key)
{
    tcpclient->flush();
    flag+="\n";
    flag+= id;
    flag+="\n";
    flag+= senderName;
    flag+="\n";
    flag+= receiverName;
    flag+="\n";
    flag+= key;
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out << (quint16)0;
    out << flag;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    tcpclient->write(block);
    tcpclient->flush();
}

void Client::displayError(QAbstractSocket::SocketError)
{
    qDebug() << tcpclient->errorString();
}

void Client::connectedSlot()
{
    emit connected();
}

void Client::loginSuccessSlot()
{

//    ChatView *cv = new ChatView;
//    GroupChat * gc = new GroupChat;

//    cv->show();
//    gc->show();

    MainUI *mu = new MainUI;
    mu->show();

}
