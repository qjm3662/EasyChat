#ifndef CR_H
#define CR_H
#include <QString>
class CR
{
public:
    CR(int id, QString senderName, QString receiverName, QString content,int flag = 1);
    int getId(void);
    QString getSenderName(void);
    QString getReceiverName(void);
    QString getContent(void);
    int getFlag(void);
    void changef(void);
private:
    int flag;
    int id;
    QString senderName;
    QString receiverName;
    QString content;
};

#endif // CR_H
