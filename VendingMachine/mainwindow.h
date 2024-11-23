#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include "VendingMachine.h"
#include "Client.h"
#include <QTableWidget>
#include <unordered_map>
#include <string>
#include <QHeaderView>
#include <QDebug>
#include <unordered_set>
#include <QMessageBox>
#include "additemdialog.h"

#include "chargedialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void SetMainLayout();
    void SetRightLayout();
    void SetRightUp();
    void SetRightDown();
    void SetLeft();


    void AutoInit();
    void AddItem(const Item& item);
    void UpdateCombo(const std::string&name);
    void UpdateTable(const std::string& name);
    void UpdateTable(const Item& item);

    void SetAllConnection();

private slots:
    void OpenChargeDialog();
    void UpdateMoney();
    void TryBuy();
    void TryAddItem();
    void ShowAddItemDialog();
    void ClearAddDialog();
private:
    Ui::MainWindow *ui;
    VendingMachine* _vend;
    Client* _client;

    QWidget* main_left;
    QWidget* main_right;
    QWidget* right_down;
    QWidget* right_up;
    QComboBox* combo;
    QPushButton* charge;
    QPushButton* money;
    QSpinBox* spin_num;

    QPushButton* buy;
    QPushButton* add_item;

    QTableWidget* item_table;

    ChargeDialog* charge_dialog;
    AddItemDialog* add_item_dialog;

    std::unordered_map<string,int> _name_to_row;
    std::unordered_set<string> _combo_set;
};
#endif // MAINWINDOW_H
