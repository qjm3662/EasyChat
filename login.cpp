#include "login.h"
#include "ui_login.h"
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QDesktopWidget>
#include "register.h"
#include <QTime>
#include <QIcon>
#include "user.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    //this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    //this->setWindowOpacity(0.9);//设置透明1-全体透明
    //this->setAttribute(Qt::WA_TranslucentBackground, true);//设置透明2-窗体标题栏不透明,背景透明
    ui->setupUi(this);
    Client * client = ClientStic::getInstance();
    QObject::connect(client, SIGNAL(closeLoginUI()), this, SLOT(closeLoginUISlot()));
    QDesktopWidget *deskdop = QApplication::desktop();
    move((deskdop->width() - this->width())/2, (deskdop->height() - this->height())/2);
    ui->le_password->setEchoMode(QLineEdit::Password);


}

Login::~Login()
{
    delete ui;
}

void Login::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/src/src/easy_chat1.png");
    painter.drawPixmap(42, 12, 222, 58, pix);

    this->setWindowTitle("登陆");
    QPixmap pix1(":/src/src/icon.ico");
    this->setWindowIcon(QIcon(pix1));
}

void Login::on_btn_creat_new_account_clicked()
{
    Register *r = new Register;
    r->show();
    QTime dieTime = QTime::currentTime().addMSecs(200);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 200);
    this->close();

}

void Login::on_btn_cancel_clicked()
{
//    Client * client = ClientStic::getInstance();
//    client->sendMessage("3", "1", ui->le_username->text(), "253","kasdlcnsadvnsakdvnsv");
    this->close();
}

void Login::on_btn_login_clicked()
{
    Client * client = ClientStic::getInstance();
    client->sendMessage("2", "1", ui->le_username->text(), "dsasadvc", ui->le_password->text());
    User *user = ClientStic::getInstanceUser();
    user->setUsername(ui->le_username->text());
}

void Login::closeLoginUISlot()
{
    this->close();
}
