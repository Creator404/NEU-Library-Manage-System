#ifndef ADMIN_WIDGET_H
#define ADMIN_WIDGET_H

#include <QWidget>
#include "Function/add_book_widget.h"
#include "Function/change_book_info_widget.h"
#include "Function/change_user_info_widget.h"
#include "Function/borrowed_chart_widget.h"

namespace Ui {
class admin_widget;
}

class admin_widget : public QWidget
{
    Q_OBJECT

public:
    explicit admin_widget(QWidget *parent = nullptr);
    ~admin_widget();

public slots:
    void Update_Full_Message();

    void Update_Full_Record_Message();

private slots:
    void on_Log_Out_clicked();

    void on_Add_Book_clicked();

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void Update_Book_Specific_Row(int row);

    void Update_User_Specific_Row(int row);

    void on_User_Info_table_cellDoubleClicked(int row, int column);

    void on_Search_clicked();

    void on_Search_UserInfo_clicked();

    void on_PaintGraph_clicked();

    void on_Search_RecordInfo_clicked();

private:
    Ui::admin_widget *ui;
    Add_Book_Widget Add_Book;
    Change_Book_Info_Widget Change_Book_Info;
    change_user_info_widget Change_User_Info;
    Borrowed_Chart_Widget BCW;

signals:
    void Show_Father_Widget();
};

#endif // ADMIN_WIDGET_H
