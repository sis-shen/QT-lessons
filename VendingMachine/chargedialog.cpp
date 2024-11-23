#include "chargedialog.h"

void ChargeDialog::GetMoney()
{
    QString text = edit->text();
    _money = text.toDouble();
    accept();
}

ChargeDialog::ChargeDialog():_money(0)
{
    setWindowTitle("账户充值界面");

    QGridLayout* main_layout = new QGridLayout;

    edit = new QLineEdit;
    edit->setPlaceholderText("请输入金额");

    QDoubleValidator* validator = new QDoubleValidator(0,99999,2,this);
    edit->setValidator(validator);

    submit = new QPushButton("充值");

    connect(submit,&QPushButton::clicked,this,&ChargeDialog::GetMoney);

    main_layout->addWidget(edit,0,0);
    main_layout->addWidget(submit,0,1);

    this->setLayout(main_layout);
}
