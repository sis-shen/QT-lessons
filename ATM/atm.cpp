#include "atm.h"

ATM::ATM()
    :authenticated(false)
    ,currentAccountNumber(-1)
    ,screen(new Screen)
    ,bankDatabase(new BankDatabase)
    ,keypad(new Keypad)
    ,cash_dispenser(new CashDispenser)
    ,trans(nullptr)
    ,state(AtmState::Authentication)
    ,subState(0)
{
    screen->setBank(bankDatabase);

    connect(keypad->confirmBtn,&QPushButton::clicked,this,&ATM::confirmRouter);
    connect(keypad->cancelBtn,&QPushButton::clicked,this,&ATM::cancelRouter);

    connect(screen,&Screen::withdrawSignal,this,&ATM::withdrawalSlot);
    connect(screen,&Screen::depositSignal,this,&ATM::depositSlot);


}



void ATM::confirmRouter()
{
    syncState();
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
    syncState();
}

void ATM::withdrawalSlot()
{
    makeWithdrawal();
    trans->execute();
}

void ATM::depositSlot()
{
    ;
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

void ATM::syncState()
{
    state = screen->innerState;
}

void ATM::makeWithdrawal()
{
    if(trans)
    {
        delete trans;
        trans = nullptr;
    }
    Trans::Withdrawal* wi = new Trans::Withdrawal(currentAccountNumber);
    trans = wi;
    wi->keypad = keypad;
    wi->amount = screen->getSelectedNum();

    wi->screen = screen;
    wi->cash_dispenser = cash_dispenser;
    wi->bankDB = bankDatabase;
}

void ATM::authenticateUser()
{
    static int accountId;
    int PIN;

    static int cnt = 3;

    if(subState == 0)
    {
        bool ok = false;
        accountId = keypad->getNumberStr().toInt(&ok);
        //合法性检测
        if(ok)
        {
            subState = 1;
            keypad->clearTxt();
            screen->switchAuthentication(subState);
        }
        else
        {
            qDebug()<<"账户非法输入";
            screen->tmpMsg("账户非法输入，请重试",state,subState=0);
        }
        return;
    }
    if(subState == 1)
    {

        bool ok = false;
        QString numStr = keypad->getNumberStr();
        if(numStr.size() != 6)
        {
            qDebug()<<"密码长度不对";
            return;
        }
        PIN = numStr.toInt(&ok);
        if(ok)
        {
            //UNDEBUG
            BankDatabase::Status bankState = bankDatabase->authenticateAccount(accountId,PIN,&authenticated);
#ifdef  DEBUG
            authenticated = true;
#endif
            if(authenticated == false)
            {
                qDebug()<<"认证失败";
                if(bankState == BankDatabase::Status::WrongPIN)
                {
                    qDebug()<<"密码错误";
                    cnt--;
                    if(cnt == 0)
                    {
                        subState = 0;
                        cnt = 3;
                        screen->tmpMsg("三次密码错误,请重新输入账户",state,subState);
                    }
                    else
                    {
                        screen->tmpMsg("密码错误,请重试",state,subState);
                    }
                }
                else if(bankState == BankDatabase::Status::UnkownAcc)
                {
                    qDebug()<<"未知账户";
                    keypad->clearTxt();
                    subState = 0;
                    screen->tmpMsg("未知账户，请重试",state,subState);
                }
            }
            else
            {
                qDebug()<<"认证成功";
                state = AtmState::Selection;
                subState = 0;
                screen->tmpMsg("认证成功!",state,subState);
                keypad->clearTxt();
                currentAccountNumber = bankDatabase->getAccountNum();
            }
        }
        else
        {
            qDebug()<<"密码非法输入";
            screen->tmpMsg("密码非法输入，请重试",state,subState);
            return;
        }

        return;
    }
}
