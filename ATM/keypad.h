#ifndef KEYPAD_H
#define KEYPAD_H

#include "common.h"

class Keypad:public QWidget
{
    Q_OBJECT
public:
    Keypad();

    void getInput();

public slots:
    void keypadCallback();
    void clearTxt();
    void initBtns();
    void keyPressEvent(QKeyEvent* event);

    void keyBoardInput(char ch);

    QString getNumberStr();
private:
    QLabel* label;

public://这些需要给atm绑定槽函数
    QPushButton* functionBtn;
    QPushButton* clearBtn;
    QPushButton* cancelBtn;
    QPushButton* confirmBtn;
};

#endif // KEYPAD_H
