#ifndef USER_WIDGET_H
#define USER_WIDGET_H

#include <QMainWindow>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <QTextCodec>
#include <string>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <string>
#include <vector>
#include <QDebug>
#include <zbar.h>
#include <zbar/Decoder.h>
#include <iconv.h>
#include <QTimer>

#include "DataStructure/User.h"

#include "Function/change_password_wdiget.h"

using namespace cv;
using namespace std;

namespace Ui {
class User_Widget;
}

class User_Widget : public QMainWindow
{
    Q_OBJECT

public:
    explicit User_Widget(QWidget *parent = nullptr);
    ~User_Widget();
    void Update_Full_Message();
    void Update_Personal_Info(User *head);
    void Set_UserID(QString &id);

    //Test
    QImage MatImageToQt(const Mat &src);

private slots:
    void on_Borrow_Return_table_cellDoubleClicked(int row, int column);

    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    //Test
    void readFrame();

    void on_BorrowList_cellDoubleClicked(int row, int column);


    void on_BorrowConfirm_clicked();

    void on_ReturnConfirm_clicked();

    void on_Search_clicked();

    void on_Search_RecordInfo_clicked();

    void on_Log_Out_clicked();

    void on_Change_Password_clicked();

private:
    Ui::User_Widget *ui;

    //Test
    VideoCapture cap;
    Mat src_image;
    QTimer *timer;
    QImage *image;
    QStringList BorrowedBookList;

    void on_Open_triggered();
    void on_Stop_triggere();

    Change_Password_Wdiget CPW;

signals:
    void Show_Father_Widget();
};

QString Modify_GetISBNFromCamera(Ui::User_Widget *ui,int &flag);
QImage  Mat2QImage(cv::Mat cvImg);

#endif // USER_WIDGET_H
