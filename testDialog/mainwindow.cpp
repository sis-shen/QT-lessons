#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QColorDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_dialogButton_clicked()
{
    static QDialog* dialog = new QDialog(this);
    dialog->resize(400,300);
    dialog->setWindowTitle("这是一个标题");
    dialog->show();
}

void MainWindow::on_pushButton_clicked()
{
    QColor color = QColorDialog::getColor(QColor(255,255,255),this,"选择颜色");
    qDebug()<<color;
    //设置背景色
    QString style = "background-color: rgb(" + QString::number(color.red()) + "," +
                QString::number(color.green()) + "," + QString::number(color.blue()) + ");";
    this->setStyleSheet(style);
}
