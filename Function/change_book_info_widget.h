#ifndef CHANGE_BOOK_INFO_WIDGET_H
#define CHANGE_BOOK_INFO_WIDGET_H

#include <QWidget>

namespace Ui {
class Change_Book_Info_Widget;
}

class Change_Book_Info_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Change_Book_Info_Widget(QWidget *parent = nullptr);
    ~Change_Book_Info_Widget();
    void Get_Info(QString name,QString writer,QString publisher,QString memo,QString ISBNcode,float price,int TotBookNum,int AlreadyBorrowedNum,bool ifGenerateFromDataBase);
    int instance_rowNum;

private slots:
    void on_ConFirm_clicked();

private:
    Ui::Change_Book_Info_Widget *ui;

signals:
    void If_Changed_Info(int row);
};

int Get_Book_Info(Ui::Change_Book_Info_Widget *ui,QString &Name,QString &Writer,QString &Publisher,QString &ISBN,QString &Memo,float &price,int &totNum);

#endif // CHANGE_BOOK_INFO_WIDGET_H
