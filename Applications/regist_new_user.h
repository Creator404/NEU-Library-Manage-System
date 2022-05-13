#ifndef REGIST_NEW_USER_H
#define REGIST_NEW_USER_H

#include <QWidget>
#include "BasicIO/Insert_User_To_DataBase.h"

namespace Ui {
class Regist_New_User;
}

class Regist_New_User : public QWidget
{
    Q_OBJECT

public:
    explicit Regist_New_User(QWidget *parent = nullptr);
    ~Regist_New_User();

private slots:
    void on_RegistConfirm_clicked();

    void on_UserRank_currentTextChanged(const QString &arg1);

    void on_GetEmailCode_clicked();

private:
    Ui::Regist_New_User *ui;
};

int GetNewUserInfo(Ui::Regist_New_User *ui,QString &id,QString &password,QString &confirmpassword,QString &name,int &UserRank);
int CombineCheckInput(QString id,QString password,QString confirmpassword);


#endif // REGIST_NEW_USER_H
