#include "transaction.h"





void Withdrawal::execute()
{
    connect(screen,&Screen::selectNumSignal,this,&Withdrawal::WithdrawalSlot);
}

void Withdrawal::WithdrawalSlot(int num)
{

}
