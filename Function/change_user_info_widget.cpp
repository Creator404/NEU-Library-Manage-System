#include "change_user_info_widget.h"
#include "ui_change_user_info_widget.h"
#include "Function/Check_Functions.h"
#include <QMessageBox>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>

int RankNow;

change_user_info_widget::change_user_info_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::change_user_info_widget)
{
    ui->setupUi(this);
    ui->ID->setFocusPolicy(Qt::NoFocus);
    ui->Password->setFocusPolicy(Qt::NoFocus);
    ui->ID->setReadOnly(true);
    ui->Password->setReadOnly(true);
}

change_user_info_widget::~change_user_info_widget()
{
    delete ui;
}

void change_user_info_widget::on_ConFirm_clicked()
{
    QString realname,mailbox,id;
    float money;
    int rank;
    if(!Get_User_Info(ui,id,realname,rank,money,mailbox)){
        qDebug()<<"Error"<<endl;
        return;
    }
    if(rank < RankNow){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您不可以使得用户等级比原来更低。"),QMessageBox::Yes);
        return;
    }
    if(!Combine_Check_User_Illegal_Input(realname,mailbox)){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入有不合法的内容，通常是与sql注入有关，请重新确认后再进行插入（如',\"等符号是不被允许的）。"),QMessageBox::Yes);
        return;
    }
    int status = !ui->IfDelete->isChecked();
    QSqlQuery Query;
    QString ExecSentence;

    ExecSentence = "UPDATE userinfo SET `User_Realname` = '" + realname + "',";
    ExecSentence += "`User_EmailBox` = '" + mailbox + "',";
    ExecSentence += "`User_MoneyLeft` = " + QString::number(money,'f',2) + ",";
    ExecSentence += "`User_Status` = " + QString::number(status) + ",";
    ExecSentence += "`User_Rank` = " + QString::number(rank) + ",";
    ExecSentence += "`User_MaxBorrowedBook` = " + QString::number(5 * rank);
    ExecSentence += " WHERE `User_Id` = '" + id + "';";

    qDebug()<<ExecSentence;

    if(Query.exec(ExecSentence)){
        emit If_Changed_Info(instance_rowNum);
        this->close();
    }
    else{
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("更新失败，请重试"),QMessageBox::Yes);
    }
}

void change_user_info_widget::Get_Info(QString id,QString password,QString realname,int rank,float money,QString mailbox)
{
    ui->ID->setText(id);
    ui->Password->setText(password);
    ui->RealName->setText(realname);
    ui->Rank->setCurrentIndex(rank-1);
    ui->MoneyLeft->setValue(money);
    ui->Mailbox->setText(mailbox);
    RankNow = rank;
}

int Get_User_Info(Ui::change_user_info_widget *ui,QString &id,QString &realname,int &rank,float &money,QString &mailbox)
{
    if(ui->RealName->text().isEmpty()){
        ui->RealName->setFocus();
        return 0;
    }
    if(ui->Mailbox->text().isEmpty()){
        ui->Mailbox->setFocus();
        return 0;
    }
    id = ui->ID->text().toUtf8().data();
    realname = ui->RealName->text().toUtf8().data();
    rank = ui->Rank->currentIndex()+1;
    money = ui->MoneyLeft->value();
    mailbox = ui->Mailbox->text().toUtf8().data();
    return 1;
}
