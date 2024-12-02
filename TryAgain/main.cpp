#include "widget.h"

#include <QApplication>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlDriver>
#include <QStringList>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 获取所有数据库驱动
    QStringList drivers = QSqlDatabase::drivers();

    // 输出所有数据库驱动
    qDebug() << "Installed SQL drivers:";
    for (const QString &driver : drivers) {
        qDebug() << driver;
    }
    Widget w;
    w.show();
    return a.exec();
}
