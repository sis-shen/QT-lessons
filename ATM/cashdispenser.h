#ifndef CASHDISPENSER_H
#define CASHDISPENSER_H

#include "common.h"

class CashDispenser:public QWidget
{
public:
    CashDispenser(int availableCash = 100000);

    bool isAvailable(int num);
    bool dispenseCash(int num);

    int getAvailableCash();

private:
    int _availableCash;
};

#endif // CASHDISPENSER_H
