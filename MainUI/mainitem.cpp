#include "mainitem.h"
#include "ui_mainitem.h"


MainItem::MainItem(User user, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainItem)
{

    ui->setupUi(this);
    ui->l_username->setText(user.getUsername());
    ui->l_sign->setText(user.getSign());
}

MainItem::~MainItem()
{
    delete ui;
}
