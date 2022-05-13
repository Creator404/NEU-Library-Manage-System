#ifndef CHANGE_PASSWORD_WDIGET_H
#define CHANGE_PASSWORD_WDIGET_H

#include <QWidget>

namespace Ui {
class Change_Password_Wdiget;
}

class Change_Password_Wdiget : public QWidget
{
    Q_OBJECT

public:
    explicit Change_Password_Wdiget(QWidget *parent = nullptr);
    ~Change_Password_Wdiget();
    QString current_User_Id;

private slots:
    void on_pushButton_clicked();

private:
    Ui::Change_Password_Wdiget *ui;
};

#endif // CHANGE_PASSWORD_WDIGET_H
