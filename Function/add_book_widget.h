#ifndef ADD_BOOK_WIDGET_H
#define ADD_BOOK_WIDGET_H

#include <QWidget>

namespace Ui {
class Add_Book_Widget;
}

class Add_Book_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Add_Book_Widget(QWidget *parent = nullptr);
    ~Add_Book_Widget();

private slots:
    void on_ScanISBN_clicked();

    void on_Confirm_clicked();

    void closeEvent(QCloseEvent *);

private:
    Ui::Add_Book_Widget *ui;

signals:
    void UpdateFull();
};

int Get_Book_Info(Ui::Add_Book_Widget *ui,QString &Name,QString &Writer,QString &Publisher,QString &ISBN,QString &Memo,float &price,int &totNum,int &IfGenerateFromDataBase);
void Set_Ui_Value_To_Default(Ui::Add_Book_Widget *ui);

#endif // ADD_BOOK_WIDGET_H
