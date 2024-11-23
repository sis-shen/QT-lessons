#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,main_left(new QWidget())
    ,main_right(new QWidget())
    ,charge_dialog(new ChargeDialog)
    ,add_item_dialog(new AddItemDialog)
    ,_vend(new VendingMachine)
    ,_client(new Client)
{
    ui->setupUi(this);
    this->setWindowTitle("自助售货机");
    this->setWindowIcon(QIcon(":/vendingMachine.png"));
    this->setMinimumWidth(1200);
    this->setMinimumHeight(600);

    SetMainLayout();
    SetRightLayout();

    SetRightUp();
    SetRightDown();
    SetLeft();
    UpdateMoney();

    SetAllConnection();

    AutoInit();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _vend;
    delete _client;
}

void MainWindow::SetMainLayout()
{
    QWidget* main_widget = this->centralWidget();

    main_left->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    main_right->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    main_right->setObjectName("main_right");

//    main_left->setStyleSheet(".QWidget{background-color: rgb(150, 150, 150)}");
    main_right->setStyleSheet("#main_right{border-image: url(:/background.png)};.QWidget{margin:0;border:0}");

    QGridLayout* main_layout = new QGridLayout();
    main_layout->setContentsMargins(0,0,0,0);//设置边距为0
    main_layout->addWidget(main_left,0,0);
    main_layout->addWidget(main_right,0,1);

    main_layout->setColumnStretch(0,1);
    main_layout->setColumnStretch(1,3);

    main_widget->setLayout(main_layout);
}

void MainWindow::SetRightLayout()
{
    right_up = new QWidget;
    right_down = new QWidget;

    //DEBUG
//    right_up->setStyleSheet(".QWidget{background-color: rgba(150, 150, 150,50)}");

    QGridLayout* right_layout = new QGridLayout();
    right_layout->addWidget(right_up,0,0);
    right_layout->addWidget(right_down,1,0);

    right_layout->setRowStretch(0,7);
    right_layout->setRowStretch(1,4);

    main_right->setLayout(right_layout);
}

void MainWindow::SetRightUp()
{
    QWidget* terminal = new QWidget(right_up);
    terminal->setObjectName("terminal");
    terminal->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    terminal->setStyleSheet("#terminal{margin-top:40%;");

    QGridLayout* mylayout = new QGridLayout;
    mylayout->setContentsMargins(0,0,0,0);
    mylayout->addItem(new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Expanding),0,0);
    mylayout->addItem(new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Expanding),0,1);
    mylayout->addItem(new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Expanding),1,1);
    mylayout->addWidget(terminal,1,0);

    mylayout->setRowStretch(0,25);
    mylayout->setRowStretch(1,50);

    mylayout->setColumnStretch(0,50);
    mylayout->setColumnStretch(1,20);

    right_up->setLayout(mylayout);

    QGridLayout* inner_layout = new QGridLayout;
    QWidget* combo_div = new QWidget;
    QWidget* spin_div = new QWidget;
    QWidget* money_div = new QWidget;
    QWidget* charge_div = new QWidget;
    money = new QPushButton("金额");
    charge = new QPushButton("充值");
    combo = new QComboBox(combo_div);
    spin_num = new QSpinBox(spin_div);


    QGridLayout* tmp = new QGridLayout;
    tmp->addWidget(combo,0,0);
    combo_div->setLayout(tmp);
    tmp = new QGridLayout;
    tmp->addWidget(spin_num);
    spin_div->setLayout(tmp);
    tmp = new QGridLayout;
    tmp->addWidget(money);
    money_div->setLayout(tmp);
    tmp=new QGridLayout;
    tmp->addWidget(charge);
    charge_div->setLayout(tmp);


    money->setObjectName("money");
    charge->setObjectName("charge");
    combo->setObjectName("charge");
    spin_num->setObjectName("spin_num");
    combo_div->setObjectName("combo_div");
    spin_div->setObjectName("spin_div");
    money_div->setObjectName("money_div");
    charge_div->setObjectName("charge_div");

    money_div->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    charge_div->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    combo_div->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    spin_div->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    money_div->setStyleSheet("#money_div{margin:20%;border-top:10%}");
    charge_div->setStyleSheet("#charge_div{margin:20%}");
    combo_div->setStyleSheet("#combo_div{margin:20%}");
    spin_div->setStyleSheet("#spin_div{margin:20%}");
//    inner_layout->setContentsMargins(20,10,20,0);

    combo->setFixedHeight(combo->height()+20);



    inner_layout->addWidget(money_div,0,0);
    inner_layout->addWidget(charge_div,0,1);
    inner_layout->addWidget(combo_div,1,0);
    inner_layout->addWidget(spin_div,1,1);

    inner_layout->setRowStretch(0,1);
    inner_layout->setRowStretch(1,1);

    terminal->setLayout(inner_layout);
}

void MainWindow::SetRightDown()
{
    QGridLayout* main_layout = new QGridLayout;

    buy = new QPushButton("购买");
    add_item = new QPushButton("进货");

    main_layout->addWidget(buy,0,0);
    main_layout->addWidget(add_item,0,1);

    main_layout->setColumnStretch(0,8);
    main_layout->setColumnStretch(1,2);

    right_down->setLayout(main_layout);
}

void MainWindow::UpdateMoney()
{
    double new_money = charge_dialog->_money;
    _client->addMoney(new_money);
    QString txt("金额: ");
    double num = _client->getMoney();

    money->setText(txt+QString::number(num));
}

