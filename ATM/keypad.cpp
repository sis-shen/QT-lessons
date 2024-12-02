#include "keypad.h"

Keypad::Keypad()
{
    initBtns();
}

void Keypad::keypadCallback()
{
    QObject* obj = sender();
    if(obj)
    {
        QPushButton* button = qobject_cast<QPushButton*>(obj);
        if(button)
        {
            QString txt = label->text();
            txt+=button->text();
            label->setText(txt);
        }
    }
}

void Keypad::clearTxt()
{
    label->setText("");
}

void Keypad::initBtns()
{
    QGridLayout* layout = new QGridLayout;

    label = new QLabel;
    label->setFixedWidth(400);
    label->setStyleSheet("QLabel {background-color:white}");

    layout->addWidget(label,0,0,1,3);
    int cnt = 1;
    for(int i = 0;i<3;++i)
    {
        for(int j = 0;j<3;++j)
        {
            QPushButton* button = new QPushButton;
            button->setText(QString::number(cnt));
            layout->addWidget(button,i+1,j);
            connect(button,&QPushButton::clicked,this,&Keypad::keypadCallback);
            cnt++;
        }
    }

    QPushButton* button = new QPushButton;
    button->setText("*");
    layout->addWidget(button,4,0);
    connect(button,&QPushButton::clicked,this,&Keypad::keypadCallback);

    button = new QPushButton;
    button->setText("0");
    layout->addWidget(button,4,1);
    connect(button,&QPushButton::clicked,this,&Keypad::keypadCallback);

    button = new QPushButton;
    button->setText("#");
    layout->addWidget(button,4,2);
    connect(button,&QPushButton::clicked,this,&Keypad::keypadCallback);

    functionBtn = new QPushButton;
    functionBtn->setText("功能");
    layout->addWidget(functionBtn,1,3);

    clearBtn = new QPushButton;
    clearBtn->setText("清除");
    layout->addWidget(clearBtn,2,3);
    connect(clearBtn,&QPushButton::clicked,this,&Keypad::clearTxt);

    cancelBtn = new QPushButton;
    cancelBtn->setText("取消");
    layout->addWidget(cancelBtn,3,3);

    confirmBtn = new QPushButton;
    confirmBtn->setText("确认");
    layout->addWidget(confirmBtn,4,3);

    this->setLayout(layout);
}

void Keypad::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_1)
    {
        keyBoardInput('1');
    }
    else if(event->key() == Qt::Key_2)
    {
        keyBoardInput('2');
    }
    else if(event->key() == Qt::Key_3)
    {
        keyBoardInput('3');
    }
    else if(event->key() == Qt::Key_4)
    {
        keyBoardInput('4');
    }
    else if(event->key() == Qt::Key_5)
    {
        keyBoardInput('5');
    }
    else if(event->key() == Qt::Key_6)
    {
        keyBoardInput('6');
    }
    else if(event->key() == Qt::Key_7)
    {
        keyBoardInput('7');
    }
    else if(event->key() == Qt::Key_8)
    {
        keyBoardInput('8');
    }
    else if(event->key() == Qt::Key_9)
    {
        keyBoardInput('9');
    }
    else if(event->key() == Qt::Key_0)
    {
        keyBoardInput('0');
    }

}

void Keypad::keyBoardInput(char ch)
{
    QString txt = label->text();
    txt+=ch;
    label->setText(txt);
}

QString Keypad::getNumberStr()
{
    return label->text();
}



