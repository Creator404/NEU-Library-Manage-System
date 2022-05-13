#include "Read_Book_From_MyLibrary.h"

Book* Read_Book_Info_By_ISBN_From_Mylibrary(QString ISBN,int mode)
{
    QSqlQuery Query;
    QString ExecSentence;
    if(mode == 1){
       ExecSentence  = "SELECT * FROM mylibrary WHERE isbn like '%";
       ExecSentence += ISBN;
       ExecSentence += "%';";
    }
    else{
       ExecSentence  = "SELECT * FROM mylibrary WHERE isbn = '";
       ExecSentence += ISBN;
       ExecSentence += "';";
    }
    Book *Head = NULL,**Instance = NULL;
    Instance = &Head;

    Query.exec(ExecSentence);
    QSqlRecord rec;
    while(Query.next()){
        rec = Query.record();
        QString name = rec.value("BookName").toString();
        QString author = rec.value("Author").toString();
        QString memo = rec.value("Memo").toString();
        QString publisher = rec.value("Publisher").toString();
        int TotBookNum = rec.value("TotNum").toInt();
        int IfGenerateFromDataBase = rec.value("ifGenerateFromDataBase").toInt();
        int TotBorrowedNum = rec.value("TotBorrowedNum").toInt();
        int AlreadyBorrowedNum = rec.value("AlreadyBorrowedNum").toInt();
        bool status = rec.value("status").toInt();
        float price = rec.value("Price").toFloat();
        (*Instance) = new Book(name,author,publisher,TotBookNum,ISBN,price,memo,IfGenerateFromDataBase,TotBorrowedNum,AlreadyBorrowedNum,status);
        Instance = &((*Instance)->next);
    };
    return Head;
}
