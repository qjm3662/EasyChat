#include "GroupChat.h"
#include "ui_GroupChat.h"
#include "critem.h"
#include <iostream>
#include <vector>
#include <QListWidgetItem>
#include <QDebug>
#include <QDesktopWidget>
#include <QStandardItem>
#include "FriendListItem.h"
#include <iostream>
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QtNetwork>
#include <QTextCodec>
#include <QString>
#include "client/client.h"
#include "client/clientstic.h"
#include <QPixmap>
#include <QIcon>

using namespace std;

GroupChat::GroupChat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupChat)
{
    ui->setupUi(this);
    cdb = ClientStic::getInstanceCDB();
    vector<CR> v = cdb->getCRByDoubleUserName("253", "Robbin");

    //实例化
    sender = new QUdpSocket(this);
    receiver = new QUdpSocket(this);
    receiver->bind(14843, QUdpSocket::ShareAddress);
    connect(receiver, SIGNAL(readyRead()), this, SLOT(processPendingDatagram()));


    ui->listWidget->setFont(font);
    for(unsigned i = 0; i < v.size(); i++)
    {
        FriendListItem *buddyItem = new FriendListItem(v[i], font, color, ui->listWidget);
        //buddyItem->setBuddyInfo(info);
        QListWidgetItem *item = new QListWidgetItem("",ui->listWidget);

        item->setSizeHint(buddyItem->size());
        ui->listWidget->setItemWidget(item,buddyItem);
        qDebug() << buddyItem->geometry();
    }
    //ui->listWidget->show();
    ui->listWidget->scrollToBottom();
    QDesktopWidget *deskdop = QApplication::desktop();
    move((deskdop->width() - this->width())/2, (deskdop->height() - this->height())/2 - 40);

    QObject::connect(ui->te_input, SIGNAL(textChanged()), this, SLOT(textChangeSlot()));



    vector<User>* v_user = ClientStic::getInstanceUserList();
    for(unsigned i = 0; i < v_user->size(); i++)
    {
        ui->listWidget_2->addItem(new QListWidgetItem((*v_user)[i].getUsername()));
    }

    QObject::connect(ClientStic::getInstance(), SIGNAL(updateFriendList()), this, SLOT(updateFriendlistSlot()));





}

GroupChat::~GroupChat()
{
    delete ui;
}

void GroupChat::on_send_clicked()
{
    CR cr = CR(0,ClientStic::getInstanceUser()->getUsername() , "ds", ui->te_input->toPlainText());
    FriendListItem *buddyItem = new FriendListItem(cr, font, color);
    //buddyItem->setBuddyInfo(info);
    QListWidgetItem *item = new QListWidgetItem("",ui->listWidget);
    item->setSizeHint(buddyItem->size());
    ui->listWidget->setItemWidget(item,buddyItem);
    ui->listWidget->scrollToBottom();

    std::string ss = ui->te_input->toPlainText().toStdString();
    ui->te_input->clear();
    QByteArray datagram(ss.c_str());
    sendMessage(datagram);

}

void GroupChat::on_pushButton_clicked()
{
    bool ok;
    font = QFontDialog::getFont(&ok, this);
    if(ok)
        ui->te_input->setFont(font);
    else
        qDebug() << tr("没有选择字体 ！！");
}

void GroupChat::on_pushButton_2_clicked()
{
    QColorDialog dialog(Qt::red, this);
    dialog.setOption(QColorDialog::ShowAlphaChannel);//显示alpha选项
    dialog.exec();
    color = dialog.currentColor();
    ui->te_input->setTextColor(color);
}

void GroupChat::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "文件对话框", "F:", "图片文件(*.png);;图片文件(*.jpg)");
    qDebug() << "fileName : " << fileName;
}

void GroupChat::on_pushButton_4_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "文件对话框", "F:", "所有文件(*.*)");
    qDebug() << "fileName : " << fileName;
}

void GroupChat::textChangeSlot()
{
    if(ui->te_input->toPlainText().endsWith("\n"))
    {
       on_send_clicked();
    }
}



void GroupChat::sendMessage(QByteArray  a)
{
    //QByteArray datagram =a;
    QString qunMessageTemp;
    qunMessageTemp+= ClientStic::getInstanceUser()->getUsername();
    qunMessageTemp+="\t";
    qunMessageTemp+=a;
    std::string ss = qunMessageTemp.toStdString();

    QByteArray datagram(ss.c_str());
    sender->writeDatagram(datagram.data(), datagram.size(),
                          QHostAddress::Broadcast, 14843);  //端口号为14843
}
QByteArray GroupChat::processPendingDatagram()
{
        // 拥有等待的数据报
    while(receiver->hasPendingDatagrams())
    {
        QByteArray datagram1;
        // 让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        datagram1.resize(receiver->pendingDatagramSize());
        // 接收数据报，将其存放到datagram中
        receiver->readDatagram(datagram1.data(), datagram1.size());
        qDebug() << datagram1;
        QString temp(datagram1);


        QString qunSenderTemp;
        QString qunContentTemp;


        int jj=0;
        while(temp[jj]!='\t')
        {
            qunSenderTemp+=temp[jj];
            jj++;

        }
        jj++;
        while(jj<temp.size())
        {
            qunContentTemp+=temp[jj];
            jj++;
        }
        //QString content(datagram1);

        if(qunSenderTemp != ClientStic::getInstanceUser()->getUsername()){
            CR cr = CR(0,qunSenderTemp , ClientStic::getInstanceUser()->getUsername(), qunContentTemp);
            FriendListItem *buddyItem = new FriendListItem(cr, font, color);
            //buddyItem->setBuddyInfo(info);
            QListWidgetItem *item = new QListWidgetItem("",ui->listWidget);
            item->setSizeHint(buddyItem->size());
            ui->listWidget->setItemWidget(item,buddyItem);
            ui->listWidget->scrollToBottom();
            qunSenderTemp.clear();
            qunContentTemp.clear();
        }

       return datagram1;
    }
}

void GroupChat::paintEvent(QPaintEvent *e)
{
    //this->setStyleSheet("QWidget{background:url(:/src/src/background.png)}");
    QPalette palette(this->palette());
    QPixmap pix(":/src/src/Groupbackground.jpg");
    QBrush brush(pix);
    palette.setBrush(QPalette::Background, brush);
    this->setPalette(palette);

    this->setWindowTitle("一起High");
    this->setWindowIcon(QIcon(":/src/src/icon.ico"));
}

void GroupChat::updateFriendlistSlot()
{

    ui->listWidget_2->clear();
    vector<User>* v_user = ClientStic::getInstanceUserList();
    for(unsigned i = 0; i < v_user->size(); i++)
    {
        ui->listWidget_2->addItem(new QListWidgetItem((*v_user)[i].getUsername()));
    }
    update();

    qDebug() << "group update";
}
