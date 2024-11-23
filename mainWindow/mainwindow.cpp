#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolBar>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenuBar* menubar = this->menuBar();

    this->setMenuBar(menubar);

    QMenu* menuParent = new QMenu("父菜单(&P)");

    QMenu* menuChild = new QMenu("子菜单(&C)");
    menuChild->setIcon(QIcon(":/res/9890.png"));

    menubar->addMenu(menuParent);
    menuParent->addMenu(menuChild);

    QAction* action1 = new QAction("action1 (&F)");
    action1->setIcon(QIcon(":/res/7767.png"));
    QAction* action2 = new QAction("action22 (&Q");
    action2->setIcon(QIcon(":/res/36469.png"));
    menuChild->addAction(action1);
    menuChild->addSeparator();
    menuChild->addAction(action2);

    QToolBar* toolBar =new QToolBar();
    this->addToolBar(toolBar);

}

MainWindow::~MainWindow()
{
    delete ui;
}

