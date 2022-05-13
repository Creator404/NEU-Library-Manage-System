#include "change_book_info_widget.h"
#include "ui_change_book_info_widget.h"
#include "Check_Functions.h"
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

int ABN;
bool IGFD;

Change_Book_Info_Widget::Change_Book_Info_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Change_Book_Info_Widget)
{
    ui->setupUi(this);
    ui->ISBNcode->setReadOnly(true);
    ui->ISBNcode->setFocusPolicy(Qt::NoFocus);
}

Change_Book_Info_Widget::~Change_Book_Info_Widget()
{
    delete ui;
}

void Change_Book_Info_Widget::Get_Info(QString name,QString writer,QString publisher,QString memo,QString ISBNcode,float price,int TotBookNum,int AlreadyBorrowedNum,bool ifGenerateFromDataBase)
{
    ui->NameOfBook->setText(name);
    ui->Writer->setText(writer);
    ui->Publisher->setText(publisher);
    ui->ISBNcode->setText(ISBNcode);
    ui->BookNum->setValue(TotBookNum);
    ui->PriceOfBook->setValue(price);
    ui->Memo->setText(memo);
    ABN = AlreadyBorrowedNum;
    IGFD = ifGenerateFromDataBase;
    if(ifGenerateFromDataBase){
        ui->NameOfBook->setFocusPolicy(Qt::NoFocus);
        ui->Writer->setFocusPolicy(Qt::NoFocus);
        ui->Publisher->setFocusPolicy(Qt::NoFocus);
        ui->PriceOfBook->setFocusPolicy(Qt::NoFocus);
        ui->Memo->setFocusPolicy(Qt::NoFocus);
        ui->NameOfBook->setReadOnly(true);
        ui->Writer->setReadOnly(true);
        ui->Publisher->setReadOnly(true);
        ui->PriceOfBook->setReadOnly(true);
        ui->Memo->setReadOnly(true);
    }
    else{
        ui->NameOfBook->setFocusPolicy(Qt::StrongFocus);
        ui->Writer->setFocusPolicy(Qt::StrongFocus);
        ui->Publisher->setFocusPolicy(Qt::StrongFocus);
        ui->PriceOfBook->setFocusPolicy(Qt::StrongFocus);
        ui->Memo->setFocusPolicy(Qt::StrongFocus);
        ui->NameOfBook->setReadOnly(false);
        ui->Writer->setReadOnly(false);
        ui->Publisher->setReadOnly(false);
        ui->PriceOfBook->setReadOnly(false);
        ui->Memo->setReadOnly(false);
    }
}

void Change_Book_Info_Widget::on_ConFirm_clicked()
{
    QString name,writer,publisher,memo,isbn;
    float price;
    int booknum;
    if(!Get_Book_Info(ui,name,writer,publisher,isbn,memo,price,booknum)){
        return;
    }
    if(booknum < ABN){
        QString Info = "您不能使书籍总数小于已经借阅的本数(已借出" + QString::number(ABN) + "本)。";
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr(Info.toUtf8().data()),QMessageBox::Yes);
        return;
    }
    if(!Combine_Check_Book_Illegal_Input(name,writer,publisher,memo)){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入有不合法的内容，通常是与sql注入有关，请重新确认后再进行插入（如',\"等符号是不被允许的）。"),QMessageBox::Yes);
        return;
    }
    int status = !ui->IfDelete->isChecked();
    QSqlQuery Query;
    QString ExecSentence;

    ExecSentence  = "UPDATE mylibrary SET `BookName` = '" + name + "',";
    ExecSentence += "`Author` = '" + writer + "',";
    ExecSentence += "`Publisher` = '" + publisher + "',";
    ExecSentence += "`Price` = " + QString::number(price,'f',2) + ",";
    ExecSentence += "`Memo` = '" + memo + "',";
    ExecSentence += "`TotNum` = " + QString::number(booknum) + ",";
    ExecSentence += "`status` = " + QString::number(status);
    ExecSentence += " WHERE `ISBN` = '" +  isbn + "';";

    if(Query.exec(ExecSentence)){
        QMessageBox::warning(NULL,QObject::tr("恭喜"),QObject::tr("信息修改成功！"),QMessageBox::Yes);
        emit If_Changed_Info(instance_rowNum);
        this->close();
    }
    else{
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("更新失败，请重试"),QMessageBox::Yes);
    }

}

int Get_Book_Info(Ui::Change_Book_Info_Widget *ui,QString &Name,QString &Writer,QString &Publisher,QString &ISBN,QString &Memo,float &price,int &totNum)
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
    Name = ui->NameOfBook->text().toUtf8().data();
    Writer = ui->Writer->text().toUtf8().data();
    Publisher = ui->Publisher->text().toUtf8().data();
    ISBN = ui->ISBNcode->text().toUtf8().data();
    price = ui->PriceOfBook->value();
    totNum = ui->BookNum->value();
    Memo = ui->Memo->toPlainText().toUtf8().data();
    return 1;
}
