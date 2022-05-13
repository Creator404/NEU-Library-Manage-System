#ifndef BOOK_H
#define BOOK_H

#include <cstring>
#include <QString>

//一个简单的Book类，用来处理Mysql返回的数据
class Book{
public:
    QString name;
    QString writer;
    QString publisher;
    int TotBookNum;
    int AlreadyBorrowedNum;
    QString ISBNcode;
    int TotBorrowedNum;
    int status;//0为删除，1为正常
    int ifGenerateFromDataBase;//1为从isbn库中生成
    float price;
    QString memo;
    Book* next;
    Book() {}
    Book(QString nam,QString writ,QString pub,int TotBN,QString ISBN,float pric, QString Me){
        ifGenerateFromDataBase = 0;
        name = nam;
        writer = writ;
        publisher = pub;
        TotBookNum = TotBN;
        AlreadyBorrowedNum = 0;
        ISBNcode = ISBN;
        TotBorrowedNum = 0;
        status = 1;
        price = pric;
        memo = Me;
        next = NULL;
    }
    Book(QString nam,QString writ,QString pub,int TotBN,QString ISBN,float pric, QString Me,int ifGenrate,int Tot,int Alread,bool stat){
        ifGenerateFromDataBase = ifGenrate;
        name = nam;
        writer = writ;
        publisher = pub;
        TotBookNum = TotBN;
        AlreadyBorrowedNum = Alread;
        ISBNcode = ISBN;
        TotBorrowedNum = Tot;
        status = stat;
        price = pric;
        memo = Me;
        next = NULL;
    }
    ~Book() {}
};

void Initial_Book_LinkList(Book* &Head);

#endif // BOOK_H
