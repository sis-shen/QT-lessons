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

BankDatabase::Status BankDatabase::authenticateAccount(const int num, const int PIN,bool* authenticated)
{
    // if(db.isOpen() == false)return MissDB;
    bool ret = createAccount(num);
    if(ret == false) return UnkownAcc;

    if(PIN != account->_PIN) return WrongPIN;

    *authenticated = true;
    return Authenticated;
}

int BankDatabase::getBalance()
{
    Q_ASSERT(account);
    return account->_amount;
}

int BankDatabase::getAccountNum()
{
    Q_ASSERT(account);
    return account->_amount;
}

bool BankDatabase::withdrawalCash(int num)
{
    if(!db.transaction())
    {
        qDebug()<<"事务开启失败";
        return false;
    }
    QSqlQuery query;
    query.prepare("update accounts set amount = :amount where account = :account");
    query.bindValue(":account",account->_accountNum);
    query.bindValue(":amount",account->_amount);

    if(!query.exec())
    {
        qDebug()<< "取钱事务失败";
        db.rollback();
        return false;
    }

    qDebug()<<"取钱事务执行成功";
    return true;
}

bool BankDatabase::createAccount(int num)
{
    if(account)
    {
        delete account;
        account = nullptr;
    }

    account = new Account;

#ifdef DEBUG
    account->_accountNum = 1;
    account->_amount = 99999;
    account->_PIN = 666666;
    return true;
#endif

    QString sql = "select * from accounts where account=";
    sql += QString::number(num);
    QSqlQuery query;
    if(db.isOpen() == false)
    {
        if(!db.open())
        {
            qDebug() << "Error: " << query.lastError().text();
        }
    }
    if (query.exec(sql)) {  // 替换为你的表名
        while (query.next())
        {
            account->_accountNum = query.value(0).toInt();
            account->_PIN = query.value(1).toInt();
            account->_amount = query.value(2).toInt();

            account->qdebug();
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
