#include "DataBase_Initial.h"
#include <QMessageBox>
#include <QApplication>
#include <cstdio>

//初始化书籍ISBN库（大数据集）
void InitialMyLibrary(QSqlDatabase &DataBase, QApplication &a)
{
    DataBase = QSqlDatabase::addDatabase("QODBC");
    DataBase.setHostName("localhost");
    DataBase.setDatabaseName("Library_Data");
    DataBase.setUserName("root");
    DataBase.setPort(3306);
    DataBase.setPassword("zsw2001020109");
    if(!DataBase.open()){
        QMessageBox::warning(NULL,QObject::tr("Warning"),QObject::tr("数据库初始化失败，致命错误，请修复后重新打开。"),QMessageBox::Yes);
        QApplication *app = &a;
        app->exit(0);
    }
    //QMessageBox::warning(NULL,QObject::tr("Warning"),QObject::tr("数据库初始化成功。"),QMessageBox::Yes);
}

void Initial_Internet_MyLibrary(QSqlDatabase &DataBase, QApplication &a)
{
    DataBase = QSqlDatabase::addDatabase("QODBC");
    DataBase.setHostName("123");
    DataBase.setDatabaseName("Libdb");
    DataBase.setUserName("root");
    DataBase.setPort(31647);
    DataBase.setPassword("123");
    if(!DataBase.open()){
        QMessageBox::warning(NULL,QObject::tr("Warning"),QObject::tr("数据库初始化失败，致命错误，请修复后重新打开。"),QMessageBox::Yes);
        QApplication *app = &a;
        app->exit(0);
    }


    //QMessageBox::warning(NULL,QObject::tr("Warning"),QObject::tr("数据库初始化成功。"),QMessageBox::Yes);
}
