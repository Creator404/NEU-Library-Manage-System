#include "Insert_Record_To_DataBase.h"
#include <QDateTime>

int Insert_Record_Command(QString UserId,QString ISBN,QString BookName)
{
    QSqlQuery query;
    QString Insert_Com = QString("INSERT INTO record(`userid`,`isbn`,`name`,`start_date`,`end_date`,`status`) VALUES ('");
    QDateTime TimeNow = QDateTime::currentDateTime();
    qDebug()<<TimeNow<<endl;
    QString StartTime = TimeNow.toString("yyyyMMdd");
    qDebug()<<StartTime<<"    "<<TimeNow<<endl;
    QString EndTime = TimeNow.addDays(20).toString("yyyyMMdd");
    Insert_Com += (UserId + "','" + ISBN + "','" + BookName + "','" + StartTime + "','" + EndTime + "',0);");
    qDebug()<<Insert_Com<<endl;
    if(query.exec(Insert_Com)){
        return 1;
    }
    else{
        return 0;
    }
}
