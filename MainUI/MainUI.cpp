#include "MainUI.h"
#include "ui_MainUI.h"

#include <QListWidgetItem>
#include "chatdb.h"
#include <QIcon>
#include <QDebug>
#include <QDesktopWidget>
#include <QStandardItem>
#include "mainitem.h"
#include <QPainter>
#include <QPalette>
#include <QPixmap>
#include <QBrush>
#include "GroupChat.h"
#include "ChatView.h"
#include <QPixmap>

MainUI::MainUI(QWidget *parent) :
    QWidget(parent),num(0),
    ui(new Ui::MainUI)
{

    ui->setupUi(this);
    cdb = ClientStic::getInstanceCDB();
    v = ClientStic::getInstanceUserList();
    for(unsigned i = 0; i < v->size(); i++)
    {
        MainItem *buddyItem = new MainItem((*v)[i], ui->listWidget);

        QListWidgetItem *item = new QListWidgetItem("",ui->listWidget);

        item->setSizeHint(buddyItem->size());
        ui->listWidget->setItemWidget(item,buddyItem);

    }
    //ui->listWidget->clear();

    QDesktopWidget *deskdop = QApplication::desktop();
    move((deskdop->width() - this->width())/1.2, (deskdop->height() - this->height())/2 - 40);


    Client *client = ClientStic::getInstance();
    QObject::connect(client,SIGNAL(updateFriendList()), this, SLOT(updateFriendListSlot()));


    QObject::connect(ui->listWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(itemClicked(QModelIndex)));


    ui->l_username->setText(ClientStic::getInstanceUser()->getUsername());
    ui->l_sign->setText(ClientStic::getInstanceUser()->getSign());

}

MainUI::~MainUI()
{
    delete ui;
}

void MainUI::paintEvent(QPaintEvent *e)
{
    //this->setStyleSheet("QWidget{background:url(:/src/src/background.png)}");
    QPalette palette(this->palette());
    QPixmap pix(":/src/src/background.png");
    QBrush brush(pix);
    palette.setBrush(QPalette::Background, brush);
    this->setPalette(palette);
    this->setWindowTitle("EasyChat");
    this->setWindowIcon(QIcon(":/src/src/icon.ico"));

}


void MainUI::on_btn_public_clicked()
{
    GroupChat *gc = new GroupChat;
    gc->show();
}

void MainUI::itemClicked(QModelIndex index)
{
    qDebug() << index.row();
    User user = (*v)[index.row()];

    if(!ClientStic::getInstanceChatName()->contains(user.getUsername())){
        ClientStic::getInstanceChatName()->push_back(user.getUsername());
        ChatView* cv = new ChatView((*v)[index.row()]);
        cv->show();
    }

}

void MainUI::on_btn_private_clicked()
{

}

void MainUI::updateFriendListSlot()
{

    ui->listWidget->clear();
    for(unsigned i = 0; i < v->size(); i++)
    {
        MainItem *buddyItem = new MainItem((*v)[i], ui->listWidget);

        QListWidgetItem *item = new QListWidgetItem("",ui->listWidget);

        item->setSizeHint(buddyItem->size());
        ui->listWidget->setItemWidget(item,buddyItem);

    }
    update();
}


void MainUI::enterEvent(QEvent *e)
{
    QRect rc;
    QRect rect;
    rect = this->geometry();
    rc.setRect(rect.x(),rect.y(),rect.width(),rect.height());
    if(rect.top()<0)
    {
        rect.setX(rc.x());
        rect.setY(0);
        move(rc.x(),-2);
    }
}

void MainUI::leaveEvent(QEvent *e)
{
    QRect rc;
    QRect rect;
    rect = this->geometry();
    rc.setRect(rect.x(),rect.y(),rect.width(),rect.height());
    if(rect.top()<0)
    {
        move(rc.x(),-rc.height()+2);
    }
}

void MainUI::closeEvent(QCloseEvent *e)
{
    //通知服务器已下线
    ClientStic::getInstance()->sendMessage("4", "00", "00", "00", "00");
    qDebug() << "tongshi";
}
