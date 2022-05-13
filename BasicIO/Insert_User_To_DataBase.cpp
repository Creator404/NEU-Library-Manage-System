#include "Insert_User_To_DataBase.h"
QSqlDatabase Insert_User_DB;

int Insert_User_Command(QString id,QString password,QString RealName,int UserLevel,QString EmailBox)
{
    QSqlQuery query;
    QString Insert_Com = QString("INSERT INTO userinfo(User_Id, User_Password, User_Realname, User_Rank, User_AlreadyBorrowedBook, User_MaxBorrowedBook, User_MoneyLeft, User_Status, User_EmailBox) VALUES ('");
    Insert_Com += (id + "','" + password + "','" + RealName + "'," + QString::number(UserLevel,10) + ",0," + QString::number(5*UserLevel,10) + "," + QString::number(200*UserLevel) + ",1,'"+ EmailBox + "');");
    if(query.exec(Insert_Com)){
        return 1;
    }
    else{
        return 0;
    }
}
