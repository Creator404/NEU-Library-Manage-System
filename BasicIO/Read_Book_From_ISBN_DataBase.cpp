#include "Read_Book_From_ISBN_DataBase.h"

Book* Read_Book_Info_By_ISBN_From_ISBNDataBase(QString ISBN,int mode)//0为精确查询，1为模糊查询
{
    QSqlQuery Query;
    QString ExecSentence;
    if(mode == 1){
       ExecSentence  = "SELECT * FROM booklibrary WHERE isbn like '%";
       ExecSentence += ISBN;
       ExecSentence += "%';";
    }
    else{
       ExecSentence  = "SELECT * FROM booklibrary WHERE isbn = '";
       ExecSentence += ISBN;
       ExecSentence += "';";
    }
    Book *Head = NULL,**Instance = NULL;
    Instance = &Head;

    Query.exec(ExecSentence);
    QSqlRecord rec;
    while(Query.next()){
        rec = Query.record();
        QString name = rec.value("name").toString();
        QString author = rec.value("author").toString();
        QString memo = rec.value("memo").toString();
        QString publisher = rec.value("publisher").toString();
        float price = rec.value("price").toFloat();
        (*Instance) = new Book(name,author,publisher,0,ISBN,price,memo);
        Instance = &((*Instance)->next);
    };
    return Head;
}
