#include "mainwindow.h"

#include <QApplication>
#include <mysql/jdbc.h>
int main(int argc, char *argv[])
{
    sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
