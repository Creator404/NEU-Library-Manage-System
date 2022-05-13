#include "admin_widget.h"
#include "ui_admin_widget.h"
#include <QTableWidgetItem>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include "DataStructure/Book.h"
#include "Function/Free_Function.h"
#include "BasicIO/Read_Book_From_MyLibrary.h"
#include "BasicIO/Read_User_From_DataBase.h"
#include "Function/Check_Functions.h"
#include <QFileDialog>
#include <stdlib.h>
#include <stdio.h>
#include <direct.h>
#include <QDebug>
#include <QFileDialog>
#include <QProgressDialog>
#include <conio.h>
#include <iostream>

admin_widget::admin_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_widget)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->User_Info_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->Borrow_Return_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(&Change_Book_Info,SIGNAL(If_Changed_Info(int)),this,SLOT(Update_Book_Specific_Row(int)));
    connect(&Add_Book,SIGNAL(UpdateFull()),this,SLOT(Update_Full_Message()));
    connect(&Change_User_Info,SIGNAL(If_Changed_Info(int)),this,SLOT(Update_User_Specific_Row(int)));
    setWindowTitle("管理员界面");
}

admin_widget::~admin_widget()
{
    delete ui;
}

void admin_widget::on_Log_Out_clicked()
{
    emit Show_Father_Widget();
    this->close();
}

void admin_widget::on_Add_Book_clicked()
{
    Add_Book.show();
}

void admin_widget::Update_Full_Message()
{
    QSqlQuery Query;
    QString ExecSentence,name,author,publisher,isbn;
    float price;
    int size;
    QSqlRecord rec;
    int TotBookNum,AlreadyBorrowedNum,TotBorrowedNum;
    int row = 0,col;

    //处理第一个tablewidget（书籍信息）
    ExecSentence  = "SELECT * FROM mylibrary WHERE `status` = 1;";
    Query.exec(ExecSentence);
    size = Query.numRowsAffected();
    ui->tableWidget->setRowCount(size);
    qDebug()<<"First size is:"<<size<<endl;
    row = 0;
    while(Query.next()){
        col = 0;
        rec = Query.record();
        name = rec.value("BookName").toString();
        author = rec.value("Author").toString();
        isbn = rec.value("ISBN").toString();
        publisher = rec.value("Publisher").toString();
        price = rec.value("Price").toFloat();
        TotBookNum = rec.value("TotNum").toInt();
        AlreadyBorrowedNum = rec.value("AlreadyBorrowedNum").toInt();
        TotBorrowedNum = rec.value("TotBorrowedNum").toInt();
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(name));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(author));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(isbn));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(publisher));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(TotBookNum)));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(AlreadyBorrowedNum)));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(TotBookNum-AlreadyBorrowedNum)));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(price,'f',2)));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(TotBorrowedNum)));
        row++;
    };

    //处理第二个tablewidget（用户信息）
    QString id,realname,mailbox;
    int rank,ABB,MBB;
    float money;

    ExecSentence  = "SELECT * FROM userinfo WHERE `User_Status` = 1;";
    Query.exec(ExecSentence);
    size = Query.numRowsAffected();
    ui->User_Info_table->setRowCount(size);
    qDebug()<<"Second size is:"<<size<<endl;
    row = 0;
    while(Query.next()){
        col = 0;
        rec = Query.record();
        id = rec.value("User_Id").toString();
        realname = rec.value("User_Realname").toString();
        rank = rec.value("User_Rank").toInt();
        ABB = rec.value("User_AlreadyBorrowedBook").toInt();
        MBB = rank * 5;
        money = rec.value("User_MoneyLeft").toFloat();
        mailbox = rec.value("User_EmailBox").toString();
        ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(id));
        ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(realname));
        ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(QString::number(rank)));
        ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(QString::number(ABB)));
        ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(QString::number(MBB)));
        ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(QString::number(money,'f',2)));
        ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(mailbox));
        row++;
    };
}

