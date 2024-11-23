#ifndef CHARGEDIALOG_H
#define CHARGEDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QDoubleValidator>
class ChargeDialog : public QDialog
{
    Q_OBJECT

private slots:
    void GetMoney();

public:
    ChargeDialog();

    QLineEdit* edit;
    QPushButton* submit;

    double _money;
};

#endif // CHARGEDIALOG_H
