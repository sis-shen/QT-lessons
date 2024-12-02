#include "atm.h"

ATM::ATM()
    :authenticated(false)
    ,currentAccountNumber(-1)
    ,screen(new Screen)
    ,bankDatabase(new BankDatabase)
    ,keypad(new Keypad)
    ,state(AtmState::Authentication)
    ,subState(0)
{
    connect(keypad->confirmBtn,&QPushButton::clicked,this,&ATM::confirmRouter);
    connect(keypad->cancelBtn,&QPushButton::clicked,this,&ATM::cancelRouter);

}

void ATM::confirmRouter()
{
    // switch(state)
    // {
    // case AtmState::Authentication:
    //     authenticateUser();break;
    // }
    if(state == AtmState::Authentication)
    {
        qDebug()<<"authentication";
        authenticateUser();
    }
}

void ATM::cancelRouter()
{

}

Screen *ATM::getScreen()
{
    return screen;
}

Keypad *ATM::getKeypad()
{
    return keypad;
}

void ATM::init()
{
    authenticated = false;
    currentAccountNumber = 0;
}

void ATM::authenticateUser()
{
    static int accountId;
    int PIN;

    static int cnt = 3;

    if(subState == 0)
    {
        bool ok = false;
        // accountId = keypad->getNumberStr().toInt(&ok);
        if(ok)
        {
            subState = 0;
        }
        else
        {
            qDebug()<<"非法输入";
            screen->tmpMsg("非法输入，请重试");
            return;
        }
    }
}
