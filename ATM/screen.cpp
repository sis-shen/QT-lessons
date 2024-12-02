#include "screen.h"

Screen::Screen()
    :w_authentication(nullptr)
    ,w_selection(nullptr)
    ,w_withdrawal(nullptr)
    ,w_deposit(nullptr)
    ,w_message(nullptr)
{
    initLayouts();

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(w_authentication,0,0);
    this->setLayout(layout);
    w_authentication->setStyleSheet("QWidget{background-color:rgb(200,50,50)}");

    //debug
    clearAll();
    layout->addWidget(w_selection,0,0);
    clearAll();
    layout->addWidget(w_authentication);
    // layout->addWidget(w_withdrawal);
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
    msg_title = new QLabel;
    msg_title->setText("请编辑信息");
    msg_title->setAlignment(Qt::AlignCenter);
    layout->addWidget(msg_title,0,0,1,2);
    w_message->setLayout(layout);
}

void Screen::clearAll()
{
    QLayout* layout = this->layout();
    while(layout->count())
    {
        QLayoutItem* obj=layout->takeAt(0);
        if(obj->widget())
        {
            delete obj->widget();
        }
    }


}

void Screen::tmpMsg(const QString &msg, int time)
{
    // 获取当前布局
    QLayout* tmp = this->layout();
    QGridLayout* layout = qobject_cast<QGridLayout*>(tmp);

    // 保证布局存在并且 w_message 以及 msg_title 被正确初始化
    if (!layout || !w_message || !msg_title)
        return;

    // 保存原先的布局项并从布局中取出它
    QLayoutItem* w = layout->takeAt(0);
    layout->addWidget(w_message, 0, 0);  // 将消息控件添加到布局中

    // 设置消息文本
    msg_title->setText(msg);

    // 使用 QTimer 定时器来延迟清空文本和恢复布局
    QTimer::singleShot(time, [layout, w, this]() {
        // 清空消息文本
        msg_title->setText("");

        // 恢复原先的控件到布局
        layout->takeAt(0);
        layout->addWidget(w->widget(), 0, 0);
    });
}

void Screen::switchAuthentication()
{
    clearAll();
    w_authentication = new QWidget;
    //用户认证
    QGridLayout* layout=new QGridLayout;
    QLabel* label = new QLabel;
    // label->setFixedSize(QSize(600,200));
    label->setText("用户认证：请输入账号代码");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label,0,0);

    w_authentication->setLayout(layout);

    this->layout()->addWidget(w_authentication);
}

void Screen::switchSelection()
{
    clearAll();

    w_selection = new QWidget;
    //选择事物
    QPushButton* withdrawalBtn = new QPushButton;
    QPushButton* depositBtn = new QPushButton;
    QLabel* title = new QLabel;
    title->setText("请选择事务");
    title->setAlignment(Qt::AlignCenter);
    withdrawalBtn->setText("取钱");
    depositBtn->setText("存钱");

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(title,0,0,1,2);
    layout->addWidget(withdrawalBtn,1,0);
    layout->addWidget(depositBtn,1,1);

    w_selection->setLayout(layout);
    this->layout()->addWidget(w_selection);
}

void Screen::switchWithdrawal()
{
    //取钱选项
    QGridLayout* layout = new QGridLayout;
    QLabel* title = new QLabel;
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
