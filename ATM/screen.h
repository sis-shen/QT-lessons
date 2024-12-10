#ifndef SCREEN_H
#define SCREEN_H
#include "common.h"
#include "bankdatabase.h"
#include "QThread"
#include <QTimer>
class Screen:public QWidget
{
    Q_OBJECT
public:
    Screen();
    void paintEvent(QPaintEvent *event)override;
    void displayMessage(const QString& msg);
    void clearAll();

    void tmpMsg(const QString& msg,AtmState state,int subState = 0,int time = 1000);

    void switchAuthentication(int subState = 0);
    void switchSelection(int subState = 0);
    void switchWithdrawal(int subState = 0);
    void switchDeposit(int substate = 0);
    void switchMessage(int substate = 0);

    void switchState(AtmState state,int subState);

    void setBank(BankDatabase* pbank);

    int getSelectedNum();
public:
signals:
    void selectNumSignal();
    void withdrawSignal();
    void depositSignal();

public slots:
    void selectNumSlot();
    void WithdrawalBtnSlot();
    void DepositBtnSlot();
public:
    AtmState innerState;
    QPushButton* withdrawalBtn = nullptr;
    QPushButton* depositBtn = nullptr;
private:
    //既是布局，也是状态表示
    QWidget* w_authentication;
    QWidget* w_selection;
    int selectedNum;
    QWidget* w_withdrawal;
    QWidget* w_deposit;
    QWidget* w_message;

    QLabel* msg_title;

    BankDatabase* bank;
private:
    QVector<int> num_selection = {100,500,1000,2000};
};

#endif // SCREEN_H
