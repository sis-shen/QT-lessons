#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QWidget>
#include <QDialog>
#include "VendingMachine.h"
#include <QValidator>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QSpinBox>
#include <QLabel>
#include <QStyle>

class AddItemDialog : public QDialog
{
    Q_OBJECT


private slots:
    void TrySubmit();

public:
    AddItemDialog();
    void Reset();

    QLineEdit* edit_name;
    QLineEdit* edit_price;
    QSpinBox* edit_cnt;

    QPushButton* submit;
    Item _item;
};

#endif // ADDITEMDIALOG_H
