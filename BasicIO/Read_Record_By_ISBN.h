#ifndef READ_RECORD_BY_ISBN_H
#define READ_RECORD_BY_ISBN_H

#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include "DataStructure/Book.h"

void Read_Record_By_ISBN(QSqlQuery &Query, QString ISBN,QString Userid);

#endif // READ_RECORD_BY_ISBN_H
