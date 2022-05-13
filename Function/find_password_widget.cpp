#include "find_password_widget.h"
#include "ui_find_password_widget.h"
#include "BasicIO/Email_Sender.h"
#include "Function/Check_Functions.h"
#include "DataStructure/User.h"
#include "BasicIO/Read_User_From_DataBase.h"
#include "Free_Function.h"

Find_Password_Widget::Find_Password_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Find_Password_Widget)
{
    ui->setupUi(this);
    setWindowTitle("找回密码");
}

Find_Password_Widget::~Find_Password_Widget()
{
    delete ui;
}

void Find_Password_Widget::on_pushButton_clicked()
{
    if(ui->Name->text().isEmpty()){
        ui->Name->setFocus();
        return;
    }
    if(ui->Email->text().isEmpty()){
        ui->Email->setFocus();
        return;
    }
    QString Regist_MailBox = ui->Email->text().toUtf8().data();
    QString UserId = ui->Name->text().toUtf8().data();
    if(!Check_EmailBox_Input(Regist_MailBox)){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入不合法，或者不为支持的邮箱类型。（目前仅支持126，163，qq）"),QMessageBox::Yes);
        Regist_MailBox = "";
        return;
    }
    User *head = Read_User_Info_By_ID(UserId,0);
    if(!head){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("该id不存在"),QMessageBox::Yes);
        return;
    }
    if(head->mailbox != Regist_MailBox){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("该邮箱与该账户不匹配"),QMessageBox::Yes);
        return;
    }
    QString Password = head->password;
    Delete_User_LinkList(head);
    PasswordSmtp *sendmail = new PasswordSmtp();
    sendmail->tcpSocket = new QTcpSocket();
    sendmail->Password = Password;
    sendmail->ReceiverEmailAddress = Regist_MailBox;
    sendmail->tcpSocket->connectToHost("smtp.qq.com",25);
    sendmail->tcpSocket->waitForConnected(3000);
    sendmail->CheckConnectState();
    return;
}
