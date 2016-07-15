#include "chatdb.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QVariant>
#include <QSqlDriver>

ChatDB::ChatDB(int i)
{

    //用户信息数据库初始化
    db = QSqlDatabase::addDatabase("QSQLITE","mydb.db");
    db.setDatabaseName("mydb.db");
    this->open();
    QSqlQuery query(db);
    query.exec("create table user (id int ,""username varchar(20) primary key, ""password varchar(20)), ""sign varchar(100))");
    query.exec("insert into user values(1, 'LiMing', '1230', '好无聊呀')");
    query.exec("insert into user values(2, 'LiuTao', '1230', '好无聊呀')");
    query.exec("insert into user values(3, 'WangHong', '1230', '好无聊呀')");


    query.exec("create table cr (id int primary key,"
               "senderName varchar(20), "
               "receiverName varchar(20), "
               "content varchar(300), "
               "flag int)");

}

bool ChatDB::open()
{
    if (!db.open()) {
        QMessageBox::critical(0, "Cannot open database",
            "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }else{
        return true;
    }
}

void ChatDB::listAllUser()
{
    // 使用QSqlQuery查询整张表
    QSqlQuery query(db);
    query.exec("select * from user");
    while(query.next())
    {
        qDebug() << query.value(0).toInt() << query.value(1).toString() << query.value(2).toString();
    }
}

bool ChatDB::isOpen()
{
    return db.isOpen();
}

void ChatDB::close()
{
    if(db.isOpen()){
        db.close();
    }
}

ChatDB::~ChatDB(){
    QSqlDatabase::removeDatabase("qt_sql_default_connection");
    if(isOpen()){
        db.close();
    }
}

int ChatDB::sizeUser(void)
{
    QSqlQuery query(db);
    query.exec("select * from user");
    // 以下是在例程17-4中添加的代码
    int numRows = 0;
    // 先判断该数据库驱动是否支持QuerySize特性，如果支持，则可以使用size()函数，
    // 如果不支持，那么就使用其他方法来获取总行数
    if (db.driver()->hasFeature(QSqlDriver::QuerySize)) {
        //qDebug() << "has feature: query size";
        numRows = query.size();
    } else {

        //qDebug() << "no feature: query size";
        query.last();
        //qDebug() << "query.at():" << query.last();
        numRows = query.at() + 1;
    }
    //qDebug() << "row number: " << numRows;
    listAllUser();
    return numRows;
}

bool ChatDB::addUser(QString username, QString password, QString sign)
{
    QSqlQuery query(db);
    query.prepare("insert into user (id, username, password) values (:id, :username, :password, :sign)");
    query.bindValue(":id", sizeUser() + 1);
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.bindValue(":sign", sign);
    return query.exec();
}

bool ChatDB::addUser(User user)
{
    return addUser(user.getUsername(), user.getPassword(), user.getSign());
}


bool ChatDB::deleteUserById(int id)
{
    QSqlQuery query(db);
    QString temp = "delete from user where id = '";
    temp = temp + QString::number(id) + "'";
    return query.exec(temp);//即成为通用的形式
}

bool ChatDB::deleteUserByUsername(QString username)
{
    QSqlQuery query(db);
    QString temp = "delete from user where username = '";
    temp = temp + username + "'";
    qDebug() << temp;
    return query.exec(temp);
}

vector<User> ChatDB::getAllUser()
{
    vector<User> v;
    QSqlQuery query(db);
    query.exec("select * from user");
    while(query.next()){
        v.push_back(User(query.value(0).toInt(), query.value(1).toString(),
                         query.value(2).toString(), query.value(3).toString()));
    }
    return v;
}

User ChatDB::getUserById(int id)
{
    QSqlQuery query(db);
    QString temp = "select * from user where id = '";
    temp = temp + QString::number(id) + "'";
    query.exec(temp);
    if(query.next()){
        return User(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString());
    }else{
        return User(0);
    }

}

User ChatDB::getUserByUsername(QString username)
{
    QSqlQuery query(db);
    QString temp = "select * from user where username = '";
    temp = temp + username + "'";
    query.exec(temp);
    if(query.next()){
        return User(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString());
    }else{
        return User(0);
    }
}




int ChatDB::sizeCR()
{
    QSqlQuery query(db);
    query.exec("select * from cr");
    // 以下是在例程17-4中添加的代码
    int numRows = 0;
    // 先判断该数据库驱动是否支持QuerySize特性，如果支持，则可以使用size()函数，
    // 如果不支持，那么就使用其他方法来获取总行数
    if (db.driver()->hasFeature(QSqlDriver::QuerySize)) {
        //qDebug() << "has feature: query size";
        numRows = query.size();
    } else {
        listAllCR();
        //qDebug() << "no feature: query size";
        query.last();
        //qDebug() << "query.at():" << query.last();
        numRows = query.at() + 1;
    }
    //qDebug() << "row number: " << numRows;
    return numRows;
}

void ChatDB::listAllCR()
{
    // 使用QSqlQuery查询整张表
    QSqlQuery query(db);
    query.exec("select * from cr");
    while(query.next())
    {
        qDebug() << query.value(0).toInt() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString() << query.value(4).toInt();
    }
}

bool ChatDB::addCR(QString senderName, QString receiverName, QString content)
{
    QSqlQuery query(db);
    query.prepare("insert into cr (id, senderName, receiverName, content ,flag) values (:id, :senderName, :receiverName, :content ,:flag)");
    query.bindValue(":id", sizeCR() + 1);
    query.bindValue(":senderName", senderName);
    query.bindValue(":receiverName", receiverName);
    query.bindValue(":content", content);
    query.bindValue(":flag",1);
    return query.exec();
}

bool ChatDB::addCR(CR cr)
{
    return addCR(cr.getSenderName(), cr.getReceiverName(), cr.getContent());
}

bool ChatDB::deleteCRById(int id)
{
    QSqlQuery query(db);
    QString temp = "delete from cr where id = '";
    temp = temp + QString::number(id) + "'";
    return query.exec(temp);
}

bool ChatDB::deleteCRBySenderName(QString senderName)
{
    QSqlQuery query(db);
    QString temp = "delete from cr where senderName = '";
    temp = temp + senderName + "'";
    qDebug() << temp;
    return query.exec(temp);
}

bool ChatDB::deleteCRByreceiverName(QString receiverName)
{
    QSqlQuery query(db);
    QString temp = "delete from cr where receiverName = '";
    temp = temp + receiverName + "'";
    qDebug() << temp;
    return query.exec(temp);
}

vector<CR> ChatDB::getAllCR()
{
    vector<CR> v;
    QSqlQuery query(db);
    query.exec("select * from cr");
    while(query.next()){
        v.push_back(CR(query.value(0).toInt(), query.value(1).toString(),
                         query.value(2).toString(), query.value(3).toString(),
                       query.value(4).toInt()));
    }
    return v;
}

vector<CR> ChatDB::getCRByReceiverName(QString name)
{
    QSqlQuery query(db);
        vector<CR> v;
        vector<QString> du;
        QString temp = "select * from cr where receiverName = '";
        temp = temp + name + "'";
        //qDebug() << temp;
        query.exec(temp);
        temp = "update cr set flag = 2 where id = '";
        if(query.next()){
            if(query.value(4).toInt()==1){
    //           temp = temp + query.value(0).toString() + "'";
               du.push_back(query.value(0).toString());
    //           qDebug()<< temp;
    //           query.exec(temp);
                v.push_back(CR(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toInt()));
            }
            while(query.next()){
                if(query.value(4).toInt()==1){
    //                temp = "update cr set flag = 2 where id = '";
    //                temp = temp + query.value(0).toString() + "'";
                    du.push_back(query.value(0).toString());
    //                qDebug()<< temp;
                    //query.exec(temp);
                    v.push_back(CR(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toInt()));
                }
            }
            for(int i=0;i<du.size();i++){
                temp = "update cr set flag = 2 where id = '";
                temp = temp + du[i] + "'";
                //qDebug()<<temp;
                query.exec(temp);
            }

        }else{
            qDebug() << "CR is null";
        }
        return v;
}


vector<CR> ChatDB::getCRByUserName(QString name)
{
//    QSqlQuery query(db);
//    QString temp = "select * from user where username = '";
//    temp = temp + username + "'";
//    query.exec(temp);
//    if(query.next()){
//        return User(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString());
//    }else{
//        return User(0);
//    }

    QSqlQuery query(db);
    vector<CR> v;
    QString temp = "select * from cr where senderName = '";
    temp = temp + name + "' or receiverName = '" + name + "'";
    qDebug() << temp;
    query.exec(temp);
    if(query.next()){
        v.push_back(CR(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(),query.value(4).toInt()));
        while(query.next()){
            v.push_back(CR(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(),query.value(4).toInt()));
        }

    }else{
        qDebug() << "CR is null";
    }
    return v;
}

vector<CR> ChatDB::getCRByDoubleUserName(QString name1, QString name2)
{
    QSqlQuery query(db);
    vector<CR> v;
    QString temp = "select * from cr where senderName = '";
    temp = temp + name1 + "' and receiverName =  '" + name2 + "'" + " or senderName = '" + name2 + "' and receiverName = '" + name1 + "'";
    qDebug() << temp;
    query.exec(temp);
    if(query.next()){
        v.push_back(CR(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(),query.value(4).toInt()));
        while(query.next()){
            v.push_back(CR(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(),query.value(4).toInt()));
        }

    }else{
        qDebug() << "CR is null";
    }
    return v;
}

vector<CR> ChatDB::getCRByDoubleUserName(User user1, User user2){
    return getCRByDoubleUserName(user1.getUsername(), user2.getUsername());
}

QString ChatDB::getLatest(QString name1, QString name2)
{
    int i;
    vector<CR> v=this->getCRByDoubleUserName(name1, name2);
    QString temp;
    i=v.size();
    i--;
    if(v[i].getFlag()==1){
        temp=v[i].getContent();
        v[i].changef();
    }
    else
        temp="";
            return temp;

}





