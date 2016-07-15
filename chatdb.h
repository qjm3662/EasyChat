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
*���ݿ�����࣬ʵ�����ݿ�Ĵ������ṩ��ɾ�Ĳ�ӿ�
*/
class ChatDB
{
public:
    ChatDB(int i);
    ~ChatDB(void);                                                                      //�ж����ݿ��Ƿ�رգ�����ر���
    bool open(void);                                                                    //�ṩ�ֶ��ر����ݿ�Ľӿ�
    bool isOpen(void);                                                                  //�жϵ�ǰ���ݿ��Ƿ��ڴ�״̬

    //�û���Ϣ��
    void listAllUser(void);                                                             //�г�User�������е����ݳ�Ա
    void close(void);                                                                   //�ṩ�ֶ��ر����ݿ�Ľӿ�
    int sizeUser(void);                                                                 //����ĳ�ű������������flag���ڱ����һ�ű�
    bool addUser(QString username, QString password, QString sign = "������ѽ");         //���һ��user��Ϣ��id�Զ�����(��ӳɹ�����true)//����Ϊ���غ���
    bool addUser(User user);                                                            //���һ��user��Ϣ��id�Զ�����(��ӳɹ�����true)
    bool deleteUserById(int id);                                                        //ͨ��Idɾ���û���Ϣ�����ã�
    bool deleteUserByUsername(QString username);                                        //ͨ���û���ɾ���û���Ϣ�����ã�
    vector<User> getAllUser(void);                                                      //��ȡ�����û���Ϣ�������ض���
    User getUserById(int id);                                                           //����id��ȡ�û���Ϣ(��δ��ѯ���򷵻�User����idΪ0���û��������붼Ϊ��0��)
    User getUserByUsername(QString username);                                           //�����û�����ȡ�û���Ϣ(��δ��ѯ���򷵻�User����idΪ0���û��������붼Ϊ��0��)

    //�����¼��
    void listAllCR(void);
    int sizeCR(void);
    bool addCR(QString senderName, QString receiverName, QString content);
    bool addCR(CR cr);
    bool deleteCRById(int id);
    bool deleteCRBySenderName(QString senderName);
    bool deleteCRByreceiverName(QString receiverName);
    vector<CR> getAllCR(void);
    vector<CR> getCRByReceiverName(QString name);                       //���ݽ����ߵļ�¼����ѯ
    vector<CR> getCRByUserName(QString name);                           //���û�й��ڸ��û��������¼�����ص�vector��size()Ϊ0
    vector<CR> getCRByDoubleUserName(QString name1, QString name2);     //�����û�����ȡ�����û�֮�����е������¼
    vector<CR> getCRByDoubleUserName(User user1, User user2);           //���������û������ȡ�����û�֮�����е������¼
    QString getLatest(QString name1, QString name2);                    //�������û����ƻ�ȡ���¼�¼��flagΪ1��ȡ


protected:
    QSqlDatabase db;    //�û���Ϣ���ݿ�
//    QSqlDatabase dbCR;      //�����¼���ݿ�
};

#endif // CHATDB_H
