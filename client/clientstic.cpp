#include "clientstic.h"
#include <QDebug>

ClientStic::ClientStic()
{

}

ClientStic::ClientStic(const ClientStic&){

}


ClientStic& ClientStic::operator=(const ClientStic&){
    //return NULL;
}

//在此处初始化
Client* ClientStic::instance = NULL;
Client* ClientStic::getInstance(){
    if(instance == NULL){
        instance = new Client;
        qDebug() << "new new new new new new";
        return instance;
    }else{
        return instance;
    }
}

User *ClientStic::user = NULL;
User * ClientStic::getInstanceUser()
{
    if(user == NULL){
        user = new User(22);
        return user;
    }else{
        return user;
    }
}

ChatDB *ClientStic::cdb = NULL;
ChatDB * ClientStic::getInstanceCDB()
{
    if(cdb == NULL){
        cdb = new ChatDB(0);
        return cdb;
    }else{
        return cdb;
    }
}


ClientStic::~ClientStic()
{
    if(user != NULL){
        delete user;
    }
    if(cdb != NULL){
        delete cdb;
    }
    if(instance != NULL){
        delete instance;
    }
}

vector<User> *ClientStic::v_user = NULL;
vector<User> * ClientStic::getInstanceUserList()
{
    if(v_user == NULL){
        v_user = new vector<User>;
        return v_user;
    }else{
        return v_user;
    }
}

QVector<QString> *ClientStic::v_chatName = NULL;
QVector<QString> * ClientStic::getInstanceChatName()
{
    if(v_chatName == NULL){
        v_chatName = new QVector<QString>;
        return v_chatName;
    }else{
        return v_chatName;
    }
}