void MainWindow::TryBuy()
{
    QString name = combo->currentText();
    int num = spin_num->value();
    if(num == 0) return;
    qDebug()<<name<<" "<<num;

    if(_vend->IsEnough(name.toStdString(),num))
    {
        double sum_value = _vend->SumValue(name.toStdString(),num);
        if(_client->getMoney() < sum_value)
        {
            static QMessageBox* warningBox = new QMessageBox;
            warningBox->setIcon(QMessageBox::Warning); // 设置为警告图标
            warningBox->setWindowTitle("警告");
            warningBox->setText("没钱！不许白嫖！");
            warningBox->setStandardButtons(QMessageBox::Ok); // 添加按钮
            warningBox->setDefaultButton(QMessageBox::Ok); // 默认按钮
            warningBox->show();
            return;
        }

        _vend->_SellItem(name.toStdString(),num);
        UpdateTable(name.toStdString());
        _client->payMoney(sum_value);
        QString txt("金额: ");
        double num = _client->getMoney();

        money->setText(txt+QString::number(num));
        spin_num->setValue(0);

        static QMessageBox* warningBox = new QMessageBox;
        warningBox->setIcon(QMessageBox::Information); // 设置为警告图标
        warningBox->setWindowTitle("信息");
        warningBox->setText("购买成功!");
        warningBox->setStandardButtons(QMessageBox::Ok); // 添加按钮
        warningBox->setDefaultButton(QMessageBox::Ok); // 默认按钮
        warningBox->show();
    }
    else
    {
        //数量不足
        static QMessageBox* warningBox = new QMessageBox;
        warningBox->setIcon(QMessageBox::Warning); // 设置为警告图标
        warningBox->setWindowTitle("警告");
        warningBox->setText("商品数量不足！");
        warningBox->setStandardButtons(QMessageBox::Ok); // 添加按钮
        warningBox->setDefaultButton(QMessageBox::Ok); // 默认按钮
        warningBox->show();
    }

}

void MainWindow::TryAddItem()
{
    const Item& item = add_item_dialog->_item;
    add_item_dialog->Reset();
    AddItem(item);
}

void MainWindow::ShowAddItemDialog()
{
    add_item_dialog->show();
}

void MainWindow::ClearAddDialog()
{
    add_item_dialog->Reset();
}

void MainWindow::SetLeft()
{
    item_table = new QTableWidget;
    item_table->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    item_table->insertColumn(0);
    item_table->insertColumn(1);
    item_table->insertColumn(2);

    item_table->setHorizontalHeaderItem(0,new QTableWidgetItem("名称"));
    item_table->setHorizontalHeaderItem(1,new QTableWidgetItem("单价"));
    item_table->setHorizontalHeaderItem(2,new QTableWidgetItem("数量"));

    item_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
//    item_table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    QGridLayout* left_layout = new QGridLayout;
    left_layout->addWidget(item_table,0,0);

    main_left->setLayout(left_layout);
}

void MainWindow::AddItem(const Item& item)
{
    if(!_vend->_InfoItem(item._name))
    {
        bool isOK = _vend->_AddItem(item);
        if(!isOK)
        {
            qDebug()<<"商品添加失败";
            return;
        }
        int sz = _name_to_row.size();
        _name_to_row[item._name] = sz;
        item_table->insertRow(sz);
        UpdateTable(item);
    }
    else
    {
        bool isOK = _vend->_AddItem(item);
        if(isOK)
        {
            UpdateTable(_vend->GetItem(item._name));
        }
    }
    UpdateCombo(item._name);


//    _vend->_AddItem(item._name,item._price,item._cnt);

}

void MainWindow::AutoInit()
{
    if(_name_to_row.size() != 0)
    {
        qDebug()<<"不能重复初始化！！！";
    }

    AddItem(Item("小苹果",5,10));
    AddItem(Item("大香蕉",2.5,2));
    AddItem(Item("香蕉君",30,5));
    AddItem(Item("野兽仙贝",1145.14,15));

    AddItem(Item("野兽仙贝",1145.14,15));
}

void MainWindow::UpdateCombo(const std::string& name)
{
    if(_combo_set.count(name))return;

    combo->addItem(name.c_str());
    _combo_set.insert(name);
}

void MainWindow::UpdateTable(const std::string &name)
{
    UpdateTable(_vend->GetItem(name));

}

void MainWindow::UpdateTable(const Item &item)
{
    if(!_name_to_row.count(item._name))return;
    int sz = _name_to_row[item._name];
    item_table->setItem(sz,0,new QTableWidgetItem(item._name.c_str()));
    item_table->setItem(sz,1,new QTableWidgetItem(QString::number(item._price,'f',2)));
    item_table->setItem(sz,2,new QTableWidgetItem(QString::number(item._cnt)));
}

void MainWindow::SetAllConnection()
{
    connect(charge,&QPushButton::clicked,this,&MainWindow::OpenChargeDialog);
    connect(charge_dialog,&QDialog::accepted,this,&MainWindow::UpdateMoney);
    connect(buy,&QPushButton::clicked,this,&MainWindow::TryBuy);
    connect(add_item,&QPushButton::clicked,this,&MainWindow::ShowAddItemDialog);
    connect(add_item_dialog,&QDialog::accepted,this,&MainWindow::TryAddItem);
    connect(add_item_dialog,&QDialog::rejected,this,&MainWindow::ClearAddDialog);
}

void MainWindow::OpenChargeDialog()
{
    charge_dialog->show();
}
