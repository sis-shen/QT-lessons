#include "screen.h"

Screen::Screen()
    :w_authentication(new QWidget)
    ,w_selection(new QWidget)
    ,w_withdrawal(new QWidget)
    ,w_deposit(new QWidget)
    ,w_message(new QWidget)
{
    initLayouts();

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(w_authentication,0,0);
    this->setLayout(layout);
    w_authentication->setStyleSheet("QWidget{background-color:rgb(200,50,50)}");

    //debug
    clearAll();
    // layout->addWidget(w_selection,0,0);
    layout->addWidget(w_withdrawal);
}



void Screen::paintEvent(QPaintEvent *event)
{
    (void)event;
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget,&opt,&p,this);
}

void Screen::initLayouts()
{
    //用户认证
    QGridLayout* layout=new QGridLayout;
    QLabel* label = new QLabel;
    // label->setFixedSize(QSize(600,200));
    label->setText("用户认证：请输入账号代码");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label,0,0);

    w_authentication->setLayout(layout);

    //选择事物
    QPushButton* withdrawalBtn = new QPushButton;
    QPushButton* depositBtn = new QPushButton;
    QLabel* title = new QLabel;
    title->setText("请选择事务");
    title->setAlignment(Qt::AlignCenter);
    withdrawalBtn->setText("取钱");
    depositBtn->setText("存钱");

    layout = new QGridLayout;
    layout->addWidget(title,0,0,1,2);
    layout->addWidget(withdrawalBtn,1,0);
    layout->addWidget(depositBtn,1,1);

    w_selection->setLayout(layout);

    //取钱选项
    layout = new QGridLayout;
    title = new QLabel;
    title->setText("请选择取钱额度");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title,0,0,1,2);

    int cnt = 0;
    for(auto num:num_selection)
    {
        QPushButton* btn = new QPushButton;
        btn->setText(QString::number(num));
        layout->addWidget(btn,1+cnt/2,cnt%2);
        connect(btn,&QPushButton::clicked,this,&Screen::selectNumSlot);
        cnt++;
    }

    w_withdrawal->setLayout(layout);

    //存钱选项
    layout = new QGridLayout;
    title = new QLabel;
    title->setText("请选择存钱额度");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title,0,0,1,2);

    cnt = 0;
    for(auto num:num_selection)
    {
        QPushButton* btn = new QPushButton;
        btn->setText(QString::number(num));
        layout->addWidget(btn,1+cnt/2,cnt%2);
        connect(btn,&QPushButton::clicked,this,&Screen::selectNumSlot);
        cnt++;
    }

    //纯信息页面
    layout = new QGridLayout;
    title = new QLabel;
    title->setText("请编辑信息");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title,0,0,1,2);
}

void Screen::clearAll()
{
    QLayout* layout = this->layout();
    while(layout->count())
    {
        layout->takeAt(0);
    }
}

void Screen::selectNumSlot()
{
    QObject* obj = sender();
    if(obj)
    {
        QPushButton* btn = qobject_cast<QPushButton*>(obj);
        if(btn)
        {
            selectedNum = btn->text().toInt();
        }
    }
}
