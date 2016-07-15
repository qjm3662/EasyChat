#include "cr.h"
#include "chatdb.h"

CR::CR(int id, QString senderName, QString receiverName, QString content ,int flag)
    :id(id), senderName(senderName), receiverName(receiverName), content(content),flag(flag)
{

}

int CR::getId()
{
    return id;
}

QString CR::getSenderName()
{
    return senderName;
}

QString CR::getReceiverName()
{
    return receiverName;
}

QString CR::getContent()
{
    return content;
}

int CR::getFlag()
{
    return flag;
}

void CR::changef()
{
    flag=2;
}
