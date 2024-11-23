#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , atm(new ATM)
{
    ui->setupUi(this);

    this->setFixedHeight(400);

    QWidget* main_widget = new QWidget(this);
    main_widget->setFixedSize(600,400);
    // main_widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QGridLayout* layout = new QGridLayout;
    layout->setSpacing(0);

    Screen* screen = atm->getScreen();
    Keypad* keypad = atm->getKeypad();

    screen->setStyleSheet("QWidget{background-color:rgb(213,213,213)}");

    // screen->setFixedSize(600,200);
    // keypad->setFixedSize(600,200);

    layout->addWidget(screen,0,0);
    layout->addWidget(keypad,1,0);
    layout->setRowStretch(0,1);
    layout->setRowStretch(1,1);
    layout->setColumnStretch(0,1);

    main_widget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete atm;
}
