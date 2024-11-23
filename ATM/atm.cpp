#include "atm.h"

ATM::ATM()
    :authenticated(false)
    ,currentAccountNumber(-1)
    ,screen(new Screen)
    ,bankDatabase(new BankDatabase)
    ,keypad(new Keypad)

{
    // connect(keypad->confirmBtn,&QPushButton::clicked,this,&ATM::confirmRouter);
    // connect(keypad->cancelBtn,&QPushButton::clicked,this,&ATM::cancelRouter);

}

void ATM::confirmRouter()
{
    qDebug()<<"11111111";
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

// void ATM::authenticateUser(int)
// {
//     int accountId;
//     int PIN;
//     keypad->switchMode(keypad::Authentication);
//     keypad->getInput(&accountId,&PIN);
//     bool res = bankDatabase->authenticate(accountId,PIN);
//     authenticated = res;
//     if(res == false)
//     {
//         screen->showMsg("用户认证失败");
//     }
// }
