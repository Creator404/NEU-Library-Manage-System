#include "login_widget.h"
#include "ui_login_widget.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include "Function/Check_Functions.h"
#include "Function/Free_Function.h"
#include "BasicIO/Read_User_From_DataBase.h"
#include <QMessageBox>

Login_Widget::Login_Widget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login_Widget)
{
    ui->setupUi(this);
    connect(&Adm,SIGNAL(Show_Father_Widget()),this,SLOT(show_again()));
    setWindowTitle("登录界面");
    connect(&Userr,SIGNAL(Show_Father_Widget()),this,SLOT(show_again()));
}

Login_Widget::~Login_Widget()
{
    delete ui;
}

void Login_Widget::on_AdminLogin_clicked()
{
    QString username,password;
    if(!Get_Login_Info(ui,username,password)){
        return;
    }
    if(username != "DemonTracer" || password != "testing"){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("账户或密码错误，请重试。"),QMessageBox::Yes);
        return;
    }
    Adm.Update_Full_Message();
    Adm.Update_Full_Record_Message();
    Adm.show();
    this->hide();

}

void Login_Widget::on_UserLogin_clicked()
{
    QString username,password;
    if(!Get_Login_Info(ui,username,password)){
        return;
    }
    User* UserForNow = Read_User_Info_By_ID(username,0);
    if(!UserForNow || !UserForNow->status){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("该用户不存在。"),QMessageBox::Yes);
        return;
    }
    if(UserForNow->UserId != username || UserForNow->password != password){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("账户或密码错误，请重试。"),QMessageBox::Yes);
        Delete_User_LinkList(UserForNow);
        return;
    }
    Userr.Set_UserID(UserForNow->UserId);
    Userr.Update_Personal_Info(UserForNow);
    Delete_User_LinkList(UserForNow);
    Userr.Update_Full_Message();
    Userr.show();
    this->hide();
}

void Login_Widget::on_RegistUser_clicked()
{
    Reg.show();
}

int Get_Login_Info(Ui::Login_Widget *ui,QString &username,QString &password)
{
    if(ui->Account->text().isEmpty()){
        ui->Account->setFocus();
        return 0;
    }
    if(ui->Password->text().isEmpty()){
        ui->Password->setFocus();
        return 0;
    }
    username = ui->Account->text().toUtf8().data();
    password = ui->Password->text().toUtf8().data();
    if(!Check_A_To_Z_Input(username) || !Check_A_To_Z_Input(password)){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入不合法，用户名，密码，只能输入A~Z,a~z,0~9。"),QMessageBox::Yes);
        return 0;
    }
    return 1;
}

void Login_Widget::show_again()
{
    ui->Account->clear();
    ui->Password->clear();
    this->show();
}

void Login_Widget::on_Forget_Password_clicked()
{
    Find_Password.show();
}
