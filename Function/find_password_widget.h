#ifndef FIND_PASSWORD_WIDGET_H
#define FIND_PASSWORD_WIDGET_H

#include <QWidget>

namespace Ui {
class Find_Password_Widget;
}

class Find_Password_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Find_Password_Widget(QWidget *parent = nullptr);
    ~Find_Password_Widget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Find_Password_Widget *ui;
};

#endif // FIND_PASSWORD_WIDGET_H
