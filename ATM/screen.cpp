#include "screen.h"

Screen::Screen()
    :w_authentication(nullptr)
    ,w_selection(nullptr)
    ,w_withdrawal(nullptr)
    ,w_deposit(nullptr)
    ,w_message(nullptr)
    ,bank(nullptr)
    ,innerState(AtmState::Authentication)
{

    QGridLayout* layout = new QGridLayout;
    this->setLayout(layout);
    this->setStyleSheet("QWidget{background-color:rgb(200,50,50)}");

    switchAuthentication();

    //debug
    // clearAll();
    // layout->addWidget(w_selection,0,0);
    // clearAll();
    // layout->addWidget(w_authentication);
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

void Screen::tmpMsg(const QString &msg,AtmState state,int subState,int time)
{
    switchMessage();
    msg_title->setText(msg);

    // 使用 QTimer 定时器来延迟清空文本和恢复布局
    QTimer::singleShot(time, [state,subState,this]() {
        // 清空消息文本
        this->msg_title->setText("");
        this->switchState(state,subState);
    });
}

void Screen::switchAuthentication(int subState)
{
    innerState = AtmState::Authentication;
    clearAll();
    w_authentication = new QWidget;
    //用户认证
    QGridLayout* layout=new QGridLayout;
    QLabel* label = new QLabel;
    // label->setFixedSize(QSize(600,200));
    if(subState == 0)
    {
        label->setText("用户认证：请输入账号");
    }
    else
    {
        label->setText("用户认证，请输入账号PIN码");
    }
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label,0,0);

    w_authentication->setLayout(layout);

    this->layout()->addWidget(w_authentication);
}


void Screen::switchSelection(int subState)
{
    innerState = AtmState::Selection;
    clearAll();

    w_selection = new QWidget;
    //选择事物
    withdrawalBtn = new QPushButton;
    depositBtn = new QPushButton;
    QLabel* title = new QLabel;
    title->setText("请选择事务");
    title->setAlignment(Qt::AlignCenter);
    withdrawalBtn->setText("取钱");
    depositBtn->setText("存钱");

    //切换界面
    connect(withdrawalBtn,&QPushButton::clicked,this,&Screen::WithdrawalBtnSlot);
    connect(depositBtn,&QPushButton::clicked,this,&Screen::DepositBtnSlot);

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(title,0,0,1,2);
    layout->addWidget(withdrawalBtn,1,0);
    layout->addWidget(depositBtn,1,1);

    w_selection->setLayout(layout);
    this->layout()->addWidget(w_selection);
}



void Screen::switchWithdrawal(int subState)
{
    Q_ASSERT(bank);
    innerState = AtmState::Withdrawal;
    clearAll();
    w_withdrawal = new QWidget;
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

    QLabel* amount = new QLabel;
    QString amountStr = "当前可用余额: ";
    amountStr += QString::number(bank->getBalance());
    amount->setText(amountStr);

    layout->addWidget(amount,100,0);

    w_withdrawal->setLayout(layout);
    this->layout()->addWidget(w_withdrawal);
}

void Screen::switchDeposit(int sunState)
{
    innerState = AtmState::Deposit;
    clearAll();
    w_deposit = new QWidget;
    //存钱选项
    QGridLayout* layout = new QGridLayout;
    QLabel* title = new QLabel;
    title->setText("请选择存钱额度");
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

    w_deposit->setLayout(layout);
    this->layout()->addWidget(w_deposit);
}

void Screen::switchMessage(int subState)
{
    clearAll();
    w_message = new QWidget;
    //纯信息页面
    QGridLayout* layout = new QGridLayout;
    msg_title = new QLabel;
    msg_title->setText("请编辑信息");
    msg_title->setAlignment(Qt::AlignCenter);
    layout->addWidget(msg_title,0,0,1,2);
    w_message->setLayout(layout);

    this->layout()->addWidget(w_message);
}

void Screen::switchState(AtmState state,int subState)
{
    switch(state)
    {
    case Authentication:switchAuthentication(subState);break;
    case Selection: switchSelection(subState);break;
    case Withdrawal:switchWithdrawal(subState);break;
    case Deposit:switchDeposit(subState);break;
    defualt: switchMessage(subState);msg_title->setText("状态转换错误");break;
    }
}

void Screen::setBank(BankDatabase *pbank)
{
    Q_ASSERT(pbank);
    bank = pbank;
}

int Screen::getSelectedNum()
{
    return selectedNum;
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
            emit selectNumSignal();
        }
    }
}

void Screen::WithdrawalBtnSlot()
{
    innerState = AtmState::Withdrawal;
    switchWithdrawal();
    emit withdrawSignal();
}

void Screen::DepositBtnSlot()
{
    innerState = AtmState::Deposit;
    switchDeposit();
    emit withdrawSignal();
}
