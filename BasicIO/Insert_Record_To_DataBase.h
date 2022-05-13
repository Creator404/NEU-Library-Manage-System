#ifndef INSERT_RECORD_TO_DATABASE_H
#define INSERT_RECORD_TO_DATABASE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

int Insert_Record_Command(QString UserId,QString ISBN,QString BookName);

#endif // INSERT_RECORD_TO_DATABASE_H
