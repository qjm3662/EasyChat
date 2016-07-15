#include "FriendListItem.h"
#include "ui_FriendListItem.h"
#include <QInputContext>
#include <QStaticText>
#include <QDebug>
#include <QDateTime>
#include <QTransform>

FriendListItem::FriendListItem(CR& cr, QFont font, QColor color, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendListItem)
{
    QDateTime time = QDateTime::currentDateTime();
    QString time_ = time.toString("hh:mm:ss");
    ui->setupUi(this);
    ui->textEdit->setEnabled(false);
    ui->label->setText(cr.getSenderName() + "(" + time_ + ")" "£º");
    ui->label->adjustSize();
    ui->textEdit->setFont(font);
    ui->textEdit->setTextColor(color);
    ui->textEdit->setText(cr.getContent());
    QStaticText t(ui->textEdit->toPlainText());
    t.prepare(QTransform(), font);

    if(t.size().toSize().width()*96/72 < 900){
        ui->textEdit->resize(t.size().toSize().width()*96/72 + 10, t.size().toSize().height()*96/72 + 15);
    }else{

        ui->textEdit->resize(900, t.size().toSize().width()*1.0*96/72/900*t.size().toSize().height() + 30);
    }
    this->adjustSize();

}

FriendListItem::~FriendListItem()
{
    delete ui;
}
