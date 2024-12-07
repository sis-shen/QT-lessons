#ifndef BANKDATABASE_H
#define BANKDATABASE_H
#include "common.h"
#include <string>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

class Account
{
public:
    int _accountNum;
    int _PIN;
    int _amount;

    void qdebug()
    {
        qDebug()<<"Account DEBUG";
        qDebug()<<_accountNum;
        qDebug()<<_PIN;
        qDebug()<<_amount;
    }
};

class BankDatabase
{
public:
    enum Status{
        Authenticated,
        UnkownAcc,
        WrongPIN,
        MissDB,
    };

public:
    BankDatabase();

    ~BankDatabase();

    Status authenticateAccount(const int num,const int PIN,bool* authenticated);
    int getBalance();
    int getAccountNum();
private:
    bool createAccount(int num);
private:
    Account* account;
    QSqlDatabase db;
};

#endif // BANKDATABASE_H
