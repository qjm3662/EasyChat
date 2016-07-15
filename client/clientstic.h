#ifndef CLIENTSTIC_H
#define CLIENTSTIC_H
#include "client.h"
#include "user.h"
#include "chatdb.h"
#include <iostream>
#include<vector>
#include <QVector>

using namespace std;

class ClientStic
{
public:
    static Client* getInstance();
    static User * getInstanceUser();
    static ChatDB *getInstanceCDB();
    static vector<User> *getInstanceUserList();
    static QVector<QString> *getInstanceChatName();

private:
    ClientStic();
    ~ClientStic();
    //�Ѹ��ƹ��캯����=������Ҳ��Ϊ˽��,��ֹ������
    ClientStic(const ClientStic&);
    ClientStic& operator=(const ClientStic&);

    static Client* instance;
    static User * user;
    static ChatDB *cdb;
    static vector<User> *v_user;

    static QVector<QString> *v_chatName;
};

#endif // CLIENTSTIC_H
