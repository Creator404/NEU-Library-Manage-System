#include "Read_User_From_DataBase.h"
#include "Initialize/DataBase_Initial.h"


User* Read_User_Info_By_ID(QString id,int mode)//0为精确查询，1为模糊查询
{
    QSqlQuery Query;
    QString ExecSentence;
    if(mode == 1){
       ExecSentence  = "SELECT * FROM userinfo WHERE User_Id like '%";
       ExecSentence += id;
       ExecSentence += "%';";
    }
    else{
       ExecSentence  = "SELECT * FROM userinfo WHERE User_Id = '";
       ExecSentence += id;
       ExecSentence += "';";
    }
    User *Head = NULL,**Instance = NULL;
    Instance = &Head;

    Query.exec(ExecSentence);
    QSqlRecord rec;
    while(Query.next()){
        rec = Query.record();
        QString id = rec.value(0).toString();
        QString password = rec.value(1).toString();
        QString realname = rec.value(2).toString();
        int Rank = rec.value(3).toInt();
        int AlreadyBorrowedBook = rec.value(4).toInt();
        float MoneyLeft = rec.value(6).toFloat();
        int status = rec.value(7).toInt();
        QString mailbox = rec.value(8).toString();
        (*Instance) = new User(id,password,realname,Rank,AlreadyBorrowedBook,MoneyLeft,status,mailbox);
        Instance = &((*Instance)->next);
    };
    return Head;
}

int Check_User_Info_By_EmailBox(QString EmailBox)//仅支持精确查询
{
    QSqlQuery Query;
    QString ExecSentence = "SELECT * FROM userinfo WHERE User_EmailBox = '";
    ExecSentence += EmailBox;
    ExecSentence += "';";
    Query.exec(ExecSentence);
    QSqlRecord rec;
    if(Query.next()){
        return 1;
    }
    return 0;
}