void admin_widget::Update_Full_Record_Message()
{
    QSqlQuery Query;
    QString ExecSentence,userid,isbn,name,start_date,end_date;
    int size,status;
    QSqlRecord rec;
    int row = 0,col;

    //处理第一个tablewidget（书籍信息）
    ExecSentence  = "SELECT * FROM record order by `index` DESC;";
    qDebug()<<ExecSentence<<endl;

    Query.exec(ExecSentence);
    size = Query.numRowsAffected();
    ui->Borrow_Return_table->setRowCount(size);
    qDebug()<<"Second size is:"<<size<<endl;
    row = 0;
    while(Query.next()){
        col = 0;
        rec = Query.record();
        userid = rec.value("userid").toString();
        isbn = rec.value("isbn").toString();
        name = rec.value("name").toString();
        start_date = rec.value("start_date").toString();
        end_date = rec.value("end_date").toString();
        status = rec.value("status").toInt();
        qDebug()<<isbn<<" "<<name<<" "<<start_date<<" "<<end_date<<" "<<status<<endl;
        ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem(userid));
        ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem(isbn));
        ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem(name));
        ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem(start_date));
        ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem(end_date));
        if(status){
            ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem("已归还"));
        }
        else{
            ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem("未归还"));
        }
        row++;
    };
}

void admin_widget::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QString isbn = ui->tableWidget->item(row,2)->text().toUtf8().data();
    Book *Head = Read_Book_Info_By_ISBN_From_Mylibrary(isbn,0);
    if(!Head){
        QMessageBox::warning(NULL,QObject::tr("Warning"),QObject::tr("致命错误，并没有获取到该书数据，请重试。"),QMessageBox::Yes);
        return;
    }
    Change_Book_Info.Get_Info(Head->name,Head->writer,Head->publisher,Head->memo,Head->ISBNcode,Head->price,Head->TotBookNum,Head->AlreadyBorrowedNum,Head->ifGenerateFromDataBase);
    Delete_Book_LinkList(Head);
    Change_Book_Info.instance_rowNum = row;
    Change_Book_Info.show();
}

void admin_widget::on_User_Info_table_cellDoubleClicked(int row, int column)
{
    QString id = ui->User_Info_table->item(row,0)->text().toUtf8().data();
    qDebug()<<id<<endl;
    User *Head = Read_User_Info_By_ID(id,0);
    Head->show();
    if(!Head){
        QMessageBox::warning(NULL,QObject::tr("Warning"),QObject::tr("致命错误，并没有获取到该用户数据，请重试。"),QMessageBox::Yes);
        return;
    }
    Change_User_Info.Get_Info(Head->UserId,Head->password,Head->name,Head->UserLevel,Head->money,Head->mailbox);
    Delete_User_LinkList(Head);
    Change_User_Info.instance_rowNum = row;
    Change_User_Info.show();
}

void admin_widget::Update_Book_Specific_Row(int row)
{
    QString ISBN = ui->tableWidget->item(row,2)->text().toUtf8().data();
    Book *Head = Read_Book_Info_By_ISBN_From_Mylibrary(ISBN,0);
    if(!Head->status){
        ui->tableWidget->removeRow(row);
        return;
    }
    int col = 0;
    ui->tableWidget->setItem(row,col++,new QTableWidgetItem(Head->name));
    ui->tableWidget->setItem(row,col++,new QTableWidgetItem(Head->writer));
    ui->tableWidget->setItem(row,col++,new QTableWidgetItem(Head->ISBNcode));
    ui->tableWidget->setItem(row,col++,new QTableWidgetItem(Head->publisher));
    ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(Head->TotBookNum)));
    ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(Head->AlreadyBorrowedNum)));
    ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(Head->TotBookNum-Head->AlreadyBorrowedNum)));
    ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(Head->price,'f',2)));
    ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(Head->TotBorrowedNum)));
    Delete_Book_LinkList(Head);
}

void admin_widget::Update_User_Specific_Row(int row)
{
    QString id = ui->User_Info_table->item(row,0)->text().toUtf8().data();
    User *Head = Read_User_Info_By_ID(id,0);
    if(!Head->status){
        ui->User_Info_table->removeRow(row);
        return;
    }
    int col = 0;
    ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(Head->UserId));
    ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(Head->name));
    ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(QString::number(Head->UserLevel)));
    ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(QString::number(Head->AlreadyBorrowedBook)));
    ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(QString::number(Head->MaxBorrowedBook)));
    ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(QString::number(Head->money,'f',2)));
    ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(Head->mailbox));
    Delete_User_LinkList(Head);
}

