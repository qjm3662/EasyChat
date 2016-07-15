#include "ChatView.h"
#include "ui_ChatView.h"
#include "critem.h"

#include <iostream>
#include <vector>
#include <QListWidgetItem>
#include <QPixmap>
#include <QIcon>
#include <QDebug>
#include <QDesktopWidget>
#include <QStandardItem>
#include "FriendListItem.h"
#include <iostream>
#include <QFontDialog>
#include <QColorDialog>
#include <QFileDialog>



using namespace std;


ChatView::ChatView(User targetUser, QWidget *parent) :
    QWidget(parent),ui(new Ui::ChatView)/*,targetUser(0, "0", "0")*/
{
    cdb = ClientStic::getInstanceCDB();

    this->targetUser = targetUser;
    ui->setupUi(this);
    ui->te_input->setFocus();

    vector<CR> v = cdb->getCRByDoubleUserName(ClientStic::getInstanceUser()->getUsername(), targetUser.getUsername());

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

    Client *client = ClientStic::getInstance();
    QObject::connect(client,SIGNAL(privateMessage(CR)), this, SLOT(privateMessageSlot(CR)));

    QObject::connect(this, SIGNAL(closeSig()), this, SLOT(closeSigSlot()));




}

ChatView::~ChatView()
{
    delete ui;

}


void ChatView::on_send_clicked()
{
    CR cr = CR(0, ClientStic::getInstanceUser()->getUsername(), targetUser.getUsername(), ui->te_input->toPlainText());
    FriendListItem *buddyItem = new FriendListItem(cr, font, color);
    QListWidgetItem *item = new QListWidgetItem("",ui->listWidget);
    item->setSizeHint(buddyItem->size());
    ui->listWidget->setItemWidget(item,buddyItem);
    ui->listWidget->scrollToBottom();
    ui->te_input->clear();
    cdb->addCR(cr);

    Client *client = ClientStic::getInstance();
    client->sendMessage("3", "sd", ClientStic::getInstanceUser()->getUsername(), targetUser.getUsername(), cr.getContent());
    //192.168.16.27
}

void ChatView::on_pushButton_clicked()
{
    bool ok;
    font = QFontDialog::getFont(&ok, this);
    if(ok)
        ui->te_input->setFont(font);
    else
        qDebug() << tr("没有选择字体 ！！");
}

void ChatView::on_pushButton_2_clicked()
{
    QColorDialog dialog(Qt::red, this);
    dialog.setOption(QColorDialog::ShowAlphaChannel);//显示alpha选项
    dialog.exec();
    color = dialog.currentColor();
    ui->te_input->setTextColor(color);
}

void ChatView::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "文件对话框", "F:", "图片文件(*.png);;图片文件(*.jpg)");
    qDebug() << "fileName : " << fileName;
}

void ChatView::keyPressEvent(QKeyEvent *e)
{
//    switch(e->KeyPress){
//        qDebug() << e;
//    }
}

void ChatView::on_pushButton_4_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "文件对话框", "F:", "所有文件(*.*)");
    qDebug() << "fileName : " << fileName;
}

void ChatView::textChangeSlot()
{
    if(ui->te_input->toPlainText().endsWith("\n"))
    {
       on_send_clicked();
    }
}

void ChatView::privateMessageSlot(CR cr)
{
    if(cr.getSenderName() == targetUser.getUsername()){
        FriendListItem *buddyItem = new FriendListItem(cr, font, color);
        //buddyItem->setBuddyInfo(info);
        QListWidgetItem *item = new QListWidgetItem("",ui->listWidget);
        item->setSizeHint(buddyItem->size());
        ui->listWidget->setItemWidget(item,buddyItem);
        ui->listWidget->scrollToBottom();
        //ui->te_input->clear();
    }
}

void ChatView::closeEvent(QCloseEvent *e)
{
    emit closeSig();
}

void ChatView::closeSigSlot()
{
    int position = ClientStic::getInstanceChatName()->lastIndexOf(targetUser.getUsername());
    qDebug() << "position : " << position  << " content:" << (*ClientStic::getInstanceChatName())[position];
    ClientStic::getInstanceChatName()->remove(position);
}

void ChatView::paintEvent(QPaintEvent *e)
{
    //this->setStyleSheet("QWidget{background:url(:/src/src/background.png)}");
    QPalette palette(this->palette());
    QPixmap pix(":/src/src/siliaobackground.jpg");
    QBrush brush(pix);
    palette.setBrush(QPalette::Background, brush);
    this->setPalette(palette);

    this->setWindowTitle("偷偷聊");
    this->setWindowIcon(QIcon(":/src/src/icon.ico"));
}
