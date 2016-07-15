#include "critem.h"
#include "ui_critem.h"

CRItem::CRItem(CR cr, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CRItem)
{
    ui->setupUi(this);
    ui->label->setText(cr.getSenderName() + "£º");
    ui->label_2->setText(cr.getContent());

    ui->label_2->setWordWrap(true);
    ui->label_2->setAlignment(Qt::AlignTop);
    ui->label_2->adjustSize();
    //ui->label_2->resize(QSize(1033, ui->textEdit->height()));

    this->adjustSize();
}

CRItem::~CRItem()
{
    delete ui;
}

void CRItem::paintEvent(QPaintEvent *e)
{

}
