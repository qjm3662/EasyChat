#include "user.h"

User::User(int id, QString username, QString password, QString sign)
    :id(id), username(username), password(password),sign(sign)
{
}


User::User()
{
    this->id = 0;
    this->username = "0";
    this->password = "0";
}


int User::getId()
{
    return id;
}

QString User::getUsername()
{
    return username;
}

QString User::getPassword()
{
    return password;
}

void User::setUsername(QString userName)
{
    this->username = userName;
}

void User::setSign(QString sign)
{
    this->sign = sign;
}

QString User::getSign()
{
    return sign;
}

