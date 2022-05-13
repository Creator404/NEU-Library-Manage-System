#ifndef READ_USER_FROM_DATABASE_H
#define READ_USER_FROM_DATABASE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include "DataStructure/User.h"

User* Read_User_Info_By_ID(QString id,int mode);//0为精确查询，1为模糊查询,2为检验是否已经存在
QString Read_User_Info_By_RealName(QString name,int mode);//0为精确查询，1为模糊查询
int Check_User_Info_By_EmailBox(QString EmailBox);//仅支持精确查询,0为未被绑定，1为已经被绑定

#endif // READ_USER_FROM_DATABASE_H
