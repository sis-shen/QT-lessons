#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "keypad.h"
#include "screen.h"
#include "cashdispenser.h"
#include "bankdatabase.h"

class Transaction
{
public:
    Transaction(int aNumber):accountNumber(aNumber){}

    int getAccountNumber();

    virtual void excute() = 0;

protected:
    int accountNumber;
};

class Withdrawal:public Transaction
{
public:
    Withdrawal(int aNum):Transaction(aNum){};

    void execute();
private:
    int amount;

    Keypad* keypad;
    Screen* screen;
    CashDispenser* cash_dispenser;
    BankDatabase* bankDB;
};

class Deposit:public Transaction
{
public:
    Deposit(int aNum):Transaction(aNum){}
};

#endif // TRANSACTION_H
