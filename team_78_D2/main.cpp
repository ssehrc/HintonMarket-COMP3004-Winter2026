#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug() << "Using DB file:" << db.databaseName();
    db.setDatabaseName("marketplace.db");
    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return -1; 
    }
    MainWindow w;
    w.show();
    return a.exec();
}
