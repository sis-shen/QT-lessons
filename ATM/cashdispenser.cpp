#include "cashdispenser.h"


CashDispenser::CashDispenser(int availableCash)
    :_availableCash(availableCash)
{

}

bool CashDispenser::isAvailable(int num)
{
    if(num > _availableCash)return false;

    return true;
}

bool CashDispenser::dispenseCash(int num)
{
    if(isAvailable(num)  == false)
    {
        return false;
    }

    _availableCash-=num;
    qDebug()<<"成功分发现金(TODO)";
}

int CashDispenser::getAvailableCash()
{
    return _availableCash;
}

