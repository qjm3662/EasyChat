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
    //把复制构造函数和=操作符也设为私有,防止被复制
    ClientStic(const ClientStic&);
    ClientStic& operator=(const ClientStic&);

    static Client* instance;
    static User * user;
    static ChatDB *cdb;
    static vector<User> *v_user;

    static QVector<QString> *v_chatName;
};

#endif // CLIENTSTIC_H
