#ifndef BANKDATABASE_H
#define BANKDATABASE_H
#include <mysql/jdbc.h>
#include "common.h"
#include <string>
class Account
{
public:
    int _accountNum;
    int _PIN;
    int _amount;
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

    Status authenticateAccount(const int num,const int PIN);
private:
    bool createAccount(int num);
private:
    Account* account;
    sql::Connection* conn;
    sql::Statement* stm;

};

#endif // BANKDATABASE_H
