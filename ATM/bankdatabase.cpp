#include "bankdatabase.h"

BankDatabase::BankDatabase()
    :account(nullptr)
{
    sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
    conn = driver->connect("localhost","root","Shendongfa!1");
    stm = conn->createStatement();
}

BankDatabase::~BankDatabase()
{
    delete account;
}

BankDatabase::Status BankDatabase::authenticateAccount(const int num, const int PIN)
{
    if(conn->isClosed())return MissDB;
    bool ret = createAccount(num);
    if(ret == false) return UnkownAcc;

    if(PIN != account->_PIN) return WrongPIN;

    return Authenticated;
}

bool BankDatabase::createAccount(int num)
{
    if(account)
    {
        delete account;
        account = nullptr;
    }

    account = new Account;

    std::string sql = "select * from account where id = " + QString::number(num).toStdString();
    sql::ResultSet* res = stm->executeQuery(sql);
    while(res->next())
    {
        account->_accountNum = res->getInt(1);
        account->_PIN = res->getInt(2);
        account->_amount = res->getInt(3);
        return true;
    }

    //用户不存在
    return false;
}
