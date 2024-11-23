#ifndef CLIENT_H
#define CLIENT_H
#include <string>
using namespace  std;

class Client
{
public:
    Client(const string& name = "",double money = 0)
        :_money(money)
        ,_name(name)
    {}

    void addMoney(double money)
    {
        _money+=money;
    }

    bool payMoney(double money)
    {
        if(money > _money)return false;
        _money-=money;
        return true;
    }

    double getMoney()
    {
        return _money;
    }

    string getName()
    {
        return _name;
    }

    bool isPayAble(double money)
    {
        if(money>_money)return false;
        return true;
    }
private:
    double _money;
    string _name;
};

#endif // CLIENT_H
