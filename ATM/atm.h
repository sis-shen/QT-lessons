#ifndef ATM_H
#define ATM_H

#include "bankdatabase.h"
#include "cashdispenser.h"
#include "screen.h"
#include "deposit.h"
#include "keypad.h"
#include "common.h"

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
private:
    bool authenticated;
    int currentAccountNumber;
    Screen* screen;
    BankDatabase* bankDatabase;
    Keypad* keypad;

    AtmState state;
    int subState;
private:
    void authenticateUser();
    void init();
};

#endif // ATM_H
