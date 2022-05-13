#include "Email_Sender.h"

int Smtp::ReadFromHost()
{
    tcpSocket->waitForReadyRead(5000);
    QString buffer = tcpSocket->readAll();
    qDebug()<<buffer<<endl;
    if(buffer.contains(this->ExpectedReplyFromHost.toLatin1())){
        return 1;
    }
    return 0;
}

void Smtp::CheckConnectState()//确认与服务器的连接，随后发送helo sis
{
    tcpSocket->waitForReadyRead(5000);
    QString buffer = tcpSocket->readAll();
    if(tcpSocket->state() == QAbstractSocket::ConnectedState){
        SendHeloSis();
    }
    else{
        QMessageBox::warning(NULL,QObject::tr("Warning"),QObject::tr("当前无法连接至邮件服务，请修复后重试"),QMessageBox::Yes);
    }
}

void Smtp::SendHeloSis()//发送helo sis，以得到host回复，确认相关状态
{
    QString str = "helo sis\r\n";
    qDebug()<<"Smtp::SendHeloSis  向服务器发送了:"<<str;
    tcpSocket->write(str.toLatin1());
    tcpSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "250 OK\r\n";
    if(ReadFromHost()){
        SendAuthLogin();
    }
}

void Smtp::SendAuthLogin()
{
    QString str = "auth login\r\n";
    qDebug()<<"Smtp::SendAuthLogin  向服务器发送了:"<<str;
    tcpSocket->write(str.toLatin1());
    tcpSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "334 VXNlcm5hbWU6\r\n";
    if(ReadFromHost()){
        SendMyEmailAddress();
    }
}

void Smtp::SendMyEmailAddress()
{
    QString str = QString("\r\n").prepend(QString("@qq.com").toLatin1().toBase64());
    qDebug()<<"Smtp::SendMyEmailAddress  向服务器发送了:"<<str;
    tcpSocket->write(str.toLatin1());
    tcpSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "334 UGFzc3dvcmQ6\r\n";
    if(ReadFromHost()){
        SendAuthCode();
    }
}

void Smtp::SendAuthCode()
{
    QString str = QString("\r\n").prepend(QString("").toLatin1().toBase64());
    qDebug()<<"Smtp::SendAuthCode  向服务器发送了:"<<str;
    tcpSocket->write(str.toLatin1());
    tcpSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "235 Authentication successful\r\n";
    if(ReadFromHost()){
        SendEmailFrom();
    }
}

void Smtp::SendEmailFrom()
{
    QString str = QString("mail from:<%1>\r\n").arg("@qq.com");
    qDebug()<<"Smtp::SendEmailFrom  向服务器发送了:"<<str;
    tcpSocket->write(str.toLatin1());
    tcpSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "250 OK";
    if(ReadFromHost()){
        SendRcptTo();
    }
}

void Smtp::SendRcptTo()
{
    QString str = QString("rcpt to:<%1>\r\n").arg(ReceiverEmailAddress);
    qDebug()<<"Smtp::SendRcptTo  向服务器发送了:"<<str;
    tcpSocket->write(str.toLatin1());
    tcpSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "250 OK\r\n";
    if(ReadFromHost()){
        StartSendContent();
    }
}

void Smtp::StartSendContent()
{
    QString str = "data\r\n";
    qDebug()<<"Smtp::StartSendContent  向服务器发送了:"<<str;
    tcpSocket->write(str.toLatin1());
    tcpSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "354 End data with <CR><LF>.<CR><LF>";
    if(ReadFromHost()){
        SendContent();
    }
}

void Smtp::SendContent()
{
    QString Time_Now = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString senderMail = "@qq.com";
    QString title = "图书管理系统注册验证码";
    QString content = "亲爱的用户:\r\n欢迎您注册图书管理系统，您的验证码为"+Identification_Code+",请勿将此验证码泄露给其他人，若您未注册系统，请忽略此邮件。\r\n\r\n本邮件于"+Time_Now+"自动生成，请勿回复。";
    QString str = QString("subject:图书管理系统注册验证码\r\n"
                          "FROM:%1\r\n"
                          "TO:%2\r\n"
                          "\r\n"
                          "%3\r\n"
                          "\r\n"
                          ".\r\n").arg("图书管理系统").arg(ReceiverEmailAddress).arg(content);
    qDebug()<<"向服务器发送：　" + str;
    tcpSocket->write(str.toUtf8());
    tcpSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "250 OK: queued as";
    QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("验证码已经发送，请及时查收。"),QMessageBox::Yes);
    if(ReadFromHost()){
        SendingStateConfirm();
    }
}

void Smtp::SendingStateConfirm()
{
    QString str = "quit\r\n";
    tcpSocket->write(str.toUtf8());
    tcpSocket->waitForBytesWritten(5000);
    //221 Bye
}

#include "Email_Sender.h"

