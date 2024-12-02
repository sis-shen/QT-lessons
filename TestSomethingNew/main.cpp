#include "mainwindow.h"

#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // QStringList drivers = QSqlDatabase::drivers();
    // qDebug() << "Loaded SQL drivers:";

    // // 输出每个驱动的名称
    // foreach (const QString &driver, drivers) {
    //     qDebug() << driver;
    // }
    qDebug() << QSqlDatabase::drivers();
    // 设置数据库文件路径
    QSqlDatabase db =  QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("Qt");
    db.setHostName("47.99.48.121");
    db.setPassword("12345678");
    db.setUserName("QTUser");

    // 尝试打开数据库连接

    if (!db.open()) {
        qDebug() << "Error: Could not open database";
        return -1;
    }

    qDebug() << "Database connected successfully";


    // 关闭数据库连接
    db.close();

    MainWindow w;
    w.show();
    return a.exec();
}
