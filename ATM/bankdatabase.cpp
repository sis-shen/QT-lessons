#include "bankdatabase.h"

BankDatabase::BankDatabase()
    :account(nullptr)
{
    //输出已安装的驱动
    qDebug() << QSqlDatabase::drivers();
    // 设置数据库文件路径
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("Qt");
    db.setHostName("47.99.48.121");
    db.setPassword("12345678");
    db.setUserName("QTUser");
}

BankDatabase::~BankDatabase()
{
    delete account;
}

BankDatabase::Status BankDatabase::authenticateAccount(const int num, const int PIN)
{
    // if(db.isOpen() == false)return MissDB;
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

    QString sql = "select * from accounts where account=";
    sql += QString::number(num);
    QSqlQuery query;
    if (query.exec(sql)) {  // 替换为你的表名
        while (query.next())
        {
            account->_accountNum = query.value(0).toInt();
            account->_PIN = query.value(1).toInt();
            account->_amount = query.value(2).toInt();
            return true;
        }
    }
    else
    {
        qDebug() << "Error: " << query.lastError().text();
    }

    //用户不存在
    return false;
}
