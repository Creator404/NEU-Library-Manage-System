#ifndef INSERT_USER_TO_DATABASE_H
#define INSERT_USER_TO_DATABASE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include "Initialize/DataBase_Initial.h"

int Insert_User_Command(QString id,QString password,QString RealName,int UserLevel,QString EmailBox);

#endif // INSERT_USER_TO_DATABASE_H