int PasswordSmtp::ReadFromHost()
{
    tcpSocket->waitForReadyRead(5000);
    QString buffer = tcpSocket->readAll();
    qDebug()<<buffer<<endl;
    if(buffer.contains(this->ExpectedReplyFromHost.toLatin1())){
        return 1;
    }
    return 0;
}

void PasswordSmtp::CheckConnectState()//确认与服务器的连接，随后发送helo sis
{
    tcpSocket->waitForReadyRead(5000);
    QString buffer = tcpSocket->readAll();
    if(tcpSocket->state() == QAbstractSocket::ConnectedState){
        SendHeloSis();
    }
    else{
        QMessageBox::warning(NULL,QObject::tr("Warning"),QObject::tr("当前无法连接至邮件服务，请修复后重试"),QMessageBox::Yes);
    }
}

void PasswordSmtp::SendHeloSis()//发送helo sis，以得到host回复，确认相关状态
{
    QString str = "helo sis\r\n";
    qDebug()<<"Smtp::SendHeloSis  向服务器发送了:"<<str;
    tcpSocket->write(str.toLatin1());
    tcpSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "250 OK\r\n";
    if(ReadFromHost()){
        SendAuthLogin();
    }
}

void PasswordSmtp::SendAuthLogin()
{
    QString str = "auth login\r\n";
    qDebug()<<"Smtp::SendAuthLogin  向服务器发送了:"<<str;
    tcpSocket->write(str.toLatin1());
    tcpSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "334 VXNlcm5hbWU6\r\n";
    if(ReadFromHost()){
        SendMyEmailAddress();
    }
}

void PasswordSmtp::SendMyEmailAddress()
{
    QString str = QString("\r\n").prepend(QString("@qq.com").toLatin1().toBase64());
    qDebug()<<"Smtp::SendMyEmailAddress  向服务器发送了:"<<str;
    tcpSocket->write(str.toLatin1());
    tcpSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "334 UGFzc3dvcmQ6\r\n";
    if(ReadFromHost()){
        SendAuthCode();
    }
}

void PasswordSmtp::SendAuthCode()
{
    QString str = QString("\r\n").prepend(QString("").toLatin1().toBase64());
    qDebug()<<"Smtp::SendAuthCode  向服务器发送了:"<<str;
    tcpSocket->write(str.toLatin1());
    tcpSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "235 Authentication successful\r\n";
    if(ReadFromHost()){
        SendEmailFrom();
    }
}

void PasswordSmtp::SendEmailFrom()
{
    QString str = QString("mail from:<%1>\r\n").arg("@qq.com");
    qDebug()<<"Smtp::SendEmailFrom  向服务器发送了:"<<str;
    tcpSocket->write(str.toLatin1());
    tcpSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "250 OK";
    if(ReadFromHost()){
        SendRcptTo();
    }
}

void PasswordSmtp::SendRcptTo()
{
    QString str = QString("rcpt to:<%1>\r\n").arg(ReceiverEmailAddress);
    qDebug()<<"Smtp::SendRcptTo  向服务器发送了:"<<str;
    tcpSocket->write(str.toLatin1());
    tcpSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "250 OK\r\n";
    if(ReadFromHost()){
        StartSendContent();
    }
}

void PasswordSmtp::StartSendContent()
{
    QString str = "data\r\n";
    qDebug()<<"Smtp::StartSendContent  向服务器发送了:"<<str;
    tcpSocket->write(str.toLatin1());
    tcpSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "354 End data with <CR><LF>.<CR><LF>";
    if(ReadFromHost()){
        SendContent();
    }
}

void PasswordSmtp::SendContent()
{
    QString Time_Now = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString senderMail = "@qq.com";
    QString title = "图书管理系统注册验证码";
    QString content = "亲爱的用户:\r\n欢迎您使用图书管理系统，您的密码为"+ Password +",请勿将密码泄露给其他人，若您未注册系统，请忽略此邮件。\r\n\r\n本邮件于"+Time_Now+"自动生成，请勿回复。";
    QString str = QString("subject:图书管理系统密码找回\r\n"
                          "FROM:%1\r\n"
                          "TO:%2\r\n"
                          "\r\n"
                          "%3\r\n"
                          "\r\n"
                          ".\r\n").arg("图书管理系统").arg(ReceiverEmailAddress).arg(content);
    qDebug()<<"向服务器发送：　" + str;
    tcpSocket->write(str.toUtf8());
    tcpSocket->waitForBytesWritten(5000);
    this->ExpectedReplyFromHost = "250 OK: queued as";
    QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("验证码已经发送，请及时查收。"),QMessageBox::Yes);
    if(ReadFromHost()){
        SendingStateConfirm();
    }
}

void PasswordSmtp::SendingStateConfirm()
{
    QString str = "quit\r\n";
    tcpSocket->write(str.toUtf8());
    tcpSocket->waitForBytesWritten(5000);
    //221 Bye
}
