#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "keypad.h"
#include "screen.h"
#include "cashdispenser.h"
#include "bankdatabase.h"

namespace Trans
{
class Transaction:public QObject
{
public:
    Transaction(int aNumber):accountNumber(aNumber){}

    int getAccountNumber();

    virtual void execute() = 0;

protected:
    int accountNumber;
};

class Withdrawal:public Transaction
{
    Q_OBJECT
public:
    Withdrawal(int aNum):Transaction(aNum){};

    virtual void execute()override;

public slots:
    void WithdrawalSlot();
public:
    int amount;
    Keypad* keypad;
    Screen* screen;
    CashDispenser* cash_dispenser;
    BankDatabase* bankDB;
};

class Deposit:public Transaction
{
    Q_OBJECT
public:
    Deposit(int aNum):Transaction(aNum){}
    virtual void execute()override;

public slots:
    void depositSlot();
public:
    int amount;
    Keypad* keypad;
    Screen* screen;
    BankDatabase* bankDB;
};

}


#endif // TRANSACTION_H
