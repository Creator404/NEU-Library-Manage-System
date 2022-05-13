#include "change_password_wdiget.h"
#include "ui_change_password_wdiget.h"
#include <QDebug>
#include <QTableWidgetItem>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDateTime>
#include "BasicIO/Read_User_From_DataBase.h"
#include "DataStructure/User.h"
#include "Function/Check_Functions.h"
#include "Function/Free_Function.h"

Change_Password_Wdiget::Change_Password_Wdiget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Change_Password_Wdiget)
{
    ui->setupUi(this);
}

Change_Password_Wdiget::~Change_Password_Wdiget()
{
    delete ui;
}

void Change_Password_Wdiget::on_pushButton_clicked()
{
    QString password,newpassword,repeatpassword;
    if(!ui->OriginPassword->text().isEmpty()){
        password = ui->OriginPassword->text().toUtf8().data();
    }
    else{
        ui->OriginPassword->setFocus();
        return;
    }
    if(!ui->NewPassword->text().isEmpty()){
        newpassword = ui->NewPassword->text().toUtf8().data();
    }
    else{
        ui->NewPassword->setFocus();
        return;
    }
    if(!ui->Repeat_Password->text().isEmpty()){
        repeatpassword = ui->Repeat_Password->text().toUtf8().data();
    }
    else{
        ui->Repeat_Password->setFocus();
        return;
    }
    User *head = Read_User_Info_By_ID(current_User_Id,0);
    if(!head){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("致命错误，并未读取到您的账户信息，请联系管理员是否已经将您的账户注销。"),QMessageBox::Yes);
        return;
    }
    if(!Combine_Check_Book_Illegal_Input(newpassword,repeatpassword)){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入有不合法的内容，通常是与sql注入有关，请重新确认后再进行插入（如',\"等符号是不被允许的）。"),QMessageBox::Yes);
        Delete_User_LinkList(head);
        return;
    }
    if(head->password != password){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的密码不正确。"),QMessageBox::Yes);
        Delete_User_LinkList(head);
        return;
    }
    else if(newpassword != repeatpassword){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的密码未确认。"),QMessageBox::Yes);
        Delete_User_LinkList(head);
        return;
    }
    QString Execsentence;

    QSqlQuery Query;
    QString ExecSentence;

    ExecSentence = "UPDATE userinfo SET `User_Password` = '" + newpassword + "' WHERE `User_Id` = '" + current_User_Id + "';";

    qDebug()<<ExecSentence;

    if(!Query.exec(ExecSentence)){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("更新失败，请重试"),QMessageBox::Yes);
    }
    QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("密码已更新"),QMessageBox::Yes);
    Delete_User_LinkList(head);
    ui->OriginPassword->clear();
    ui->NewPassword->clear();
    ui->Repeat_Password->clear();
    this->close();
}
