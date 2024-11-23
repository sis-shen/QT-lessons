#include "additemdialog.h"

void AddItemDialog::Reset()
{
    edit_name->setText("");
    edit_price->setText("");
    edit_cnt->setValue(0);
}

void AddItemDialog::TrySubmit()
{
    int num = edit_cnt->value();
    if(num == 0)return;

    QString name = edit_name->text();
    QString str = edit_price->text();
    double price = str.toDouble();

    _item._name = name.toStdString();
    _item._price = price;
    _item._cnt = num;

    accept();
}

AddItemDialog::AddItemDialog():_item("",0,0)
{
    this->setMinimumWidth(400);
    this->setWindowTitle("添加商品");
    QGridLayout* main_layout = new QGridLayout;

    edit_name = new QLineEdit;
    edit_name->setToolTip("请输入商品名称");
    edit_name->setPlaceholderText("请输入商品名称");

    edit_price = new QLineEdit;
    edit_price->setToolTip("请输入商品单价");
    edit_price->setPlaceholderText("请输入商品单价");

    edit_cnt = new QSpinBox;

    QLabel* tip = new QLabel;
    tip->setText("在下方输入商品数量");

    submit = new QPushButton("提交");

    main_layout->addWidget(edit_name,0,0);
    main_layout->addWidget(edit_price,1,0);
    main_layout->addWidget(tip,2,0);
    main_layout->addWidget(edit_cnt,3,0);
    main_layout->addWidget(submit,4,0);
    this->setLayout(main_layout);

    QDoubleValidator* vali = new QDoubleValidator(0,999999,2,this);
    edit_price->setValidator(vali);

    connect(submit,&QPushButton::clicked,this,&AddItemDialog::TrySubmit);
}
