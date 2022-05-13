#include "Applications/login_widget.h"
#include "Initialize/DataBase_Initial.h"
#include <QtSql/QSqlDatabase>
#include <QApplication>
#include <QDebug>
#include <QSqlError>
#include "BasicIO/Read_User_From_DataBase.h"
#include "Function/Get_ISBN_From_Camera.h"

QSqlDatabase My_Library_Data;//我当前的图书馆的数据库

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InitialMyLibrary(My_Library_Data, a);
    //Initial_Internet_MyLibrary(My_Library_Data);
    Login_Widget Login;
    Login.show();
    return a.exec();
}