void admin_widget::on_Search_clicked()
{
    QSqlQuery Query;
    QString ExecSentence,name,author,publisher,isbn;
    float price;
    int TotBookNum,AlreadyBorrowedNum,TotBorrowedNum;
    QSqlRecord rec;
    int OrderType = ui->BookOrderType->currentIndex();
    name = ui->BookName->text().toUtf8().data();
    isbn = ui->ISBNCode->text().toUtf8().data();
    author = ui->Writer->text().toUtf8().data();
    publisher = ui->Publisher->text().toUtf8().data();
    if(!(name != "" || isbn != "" || author != "" || publisher != "")){
        Update_Full_Message();
        return;
    }

    //处理接下来需要上传的数据
    int size;
    if(!Combine_Check_Book_Illegal_Input(name,isbn,author,publisher)){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入有不合法的内容，通常是与sql注入有关，请重新确认后再进行插入（如',\"等符号是不被允许的）。"),QMessageBox::Yes);
        return;
    }
    ExecSentence  = "SELECT * FROM mylibrary WHERE `status` = 1 ";
    if(name != ""){
        ExecSentence += "and ";
        ExecSentence += "`BookName` like '%" + name + "%'";
    }
    if(isbn != ""){
        ExecSentence += " and ";
        ExecSentence += "`ISBN` = '" + isbn + "'";
    }
    if(author != ""){
        ExecSentence += " and ";
        ExecSentence += "`Author` like '%" + author + "%'";
    }
    if(publisher != ""){
        ExecSentence += " and ";
        ExecSentence += "`Publisher` like '%" + publisher + "%'";
    }

    if(OrderType <= 1){
        ExecSentence += " order by `TotBorrowedNum` ";
    }
    else{
        ExecSentence += " order by (`TotNum` - `AlreadyBorrowedNum`) ";
    }

    if(OrderType % 2 == 1){
        ExecSentence += "ASC;";
    }
    else{
        ExecSentence += "DESC;";
    }

    qDebug()<<ExecSentence<<endl;

    Query.exec(ExecSentence);
    size = Query.numRowsAffected();
    ui->tableWidget->setRowCount(size);
    qDebug()<<"After Search Size is:"<<size<<endl;
    int row = 0,col = 0;
    while(Query.next()){
        col = 0;
        rec = Query.record();
        name = rec.value("BookName").toString();
        author = rec.value("Author").toString();
        isbn = rec.value("ISBN").toString();
        publisher = rec.value("Publisher").toString();
        price = rec.value("Price").toFloat();
        TotBookNum = rec.value("TotNum").toInt();
        AlreadyBorrowedNum = rec.value("AlreadyBorrowedNum").toInt();
        TotBorrowedNum = rec.value("TotBorrowedNum").toInt();
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(name));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(author));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(isbn));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(publisher));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(TotBookNum)));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(AlreadyBorrowedNum)));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(TotBookNum-AlreadyBorrowedNum)));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(price,'f',2)));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(TotBorrowedNum)));
        row++;
    };
    return;
}

