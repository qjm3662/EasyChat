#ifndef CHATDB_H
#define CHATDB_H
#include <QSqlDatabase>
#include "user.h"
#include "cr.h"
#include <vector>
#include <iostream>

using namespace std;
/**
*
*数据库管理类，实现数据库的创建，提供增删改查接口
*/
class ChatDB
{
public:
    ChatDB(int i);
    ~ChatDB(void);                                                                      //判断数据库是否关闭，否则关闭它
    bool open(void);                                                                    //提供手动关闭数据库的接口
    bool isOpen(void);                                                                  //判断当前数据库是否处于打开状态

    //用户信息库
    void listAllUser(void);                                                             //列出User表中所有的数据成员
    void close(void);                                                                   //提供手动关闭数据库的接口
    int sizeUser(void);                                                                 //返回某张表的数据条数，flag用于标记哪一张表
    bool addUser(QString username, QString password, QString sign = "好无聊呀");         //添加一条user信息，id自动递增(添加成功返回true)//两种为重载函数
    bool addUser(User user);                                                            //添加一条user信息，id自动递增(添加成功返回true)
    bool deleteUserById(int id);                                                        //通过Id删除用户信息（慎用）
    bool deleteUserByUsername(QString username);                                        //通过用户名删除用户信息（慎用）
    vector<User> getAllUser(void);                                                      //获取所有用户信息，并返回对象集
    User getUserById(int id);                                                           //根据id获取用户信息(若未查询到则返回User对象id为0，用户名和密码都为“0”)
    User getUserByUsername(QString username);                                           //根据用户名获取用户信息(若未查询到则返回User对象id为0，用户名和密码都为“0”)

    //聊天记录库
    void listAllCR(void);
    int sizeCR(void);
    bool addCR(QString senderName, QString receiverName, QString content);
    bool addCR(CR cr);
    bool deleteCRById(int id);
    bool deleteCRBySenderName(QString senderName);
    bool deleteCRByreceiverName(QString receiverName);
    vector<CR> getAllCR(void);
    vector<CR> getCRByReceiverName(QString name);                       //根据接收者的记录来查询
    vector<CR> getCRByUserName(QString name);                           //如果没有关于该用户的聊天记录，返回的vector，size()为0
    vector<CR> getCRByDoubleUserName(QString name1, QString name2);     //根据用户名获取两个用户之间所有的聊天记录
    vector<CR> getCRByDoubleUserName(User user1, User user2);           //根据两个用户对象获取两个用户之间所有的聊天记录
    QString getLatest(QString name1, QString name2);                    //根据两用户名称获取最新记录，flag为1则取


protected:
    QSqlDatabase db;    //用户信息数据库
//    QSqlDatabase dbCR;      //聊天记录数据库
};

#endif // CHATDB_H
