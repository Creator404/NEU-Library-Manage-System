#ifndef EMAIL_SENDER_H
#define EMAIL_SENDER_H

#include<QtCore>
#include<QObject>
#include<QCoreApplication>

#include <QTcpSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QAbstractSocket>
#include <QDateTime>
#include <QDate>
#include <QLocale>
#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>

class BasicSmtp:public QObject
{
    Q_OBJECT

public:
    BasicSmtp(){
        ExpectedReplyFromHost = "220 newxmesmtplogicsvrszb6.qq.com XMail Esmtp QQ Mail Server.\r\n";
    }
    ~BasicSmtp(){}

    virtual int ReadFromHost() = 0;
    virtual void CheckConnectState() = 0;
    virtual void SendHeloSis() = 0;
    virtual void SendAuthLogin() = 0;
    virtual void SendMyEmailAddress() = 0;
    virtual void SendAuthCode() = 0;
    virtual void SendEmailFrom() = 0;
    virtual void SendRcptTo() = 0;
    virtual void StartSendContent() = 0;
    virtual void SendContent() = 0;
    virtual void SendingStateConfirm() = 0;
    QString MyEmailAddress;
    QString authCode;
    QString ReceiverEmailAddress;

    QString Title;
    QString Content;

    QString ExpectedReplyFromHost;

    QString encodeBase64( QString xml );
    QString decodeBase64( QString xml );

    QTcpSocket *tcpSocket;

    QString Identification_Code;
};

class Smtp:public BasicSmtp
{
    Q_OBJECT

public:
    Smtp(){
        ExpectedReplyFromHost = "220 newxmesmtplogicsvrszb6.qq.com XMail Esmtp QQ Mail Server.\r\n";
    }
    ~Smtp(){}

    int ReadFromHost();
    void CheckConnectState();
    void SendHeloSis();
    void SendAuthLogin();
    void SendMyEmailAddress();
    void SendAuthCode();
    void SendEmailFrom();
    void SendRcptTo();
    void StartSendContent();
    void SendContent();
    void SendingStateConfirm();
    QString MyEmailAddress;
    QString authCode;
    QString ReceiverEmailAddress;

    QString Title;
    QString Content;

    QString ExpectedReplyFromHost;

    QString encodeBase64( QString xml );
    QString decodeBase64( QString xml );

    QTcpSocket *tcpSocket;

    QString Identification_Code;
};

class PasswordSmtp:public BasicSmtp
{
    Q_OBJECT

public:
    PasswordSmtp(){
        ExpectedReplyFromHost = "220 newxmesmtplogicsvrszb6.qq.com XMail Esmtp QQ Mail Server.\r\n";
    }
    ~PasswordSmtp(){}

    int ReadFromHost();
    void CheckConnectState();
    void SendHeloSis();
    void SendAuthLogin();
    void SendMyEmailAddress();
    void SendAuthCode();
    void SendEmailFrom();
    void SendRcptTo();
    void StartSendContent();
    void SendContent();
    void SendingStateConfirm();
    QString MyEmailAddress;
    QString authCode;
    QString ReceiverEmailAddress;

    QString Title;
    QString Content;

    QString ExpectedReplyFromHost;

    QString encodeBase64( QString xml );
    QString decodeBase64( QString xml );

    QTcpSocket *tcpSocket;

    QString Password;
};

#endif // EMAIL_SENDER_H
