#include "transaction.h"

void Trans::Withdrawal::execute()
{
    connect(screen,&Screen::selectNumSignal,this,&Withdrawal::WithdrawalSlot);
}

void Trans::Withdrawal::WithdrawalSlot()
{
    int num = screen->getSelectedNum();
    qDebug()<<"WithdrawalSlot";
    int amount = bankDB->getAccountNum();
    if(amount < num)
    {
        qDebug()<<"余额不足";
        qDebug()<<"amount "<<amount<< " num:"<<num;
        screen->tmpMsg("账户余额不足！",AtmState::Withdrawal);
    }
    if(cash_dispenser->isAvailable(num))
    {
        qDebug()<<"现金不足";
        qDebug()<<"avalailable cash "<<cash_dispenser->getAvailableCash()<< " num:"<<num;
        screen->tmpMsg("账户余额不足！",AtmState::Withdrawal);
    }
    //尝试取钱
    if (!bankDB->withdrawalCash(num))
    {
        qDebug()<<"数据库取钱失败";
        screen->tmpMsg("数据库错误",AtmState::Authentication);
        return;
    }
    //开始分发
    cash_dispenser->dispenseCash(num);

    screen->tmpMsg("取钱成功!",AtmState::Withdrawal);
}
