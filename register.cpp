#include "register.h"
#include "ui_register.h"
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QDesktopWidget>
#include "register.h"
#include "login.h"
#include <QTime>
#include <QIcon>
#include <QMessageBox>

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    QDesktopWidget *deskdop = QApplication::desktop();
    move((deskdop->width() - this->width())/2, (deskdop->height() - this->height())/2);
    ui->le_password->setEchoMode(QLineEdit::Password);
    client = ClientStic::getInstance();

    QObject::connect(client, SIGNAL(registerSuccess()), this, SLOT(registerSuccessSlot()));
}
Register::~Register()
{
    delete ui;
}

void Register::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/src/src/easy_chat1.png");
    painter.drawPixmap(42, 12, 222, 58, pix);
    this->setWindowTitle("зЂВс");
    this->setWindowIcon(QIcon(":/src/src/icon.ico"));
}

void Register::on_btn_to_login_clicked()
{
    Login *l = new Login;
    l->show();
    QTime dieTime = QTime::currentTime().addMSecs(200);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 200);
    this->close();
}

void Register::on_btn_cancel_2_clicked()
{
    this->close();
}

void Register::on_btn_register_clicked()
{
//    Client * client = ClientStic::getInstance();
    client->sendMessage("1", "1", ui->le_username->text(), "dsasadvc", ui->le_password->text());
}

void Register::registerSuccessSlot()
{
    QMessageBox msgBox;
    msgBox.setText("Register success!!");
    msgBox.setIconPixmap(QPixmap(":src/src/icon.ico"));
    msgBox.exec();
    on_btn_to_login_clicked();
}
