#include "connext.h"
#include "ui_connext.h"
#include "login.h"

connext::connext(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::connext)
{

    ui->setupUi(this);

}

connext::~connext()
{
    delete ui;
}

void connext::on_pushButton_clicked()
{
    Client * client = ClientStic::getInstance();
    client->newConnect(ui->hostLineEdit->text(), ui->portLineEdit->text().toInt());
    QObject::connect(client, SIGNAL(connected()), this, SLOT(connectedSlot()));
    //ClientStic::getInstance()->newConnect(ui->hostLineEdit->text(), ui->portLineEdit->text().toInt());
}

void connext::connectedSlot()
{
    Login * l = new Login;
    l->show();
    this->close();
}
