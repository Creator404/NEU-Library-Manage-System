#include "add_book_widget.h"
#include "ui_add_book_widget.h"

#include "BasicIO/Read_Book_From_ISBN_DataBase.h"
#include "BasicIO/Insert_Book_To_DataBase.h"
#include "BasicIO/Read_Book_From_MyLibrary.h"

#include "DataStructure/Book.h"

#include "Get_ISBN_From_Camera.h"
#include "Free_Function.h"
#include "Check_Functions.h"

#include <QMessageBox>

Add_Book_Widget::Add_Book_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Add_Book_Widget)
{
    ui->setupUi(this);
    setWindowTitle("添加书籍");
    ui->Writer->setFocusPolicy(Qt::NoFocus);
    ui->NameOfBook->setFocusPolicy(Qt::NoFocus);
    ui->Publisher->setFocusPolicy(Qt::NoFocus);
    ui->ISBNcode->setFocusPolicy(Qt::NoFocus);
    ui->PriceOfBook->setFocusPolicy(Qt::NoFocus);
    ui->Memo->setFocusPolicy(Qt::NoFocus);
    ui->IfGenerateFromDataBase->setFocusPolicy(Qt::NoFocus);
    ui->Writer->setReadOnly(true);
    ui->NameOfBook->setReadOnly(true);
    ui->Publisher->setReadOnly(true);
    ui->ISBNcode->setReadOnly(true);
    ui->PriceOfBook->setReadOnly(true);
    ui->Memo->setReadOnly(true);
    ui->IfGenerateFromDataBase->setReadOnly(true);
}

Add_Book_Widget::~Add_Book_Widget()
{
    delete ui;
}

void Add_Book_Widget::on_ScanISBN_clicked()
{
    QString ISBN = GetISBNFromCamera();
    if(ISBN == ""){
        return;
    }
    Book *Head = Read_Book_Info_By_ISBN_From_ISBNDataBase(ISBN,0);
    if(Head){
        ui->NameOfBook->setText(Head->name);
        ui->Writer->setText(Head->writer);
        ui->Publisher->setText(Head->publisher);
        ui->ISBNcode->setText(ISBN);
        ui->PriceOfBook->setValue(Head->price);
        ui->Memo->setText(Head->memo);
        ui->IfGenerateFromDataBase->setText("1");
        Delete_Book_LinkList(Head);
    }
    else{
        ui->Writer->setFocusPolicy(Qt::StrongFocus);
        ui->NameOfBook->setFocusPolicy(Qt::StrongFocus);
        ui->Publisher->setFocusPolicy(Qt::StrongFocus);
        ui->PriceOfBook->setFocusPolicy(Qt::StrongFocus);
        ui->Memo->setFocusPolicy(Qt::StrongFocus);
        ui->Writer->setReadOnly(false);
        ui->NameOfBook->setReadOnly(false);
        ui->Publisher->setReadOnly(false);
        ui->PriceOfBook->setReadOnly(false);
        ui->Memo->setReadOnly(false);
        ui->ISBNcode->setText(ISBN);
        ui->IfGenerateFromDataBase->setText("0");
        ui->NameOfBook->clear();
        ui->Writer->clear();
        ui->Publisher->clear();
        ui->PriceOfBook->setValue(0);
        ui->Memo->clear();
        ui->BookNum->setValue(1);
    }
}

void Add_Book_Widget::on_Confirm_clicked()
{
    QString name,writer,publisher,isbn,memo;
    float price;
    int totnum,IfGenerateFromDataBase;
    if(!Get_Book_Info(ui,name,writer,publisher,isbn,memo,price,totnum,IfGenerateFromDataBase)){
        return;
    }
    if(!IfGenerateFromDataBase && !Combine_Check_Book_Illegal_Input(name,writer,publisher,memo)){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入有不合法的内容，通常是与sql注入有关，请重新确认后再进行插入（如',\"等符号是不被允许的）。"),QMessageBox::Yes);
        return;
    }
    Book *Head = Read_Book_Info_By_ISBN_From_Mylibrary(isbn,0);
    if(Head){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("该书已经在图书馆中，请勿重复插入。"),QMessageBox::Yes);
        Delete_Book_LinkList(Head);
        Set_Ui_Value_To_Default(ui);
        return;
    }
    if(Insert_Book_Command(name,writer,publisher,isbn,memo,price,totnum,IfGenerateFromDataBase)){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("书籍已经成功插入。"),QMessageBox::Yes);
        emit UpdateFull();
        Set_Ui_Value_To_Default(ui);
    }
    else{
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("插入失败，请重试。"),QMessageBox::Yes);
    }
}

void Add_Book_Widget::closeEvent(QCloseEvent *)
{
    ui->Writer->setFocusPolicy(Qt::NoFocus);
    ui->NameOfBook->setFocusPolicy(Qt::NoFocus);
    ui->Publisher->setFocusPolicy(Qt::NoFocus);
    ui->PriceOfBook->setFocusPolicy(Qt::NoFocus);
    ui->Memo->setFocusPolicy(Qt::NoFocus);
    ui->Writer->setReadOnly(true);
    ui->NameOfBook->setReadOnly(true);
    ui->Publisher->setReadOnly(true);
    ui->PriceOfBook->setReadOnly(true);
    ui->Memo->setReadOnly(true);
    Set_Ui_Value_To_Default(ui);
    emit UpdateFull();
}

int Get_Book_Info(Ui::Add_Book_Widget *ui,QString &Name,QString &Writer,QString &Publisher,QString &ISBN,QString &Memo,float &price,int &totNum,int &IfGenerateFromDataBase)
{
    if(ui->NameOfBook->text().isEmpty()){
        ui->NameOfBook->setFocus();
        return 0;
    }
    if(ui->Writer->text().isEmpty()){
        ui->Writer->setFocus();
        return 0;
    }
    if(ui->Publisher->text().isEmpty()){
        ui->Publisher->setFocus();
        return 0;
    }
    if(ui->ISBNcode->text().isEmpty()){
        ui->ISBNcode->setFocus();
        return 0;
    }
    if(ui->IfGenerateFromDataBase->text().isEmpty()){
        return 0;
    }
    Name = ui->NameOfBook->text().toUtf8().data();
    Writer = ui->Writer->text().toUtf8().data();
    Publisher = ui->Publisher->text().toUtf8().data();
    ISBN = ui->ISBNcode->text().toUtf8().data();
    price = ui->PriceOfBook->value();
    totNum = ui->BookNum->value();
    Memo = ui->Memo->toPlainText().toUtf8().data();
    IfGenerateFromDataBase = ui->IfGenerateFromDataBase->text().toInt();
    return 1;
}

void Set_Ui_Value_To_Default(Ui::Add_Book_Widget *ui)
{
    ui->Writer->clear();
    ui->NameOfBook->clear();
    ui->Publisher->clear();
    ui->ISBNcode->clear();
    ui->PriceOfBook->setValue(0);
    ui->BookNum->setValue(1);
    ui->Memo->clear();
    ui->IfGenerateFromDataBase->clear();
}
