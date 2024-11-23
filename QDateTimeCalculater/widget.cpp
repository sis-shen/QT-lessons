#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->horizontalSlider->setMinimum(100);
    ui->horizontalSlider->setMaximum(1000);
    ui->horizontalSlider->setSingleStep(50);
    ui->horizontalSlider->setValue(800);
    ui->verticalSlider->setMinimum(100);
    ui->verticalSlider->setMaximum(1500);
    ui->verticalSlider->setSingleStep(50);
    ui->verticalSlider->setValue(600);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    QDateTime timeOld = ui->dateTimeEdit->dateTime();
    QDateTime timeNew = ui->dateTimeEdit_2->dateTime();
    qDebug()<<timeOld<<timeNew;
    int days = timeOld.daysTo(timeNew);
    int seconds = timeOld.secsTo(timeNew);

//    int hours = (seconds/3600) %24;
//    int mins = (seconds / 60)%60;
//    int secs = seconds % 60;
    qDebug()<<days;
}



void Widget::on_horizontalSlider_valueChanged(int value)
{
    const QRect& rect = this->geometry();
    this->setGeometry(rect.x(),rect.y(),value,rect.height());
}

void Widget::on_verticalSlider_valueChanged(int value)
{
    const QRect& rect = this->geometry();
    this->setGeometry(rect.x(),rect.y(),rect.width(),value);
}

void Widget::on_horizontalSlider_sliderMoved(int position)
{
    ;
}
