#ifndef INSERT_BOOK_TO_DATABASE_H
#define INSERT_BOOK_TO_DATABASE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

int Insert_Book_Command(QString Name,QString Writer,QString Publisher,QString ISBN,QString Memo,float price,int totNum,int IfGenerateFromDataBase);

#endif // INSERT_BOOK_TO_DATABASE_H
