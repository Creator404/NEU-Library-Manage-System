#ifndef READ_BOOK_FROM_MYLIBRARY_H
#define READ_BOOK_FROM_MYLIBRARY_H

#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include "DataStructure/Book.h"

Book* Read_Book_Info_By_ISBN_From_Mylibrary(QString ISBN,int mode);//0为精确查询，1为模糊查询

#endif // READ_BOOK_FROM_MYLIBRARY_H
