#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QPainter>
#include <QStylePainter>
#include <QStyleOption>
#include <QKeyEvent>
#include <QLayout>
#include <QDebug>

#include <QVector>

enum AtmState
{
    Authentication,
    Selection,
    Withdrawal,
    Deposit
};

#endif // COMMON_H
