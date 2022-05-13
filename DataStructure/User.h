#ifndef USER_H
#define USER_H

#include <cstring>
#include <QString>
#include <QDebug>

//一个简单的User类，用来处理Mysql返回的数据
class People{
public:
    QString UserId;
    QString password;
    QString name;
    QString mailbox;
    virtual void show() = 0;
    People(){}
    ~People(){}
};

class User:public People{
public:
//    QString UserId;//用户名
//    QString password;//密码
//    QString name;//用户真实姓名
//    QString mailbox;
    int UserLevel;//用户等级(1-3)
    int AlreadyBorrowedBook;//已经借阅的书目
    int MaxBorrowedBook;//最大借阅书目（用户等级*5）
    float money;//用户余额(注册时需要提交200*用户等级的押金)
    int status;//0为删除，1为正常，2为锁定
    User* next;
    User(){}
    User(QString id, QString pass, QString nam, int UserL){
        UserId = id;
        password = pass;
        name = nam;
        UserLevel = UserL;
        AlreadyBorrowedBook = 0;
        MaxBorrowedBook = 5 * UserL;
        money = 200 * UserL;
        status = 1;
        next = NULL;
    }
    User(QString id, QString pass, QString nam, int UserL, int ABB, float Moy,int stat){
        UserId = id;
        password = pass;
        name = nam;
        UserLevel = UserL;
        AlreadyBorrowedBook = ABB;
        MaxBorrowedBook = 5 * UserL;
        money = Moy;
        status = stat;
        next = NULL;
    }
    User(QString id, QString pass, QString nam, int UserL, int ABB, float Moy,int stat,QString Mailbox){
        UserId = id;
        password = pass;
        name = nam;
        UserLevel = UserL;
        AlreadyBorrowedBook = ABB;
        MaxBorrowedBook = 5 * UserL;
        money = Moy;
        status = stat;
        next = NULL;
        mailbox = Mailbox;
    }
    ~User(){}
    void show(){
        qDebug()<<"UserId:"<<UserId<<"\nPassword:"<<password<<"\nName:"<<name<<"\nMailbox:"<<mailbox<<"\nUserLevel:"<<UserLevel<<endl;
    }
};

class StuffUser:public People{
public:
//    QString UserId;//用户名
//    QString password;//密码
//    QString name;//用户真实姓名
//    QString mailbox;
    int AlreadyBorrowedBook;//已经借阅的书目
    int MaxBorrowedBook;//最大借阅书目（用户等级*5）
    float money;//用户余额(注册时需要提交200*用户等级的押金)
    int status;//0为删除，1为正常，2为锁定
    StuffUser* next;
    StuffUser(){}
    StuffUser(QString id){
        UserId = id;
    }
    StuffUser(QString id, QString pass, QString nam){
        UserId = id;
        password = pass;
        name = nam;
        AlreadyBorrowedBook = 0;
        MaxBorrowedBook = 20;
        money = 20000;
        status = 1;
        next = NULL;
    }
    StuffUser(QString id, QString pass, QString nam, int ABB, float Moy,int stat){
        UserId = id;
        password = pass;
        name = nam;
        AlreadyBorrowedBook = ABB;
        MaxBorrowedBook = 20;
        money = Moy;
        status = stat;
        next = NULL;
    }
    StuffUser(QString id, QString pass, QString nam, int ABB, float Moy,int stat,QString Mailbox){
        UserId = id;
        password = pass;
        name = nam;
        AlreadyBorrowedBook = ABB;
        MaxBorrowedBook = 20;
        money = Moy;
        status = stat;
        next = NULL;
        mailbox = Mailbox;
    }
    ~StuffUser(){}
    void show(){
        qDebug()<<"UserId:"<<UserId<<"\nPassword:"<<password<<"\nName:"<<name<<"\nMailbox:"<<mailbox<<endl;
    }
    void ExtendDate();
};

void Initial_User_LinkList(User* &Head);

#endif // USER_H
