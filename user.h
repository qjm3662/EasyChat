#ifndef USER_H
#define USER_H
#include <QString>
class User
{
public:
    User(int id, QString username = "0", QString password = "0", QString sign = "Œ“ ««©√˚¿≤¿≤¿≤");
    User();
    int getId(void);
    QString getUsername(void);
    QString getPassword(void);
    QString getSign(void);
    void setUsername(QString userName);
    void setSign(QString sign);

private:
    int id;
    QString username;
    QString password;
    QString sign;
};

#endif // USER_H
