#include "Read_Record_By_ISBN.h"

void Read_Record_By_ISBN(QSqlQuery &Query, QString ISBN,QString Userid)
{
    QString ExecSentence;
    ExecSentence = "SELECT * FROM record where `isbn` = '" + ISBN + "' and `userid` = '" + Userid + "' and `status` = 0";
    qDebug()<<ExecSentence<<endl;
    Query.exec(ExecSentence);
    return;
}
