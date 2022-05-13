#include "regist_new_user.h"
#include "ui_regist_new_user.h"
#include "Function/Check_Functions.h"
#include "BasicIO/Read_User_From_DataBase.h"
#include "DataStructure/User.h"
#include "Function/Free_Function.h"
#include <QMessageBox>
#include <QUuid>
#include "BasicIO/Email_Sender.h"
#include "BasicIO/Read_User_From_DataBase.h"

QString Regist_MailBox = "";
QString Identification_Code = "";

Regist_New_User::Regist_New_User(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Regist_New_User)
{
    ui->setupUi(this);
    ui->Money->setFocusPolicy(Qt::NoFocus);
    ui->MaxLending->setFocusPolicy(Qt::NoFocus);
    ui->Money->setReadOnly(true);
    ui->MaxLending->setReadOnly(true);
    ui->UserRank->setCurrentText("1");
    ui->Money->setText("200");
    ui->MaxLending->setText("5");
    this->setWindowTitle("注册新用户");
}

Regist_New_User::~Regist_New_User()
{
    delete ui;
}

void Regist_New_User::on_RegistConfirm_clicked()
{
    QString id,password,name,confirmpassword,IdCode;
    int level;
    if(!GetNewUserInfo(ui,id,password,confirmpassword,name,level)){
        return;
    }
    if(!CombineCheckInput(id,password,confirmpassword)){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入不合法，用户名，密码，只能输入A~Z,a~z,0~9。"),QMessageBox::Yes);
        return;
    }
    if(password != confirmpassword){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您并没有确认您的密码，请重试。"),QMessageBox::Yes);
        return;
    }
    User* Head = Read_User_Info_By_ID(id,0);
    if(Head){
        if(Head->UserId == id){
            QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("该用户已经被注册，请更换您的用户名。"),QMessageBox::Yes);
            return;
        }
        Delete_User_LinkList(Head);
    }
    if(ui->MailBox->text().toUtf8() != Regist_MailBox){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您更改了要注册的邮箱，请重新获取对应的验证码。"),QMessageBox::Yes);
        return;
    }
    if(Regist_MailBox == ""){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您尚未获取验证码，请获取验证码后再注册。"),QMessageBox::Yes);
        return;
    }
    IdCode = ui->Identification_Code->text().toUtf8().data();
    if(IdCode != Identification_Code){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的验证码不正确，请重新输入。"),QMessageBox::Yes);
        ui->Identification_Code->clear();
        return;
    }
    Insert_User_Command(id,password,name,level,Regist_MailBox);
    ui->id->clear();
    ui->password->clear();
    ui->passwordconfirm->clear();
    ui->realname->clear();
    ui->UserRank->setCurrentText("1");
    ui->MailBox->clear();
    ui->Identification_Code->clear();
    Regist_MailBox = "";
    Identification_Code = "";
    QMessageBox::warning(NULL,QObject::tr("恭喜"),QObject::tr("注册成功！"),QMessageBox::Yes);
    this->close();
    return;
}

int GetNewUserInfo(Ui::Regist_New_User *ui,QString &id,QString &password,QString &confirmpassword,QString &name,int &UserRank)
{
    if(ui->id->text().isEmpty()){
        ui->id->setFocus();
        return 0;
    }
    if(ui->password->text().isEmpty()){
        ui->password->setFocus();
        return 0;
    }
    if(ui->passwordconfirm->text().isEmpty()){
        ui->passwordconfirm->setFocus();
        return 0;
    }
    if(ui->realname->text().isEmpty()){
        ui->realname->setFocus();
        return 0;
    }
    if(ui->MailBox->text().isEmpty()){
        ui->MailBox->setFocus();
        return 0;
    }
    if(ui->Identification_Code->text().isEmpty()){
        ui->Identification_Code->setFocus();
        return 0;
    }
    id = ui->id->text().toUtf8().data();
    password = ui->password->text().toUtf8().data();
    confirmpassword = ui->passwordconfirm->text().toUtf8().data();
    name = ui->realname->text().toUtf8().data();
    UserRank = ui->UserRank->currentText().toInt();
    return 1;
}

void Regist_New_User::on_UserRank_currentTextChanged(const QString &arg1)
{
    int Rank = arg1.toInt();
    ui->Money->setText(QString::number(Rank*200));
    ui->MaxLending->setText(QString::number(Rank*5));
}

int CombineCheckInput(QString id,QString password,QString confirmpassword)
{
    int tag = Check_A_To_Z_Input(id) && Check_A_To_Z_Input(password) && Check_A_To_Z_Input(confirmpassword);
    return tag;
}

void Regist_New_User::on_GetEmailCode_clicked()
{
    if(ui->MailBox->text().isEmpty()){
        ui->MailBox->setFocus();
        return;
    }
    Regist_MailBox = ui->MailBox->text().toUtf8().data();
    if(!Check_EmailBox_Input(Regist_MailBox)){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入不合法，或者不为支持的邮箱类型。（目前仅支持126，163，qq）"),QMessageBox::Yes);
        Regist_MailBox = "";
        return;
    }
    if(Check_User_Info_By_EmailBox(Regist_MailBox)){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("该邮箱已经被注册，请勿重复注册。"),QMessageBox::Yes);
        Regist_MailBox = "";
        return;
    }
    Identification_Code = QUuid::createUuid().toString().remove("{").remove("}").remove("-").right(6);
    Smtp *sendmail = new Smtp();
    sendmail->tcpSocket = new QTcpSocket();
    sendmail->Identification_Code = Identification_Code;
    sendmail->ReceiverEmailAddress = Regist_MailBox;
    sendmail->tcpSocket->connectToHost("smtp.qq.com",25);
    sendmail->tcpSocket->waitForConnected(3000);
    sendmail->CheckConnectState();
    return;
}
