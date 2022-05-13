#include "Insert_Book_To_DataBase.h"

int Insert_Book_Command(QString Name,QString Writer,QString Publisher,QString ISBN,QString Memo,float price,int totNum,int IfGenerateFromDataBase)
{
    QSqlQuery query;
    QString Insert_Com = QString("INSERT INTO mylibrary(`BookName`, `ISBN`, `Author`, `Publisher`, `Price`, `Memo`, `TotNum`, `AlreadyBorrowedNum`, `TotBorrowedNum`, `status`, `ifGenerateFromDataBase`) VALUES ('");
    Insert_Com += (Name + "','" + ISBN + "','" + Writer + "','" + Publisher + "'," + QString::number(price) + ",'" + Memo + "',"+ QString::number(totNum) + ",0,0,1," + QString::number(IfGenerateFromDataBase) +");");
    if(query.exec(Insert_Com)){
        return 1;
    }
    else{
        return 0;
    }
}
