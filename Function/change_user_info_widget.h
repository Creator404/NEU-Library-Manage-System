#ifndef CHANGE_USER_INFO_WIDGET_H
#define CHANGE_USER_INFO_WIDGET_H

#include <QWidget>

namespace Ui {
class change_user_info_widget;
}

class change_user_info_widget : public QWidget
{
    Q_OBJECT

public:
    explicit change_user_info_widget(QWidget *parent = nullptr);
    ~change_user_info_widget();
    void Get_Info(QString id,QString password,QString realname,int rank,float money,QString mailbox);
    int instance_rowNum;

private slots:
    void on_ConFirm_clicked();

private:
    Ui::change_user_info_widget *ui;

signals:
    void If_Changed_Info(int row);
};

int Get_User_Info(Ui::change_user_info_widget *ui,QString &id,QString &realname,int &rank,float &money,QString &mailbox);

#endif // CHANGE_USER_INFO_WIDGET_H
