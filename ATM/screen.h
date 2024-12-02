#ifndef SCREEN_H
#define SCREEN_H
#include "common.h"
#include "QThread"
#include <QTimer>
class Screen:public QWidget
{
public:
    Screen();
    void paintEvent(QPaintEvent *event)override;
    void displayMessage(const QString& msg);
    void initLayouts();
    void clearAll();

    void tmpMsg(const QString& msg,int time = 1000);

    void switchAuthentication();
    void switchSelection();
    void switchWithdrawal();
    void switchDeposit();
    void switchMessage();

public slots:
    void selectNumSlot();
private:
    //既是布局，也是状态表示
    QWidget* w_authentication;
    QWidget* w_selection;
    int selectedNum;
    QWidget* w_withdrawal;
    QWidget* w_deposit;
    QWidget* w_message;

    QLabel* msg_title;

private:
    QVector<int> num_selection = {100,500,1000,2000};
};

#endif // SCREEN_H