void admin_widget::on_Search_UserInfo_clicked()
{
    QSqlQuery Query;
    QString ExecSentence,UserId,RealName,Email;
    QSqlRecord rec;
    int OrderType = ui->BookOrderType->currentIndex();
    UserId = ui->UserId->text().toUtf8().data();
    RealName = ui->RealName->text().toUtf8().data();
    Email = ui->Email->text().toUtf8().data();
    if(!(UserId != "" || RealName != "" || Email != "")){
        Update_Full_Message();
        return;
    }

    //处理接下来需要上传的数据
    int size;
    if(!Combine_Check_Book_Illegal_Input(UserId,RealName)){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入有不合法的内容，通常是与sql注入有关，请重新确认后再进行插入（如',\"等符号是不被允许的）。"),QMessageBox::Yes);
        return;
    }
    if(!Check_EmailBox_Input(Email)){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入不为支持的邮箱类型。（目前仅支持126，163，qq）"),QMessageBox::Yes);
        return;
    }
    ExecSentence  = "SELECT * FROM userinfo WHERE `User_Status` = 1 ";
    if(UserId != ""){
        ExecSentence += "and ";
        ExecSentence += "`User_Id` like '%" + UserId + "%'";
    }
    if(RealName != ""){
        ExecSentence += " and ";
        ExecSentence += "`User_Realname` like '%" + RealName + "%'";
    }
    if(Email != ""){
        ExecSentence += " and ";
        ExecSentence += "`User_EmailBox` = '" + Email + "'";
    }
    if(OrderType <= 1){
        ExecSentence += " order by `User_Rank` ";
    }
    else{
        ExecSentence += " order by `User_MoneyLeft` ";
    }

    if(OrderType % 2 == 1){
        ExecSentence += "ASC;";
    }
    else{
        ExecSentence += "DESC;";
    }

    qDebug()<<ExecSentence<<endl;

    Query.exec(ExecSentence);
    size = Query.numRowsAffected();
    ui->User_Info_table->setRowCount(size);
    qDebug()<<"Second size is:"<<size<<endl;
    int row = 0,col;
    int rank,ABB,MBB;
    float money;
    while(Query.next()){
        col = 0;
        rec = Query.record();
        UserId = rec.value("User_Id").toString();
        RealName = rec.value("User_Realname").toString();
        rank = rec.value("User_Rank").toInt();
        ABB = rec.value("User_AlreadyBorrowedBook").toInt();
        MBB = rank * 5;
        money = rec.value("User_MoneyLeft").toFloat();
        Email = rec.value("User_EmailBox").toString();
        ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(UserId));
        ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(RealName));
        ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(QString::number(rank)));
        ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(QString::number(ABB)));
        ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(QString::number(MBB)));
        ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(QString::number(money,'f',2)));
        ui->User_Info_table->setItem(row,col++,new QTableWidgetItem(Email));
        row++;
    };
    return;
}

void admin_widget::on_PaintGraph_clicked()
{
    BCW.GenerateChart();
    BCW.show();
}

void admin_widget::on_Search_RecordInfo_clicked()
{
    QSqlQuery Query;
    QString ExecSentence,UserId,ISBN,BookName;
    QSqlRecord rec;
    UserId = ui->UserId_Record->text().toUtf8().data();
    ISBN = ui->ISBN_Record->text().toUtf8().data();
    BookName = ui->BookName_Record->text().toUtf8().data();
    if(!(UserId != "" || ISBN != "" || BookName != "")){
        Update_Full_Record_Message();
        return;
    }

    //处理接下来需要上传的数据
    int size;
    if(!Combine_Check_Book_Illegal_Input(UserId,ISBN,BookName)){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入有不合法的内容，通常是与sql注入有关，请重新确认后再进行插入（如',\"等符号是不被允许的）。"),QMessageBox::Yes);
        return;
    }
    ExecSentence  = "SELECT * FROM record WHERE ";
    int flag = 0;
    if(UserId != ""){
        ExecSentence += "`userid` like '%" + UserId + "%'";
        flag = 1;
    }
    if(ISBN != ""){
        if(flag){
            ExecSentence += " and ";
        }
        ExecSentence += "`isbn` = '" + ISBN + "'";
        flag = 1;
    }
    if(BookName != ""){
        if(flag){
            ExecSentence += " and ";
        }
        ExecSentence += "`name` = '" + BookName + "'";
    }
    if(ui->RecordOrderType->currentIndex()){
        ExecSentence += " order by `isbn` DESC,`index` DESC;";
    }
    else{
        ExecSentence += " order by `index` DESC,`isbn` DESC;";
    }
    qDebug()<<ExecSentence<<endl;

    Query.exec(ExecSentence);
    size = Query.numRowsAffected();
    ui->Borrow_Return_table->setRowCount(size);
    qDebug()<<"Second size is:"<<size<<endl;
    int row = 0,col,status;
    QString start_date,end_date;
    while(Query.next()){
        col = 0;
        rec = Query.record();
        UserId = rec.value("userid").toString();
        ISBN = rec.value("isbn").toString();
        BookName = rec.value("name").toString();
        start_date = rec.value("start_date").toString();
        end_date = rec.value("end_date").toString();
        status = rec.value("status").toInt();
        ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem(UserId));
        ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem(ISBN));
        ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem(BookName));
        ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem(start_date));
        ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem(end_date));
        if(status){
            ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem("已归还"));
        }
        else{
            ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem("未归还"));
        }
        row++;
    };
    return;
}
