#ifndef LOGIN_WIDGET_H
#define LOGIN_WIDGET_H

#include <QMainWindow>
#include "Initialize/DataBase_Initial.h"
#include "DataStructure/User.h"
#include "Applications/regist_new_user.h"
#include "Applications/admin_widget.h"
#include "Applications/user_widget.h"
#include "Function/find_password_widget.h"
#include "DataStructure/User.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login_Widget; }
QT_END_NAMESPACE

class Login_Widget : public QMainWindow
{
    Q_OBJECT

public:
    Login_Widget(QWidget *parent = nullptr);
    ~Login_Widget();

private slots:
    void on_AdminLogin_clicked();

    void on_UserLogin_clicked();

    void on_RegistUser_clicked();

    void show_again();

    void on_Forget_Password_clicked();

private:
    Ui::Login_Widget *ui;
    Regist_New_User Reg;
    admin_widget Adm;
    User_Widget Userr;
    Find_Password_Widget Find_Password;
};

int Get_Login_Info(Ui::Login_Widget *ui,QString &username,QString &password);

#endif // LOGIN_WIDGET_H
