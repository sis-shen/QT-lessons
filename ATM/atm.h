#ifndef ATM_H
#define ATM_H

#include "bankdatabase.h"
#include "cashdispenser.h"
#include "screen.h"
#include "keypad.h"
#include "common.h"
#include "transaction.h"

class ATM:public QWidget
{
    Q_OBJECT
public:
    ATM();


    Screen* getScreen();
    Keypad* getKeypad();

public slots:
    void confirmRouter();
    void cancelRouter();

    void withdrawalSlot();
    void depositSlot();
private:
    bool authenticated;
    int currentAccountNumber;
    Screen* screen;
    BankDatabase* bankDatabase;
    Keypad* keypad;
    Trans::Transaction* trans;
    CashDispenser* cash_dispenser;

    AtmState state;
    int subState;
private:
    void authenticateUser();
    void init();
    void syncState();
    void makeWithdrawal();
};

#endif // ATM_H
