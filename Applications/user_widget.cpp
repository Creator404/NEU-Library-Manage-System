#include "user_widget.h"
#include "ui_user_widget.h"
#include <QDebug>
#include <QTableWidgetItem>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDateTime>

#include "DataStructure/Book.h"

#include "Function/Free_Function.h"
#include "Function/Check_Functions.h"

#include "BasicIO/Read_Book_From_MyLibrary.h"
#include "BasicIO/Read_User_From_DataBase.h"
#include "BasicIO/Insert_Record_To_DataBase.h"
#include "BasicIO/Read_Record_By_ISBN.h"

using namespace std;
using namespace cv;
using namespace zbar;

QString Instance_User_Id = "";
float Money_Now;

User_Widget::User_Widget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::User_Widget)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->BorrowList->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->Borrow_Return_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->UserId->setFocusPolicy(Qt::NoFocus);
    ui->Password->setFocusPolicy(Qt::NoFocus);
    ui->RealName->setFocusPolicy(Qt::NoFocus);
    ui->UserRank->setFocusPolicy(Qt::NoFocus);
    ui->MaxBorrowedNum->setFocusPolicy(Qt::NoFocus);
    ui->AlreadyBorrowedNum->setFocusPolicy(Qt::NoFocus);
    ui->MoneyLeft->setFocusPolicy(Qt::NoFocus);
    ui->Email->setFocusPolicy(Qt::NoFocus);
    ui->UserId->setReadOnly(true);
    ui->Password->setReadOnly(true);
    ui->RealName->setReadOnly(true);
    ui->UserRank->setReadOnly(true);
    ui->MaxBorrowedNum->setReadOnly(true);
    ui->AlreadyBorrowedNum->setReadOnly(true);
    ui->MoneyLeft->setReadOnly(true);
    ui->Email->setReadOnly(true);

    timer = new QTimer(this);
    image = new QImage();
    connect(timer,SIGNAL(timeout()),this,SLOT(readFrame()));
}

User_Widget::~User_Widget()
{
    delete ui;
}

void User_Widget::Set_UserID(QString &id)
{
    Instance_User_Id = id;
}

void User_Widget::Update_Full_Message()
{
    QSqlQuery Query;
    QString ExecSentence,name,author,publisher,isbn;
    QString start_date,end_date;
    float price;
    int size;
    int status;
    QSqlRecord rec;
    int TotBookNum,AlreadyBorrowedNum,TotBorrowedNum;
    int row = 0,col;

    //处理第一个tablewidget（书籍信息）
    ExecSentence  = "SELECT * FROM mylibrary WHERE `status` = 1;";
    Query.exec(ExecSentence);
    size = Query.numRowsAffected();
    ui->tableWidget->setRowCount(size);
    qDebug()<<"First size is:"<<size<<endl;
    row = 0;
    while(Query.next()){
        col = 0;
        rec = Query.record();
        name = rec.value("BookName").toString();
        author = rec.value("Author").toString();
        isbn = rec.value("ISBN").toString();
        publisher = rec.value("Publisher").toString();
        price = rec.value("Price").toFloat();
        TotBookNum = rec.value("TotNum").toInt();
        AlreadyBorrowedNum = rec.value("AlreadyBorrowedNum").toInt();
        TotBorrowedNum = rec.value("TotBorrowedNum").toInt();
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(name));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(author));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(isbn));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(publisher));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(TotBookNum)));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(AlreadyBorrowedNum)));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(TotBookNum-AlreadyBorrowedNum)));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(price,'f',2)));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(TotBorrowedNum)));
        row++;
    };

    //处理第二个tablewidget（借还信息）
    ExecSentence  = "SELECT * FROM record WHERE `userid` = '";
    ExecSentence += Instance_User_Id + "' order by `start_date` DESC;";
    if(!Query.exec(ExecSentence)){
        qDebug()<<ExecSentence<<endl;
        qDebug()<<"Serious Error."<<endl;
    }
    size = Query.numRowsAffected();
    ui->Borrow_Return_table->setRowCount(size);
    qDebug()<<"Second size is:"<<size<<endl;
    row = 0;
    while(Query.next()){
        col = 0;
        rec = Query.record();
        isbn = rec.value("isbn").toString();
        name = rec.value("name").toString();
        start_date = rec.value("start_date").toString();
        end_date = rec.value("end_date").toString();
        status = rec.value("status").toInt();
        ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem(isbn));
        ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem(name));
        ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem(start_date));
        ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem(end_date));
        if(status){
            ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem("已归还"));
        }
        else{
            ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem("未归还"));
        }
        row++;
    };
}

void User_Widget::Update_Personal_Info(User *head)
{
    ui->UserId->setText(head->UserId);
    ui->Password->setText("暂时不能显示");
    ui->RealName->setText(head->name);
    ui->UserRank->setText(QString::number(head->UserLevel));
    ui->MaxBorrowedNum->setText(QString::number(head->MaxBorrowedBook));
    ui->AlreadyBorrowedNum->setText(QString::number(head->AlreadyBorrowedBook));
    ui->MoneyLeft->setText(QString::number(head->money,'f',2));
    ui->Email->setText(head->mailbox);
}

void User_Widget::on_tableWidget_cellDoubleClicked(int row, int column)
{
    return;
}

void User_Widget::on_Borrow_Return_table_cellDoubleClicked(int row, int column)
{
    return;
}

QString Modify_GetISBNFromCamera(Ui::User_Widget *ui,int &flag)
{
    VideoCapture capture(0);
    if (!capture.isOpened()){//没有打开摄像头的话，就返回。
        return NULL;
    }
    // 灰度图
    // 创建zbar图像扫描器
    ImageScanner scanner;
    // 配置zbar图片扫描器，采取13位ISBN
    scanner.set_config(ZBAR_ISBN13,ZBAR_CFG_ENABLE,1);
    while (1)
    {
        if(flag == 1){
            goto stop;
        }

        // 从摄像头中抓取一帧
        Mat frame;
        capture>>frame;

        // 图像不为空
        if (!frame.empty())
        {
            Mat imageGray;

            cvtColor(frame,imageGray,CV_RGB2GRAY);
            int width = imageGray.cols;
            int height = imageGray.rows;
            uchar *raw = (uchar*)imageGray.data;
            Image CheckZBar(width,height,"Y800",raw,width*height);
            scanner.scan(CheckZBar);
            Image::SymbolIterator symbol = CheckZBar.symbol_begin();
            int test = 0;
            if(!(CheckZBar.symbol_begin()==CheckZBar.symbol_end())){
                test = 1;
            }
            for(;symbol != CheckZBar.symbol_end();++symbol)
            {
                cout<<"Type:"<<endl<<symbol->get_type_name()<<endl;
                cout<<"Data:"<<endl<<symbol->get_data()<<endl;
                string answer = symbol->get_data();
                QString ans = QString::fromStdString(answer);
                cv::destroyAllWindows();
                return ans;
            }
            waitKey(50);
            if(test){
                cv::destroyAllWindows();
                goto stop;
            }

            //一个二维码
        }
        // 按了ESC可退出
//        cvWaitKey(50);
//        if (cvWaitKey(50) == 27) {
//            cv::destroyAllWindows();
//            break;
//        }
        // 按叉可推出
//        if (!cvGetWindowHandle("Scanner"))
//        {
//            cv::destroyAllWindows();
//            break;
//        }
    }
stop:
    return "";
}

void User_Widget::on_pushButton_clicked()
{

    cap.open(0);
    timer->start(33);
}

void User_Widget::on_pushButton_2_clicked()
{
    timer->stop();
    cap.release();
    ui->label->clear();
    BorrowedBookList.clear();
}

void User_Widget::readFrame()
{
    // 读入显示
    cap.read(src_image);
    QStringList ScannedBooks;
    Mat frame = src_image;
    QImage imag = MatImageToQt(src_image);
    ui->label->setPixmap(QPixmap::fromImage(imag));
    ImageScanner scanner;
    scanner.set_config(ZBAR_ISBN13,ZBAR_CFG_ENABLE,1);
    if (!frame.empty())
    {
        //qDebug()<<"Inside"<<endl;
        Mat imageGray;
        cvtColor(frame,imageGray,CV_RGB2GRAY);
        int width = imageGray.cols;
        int height = imageGray.rows;
        uchar *raw = (uchar*)imageGray.data;
        Image CheckZBar(width,height,"Y800",raw,width*height);
        scanner.scan(CheckZBar);
        Image::SymbolIterator symbol = CheckZBar.symbol_begin();
        for(;symbol != CheckZBar.symbol_end();++symbol)
        {
            cout<<"Type:"<<endl<<symbol->get_type_name()<<endl;
            cout<<"Data:"<<endl<<symbol->get_data()<<endl;
            string answer = symbol->get_data();
            QString ans = QString::fromStdString(answer);
            if(!BorrowedBookList.contains(ans)){
                BorrowedBookList.append(ans);
                qDebug()<<"Inserting in User_Widget Func:readFrame:"<<ans<<endl;
                int rowcount = ui->BorrowList->rowCount();
                ui->BorrowList->setRowCount(rowcount+1);
                ui->BorrowList->setItem(rowcount,0,new QTableWidgetItem(ans));
                Book *Head = Read_Book_Info_By_ISBN_From_Mylibrary(ans,0);
                if(!Head){
                    ui->BorrowList->removeRow(ui->BorrowList->rowCount()-1);
                    continue;
                }
                ui->BorrowList->setItem(rowcount,1,new QTableWidgetItem(Head->name));
                Delete_Book_LinkList(Head);
            }
        }
    }
    return;
}

QImage User_Widget::MatImageToQt(const Mat &src)
{
    //CV_8UC1 8位无符号的单通道---灰度图片
    if(src.type() == CV_8UC1)
    {
        //使用给定的大小和格式构造图像
        //QImage(int width, int height, Format format)
        QImage qImage(src.cols,src.rows,QImage::Format_Indexed8);
        //扩展颜色表的颜色数目
        qImage.setColorCount(256);

        //在给定的索引设置颜色
        for(int i = 0; i < 256; i ++)
        {
            //得到一个黑白图
            qImage.setColor(i,qRgb(i,i,i));
        }
        //复制输入图像,data数据段的首地址
        uchar *pSrc = src.data;
        //
        for(int row = 0; row < src.rows; row ++)
        {
            //遍历像素指针
            uchar *pDest = qImage.scanLine(row);
            //从源src所指的内存地址的起始位置开始拷贝n个
            //字节到目标dest所指的内存地址的起始位置中
            memcmp(pDest,pSrc,src.cols);
            //图像层像素地址
            pSrc += src.step;
        }
        return qImage;
    }
    //为3通道的彩色图片
    else if(src.type() == CV_8UC3)
    {
        //得到图像的的首地址
        const uchar *pSrc = (const uchar*)src.data;
        //以src构造图片
        QImage qImage(pSrc,src.cols,src.rows,src.step,QImage::Format_RGB888);
        //在不改变实际图像数据的条件下，交换红蓝通道
        return qImage.rgbSwapped();
    }
    //四通道图片，带Alpha通道的RGB彩色图像
    else if(src.type() == CV_8UC4)
    {
        const uchar *pSrc = (const uchar*)src.data;
        QImage qImage(pSrc, src.cols, src.rows, src.step, QImage::Format_ARGB32);
        //返回图像的子区域作为一个新图像
        return qImage.copy();
    }
    else
    {
        return QImage();
    }
}

void User_Widget::on_BorrowList_cellDoubleClicked(int row, int column)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("移除确认");
    msgBox.setText("您确认要移除本书吗？");
    QPushButton *YesButton = msgBox.addButton(tr("是"), QMessageBox::ActionRole);
    QPushButton *NoButton = msgBox.addButton(tr("否"),QMessageBox::ActionRole);
    msgBox.exec();
    if (msgBox.clickedButton() != YesButton) {
        return;
    }
    Book *Head = Read_Book_Info_By_ISBN_From_Mylibrary(ui->BorrowList->item(row,0)->text().toUtf8().data(),0);
    Money_Now -= Head->price;
    BorrowedBookList.removeOne(Head->ISBNcode);
    Delete_Book_LinkList(Head);
    ui->BorrowList->removeRow(row);
    return;
}

void User_Widget::on_BorrowConfirm_clicked()
{
    int BookNum = ui->BorrowList->rowCount();
    if(BookNum == 0){
        return;
    }
    User *Head = Read_User_Info_By_ID(Instance_User_Id,0);
    int Still_Can_Borrowed_Num = Head->MaxBorrowedBook - Head->AlreadyBorrowedBook;
    if(BookNum >= Still_Can_Borrowed_Num){
        QMessageBox::warning(NULL,QObject::tr("Warning"),QObject::tr("您借阅的书籍已经超出了您的借阅上限。"),QMessageBox::Yes);
        return;
    }
    float TotMoney = 0;
    for(int i = 0;i < BookNum;i++)
    {
        QString isbn = ui->BorrowList->item(i,0)->text().toUtf8().data();
        Book *head = Read_Book_Info_By_ISBN_From_Mylibrary(isbn,0);
        TotMoney += head->price;
        Delete_Book_LinkList(head);
    }
    if(TotMoney > Head->money){
        Delete_User_LinkList(Head);
        return;
    }

    for(int i = 0;i < BookNum;i++)
    {
        QString isbn = ui->BorrowList->item(i,0)->text().toUtf8().data();
        Book *head = Read_Book_Info_By_ISBN_From_Mylibrary(isbn,0);
        QSqlQuery Query;
        QString ExecSentence;

        ExecSentence = "UPDATE mylibrary SET `AlreadyBorrowedNum` = " + QString::number(head->AlreadyBorrowedNum + 1) + ",";
        ExecSentence += "`TotBorrowedNum` = " + QString::number(head->TotBorrowedNum + 1) + " ";
        ExecSentence += " WHERE `ISBN` = '" + isbn + "';";

        qDebug()<<ExecSentence;

        if(!Query.exec(ExecSentence)){
            QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("更新失败，请重试"),QMessageBox::Yes);
        }
        Insert_Record_Command(Instance_User_Id,head->ISBNcode,head->name);
        Delete_Book_LinkList(head);
    }

    QSqlQuery Query;
    QString ExecSentence;

    ExecSentence = "UPDATE userinfo SET `User_MoneyLeft` = " + QString::number(Head->money - TotMoney,'f',2) + ",";
    ExecSentence += "`User_AlreadyBorrowedBook` = " + QString::number(Head->AlreadyBorrowedBook + BookNum) + " ";
    ExecSentence += " WHERE `User_Id` = '" + Instance_User_Id + "';";

    qDebug()<<ExecSentence;

    if(Query.exec(ExecSentence)){
        ui->BorrowList->setRowCount(0);
    }
    else{
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("更新失败，请重试"),QMessageBox::Yes);
    }
}

void User_Widget::on_ReturnConfirm_clicked()
{
    int BookNum = ui->BorrowList->rowCount();
    if(BookNum == 0){
        return;
    }
    User *Head = Read_User_Info_By_ID(Instance_User_Id,0);
    float TotMoney = 0;

    for(int i = 0;i < BookNum;i++)
    {
        QString isbn = ui->BorrowList->item(i,0)->text().toUtf8().data();
        Book *head = Read_Book_Info_By_ISBN_From_Mylibrary(isbn,0);
        QSqlQuery Query;
        QString ExecSentence;
        QSqlRecord rec;

        ExecSentence = "SELECT * FROM record where `isbn` = '" + isbn + "' and `userid` = '" + Instance_User_Id + "' and `status` = 0";
        qDebug()<<ExecSentence<<endl;
        Query.exec(ExecSentence);
        if(!Query.next()){
            QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您并未借阅过本书。"),QMessageBox::Yes);
            continue;
        }
        rec = Query.record();

        int index = rec.value("index").toInt();
        QString timeInDataBase = rec.value("end_date").toString();

        ExecSentence = "UPDATE record SET `status` = 1";
        ExecSentence += " WHERE `index` = " + QString::number(index) + ";";
        if(!Query.exec(ExecSentence)){
            QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("更新失败，请重试。"),QMessageBox::Yes);
        }
        qDebug()<<timeInDataBase<<endl;
        QDate instance = QDate::currentDate();
        QDate dif = QDate::fromString(timeInDataBase,"yyyy-MM-dd");

        int Offset = 0;
        while(dif < instance){
            qDebug()<<dif<<"   "<<instance<<endl;
            Offset++;
            dif = dif.addDays(1);
        }

        TotMoney += max((20 - Offset),0)*head->price / 20.0;

        ExecSentence = "UPDATE mylibrary SET `AlreadyBorrowedNum` = " + QString::number(head->AlreadyBorrowedNum - 1) + " ";
        ExecSentence += " WHERE `ISBN` = '" + isbn + "';";

        qDebug()<<ExecSentence;

        if(!Query.exec(ExecSentence)){
            QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("更新失败，请重试。"),QMessageBox::Yes);
        }
        Delete_Book_LinkList(head);
    }

    QSqlQuery Query;
    QString ExecSentence;

    ExecSentence = "UPDATE userinfo SET `User_MoneyLeft` = " + QString::number(Head->money + TotMoney,'f',2) + ",";
    ExecSentence += "`User_AlreadyBorrowedBook` = " + QString::number(Head->AlreadyBorrowedBook + BookNum) + " ";
    ExecSentence += " WHERE `User_Id` = '" + Instance_User_Id + "';";

    qDebug()<<ExecSentence;

    if(Query.exec(ExecSentence)){
        ui->BorrowList->setRowCount(0);
    }
    else{
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("更新失败，请重试"),QMessageBox::Yes);
    }
}

void User_Widget::on_Search_clicked()
{
    QSqlQuery Query;
    QString ExecSentence,name,author,publisher,isbn;
    float price;
    int TotBookNum,AlreadyBorrowedNum,TotBorrowedNum;
    QSqlRecord rec;
    int OrderType = ui->BookOrderType->currentIndex();
    name = ui->BookName->text().toUtf8().data();
    isbn = ui->ISBNCode->text().toUtf8().data();
    author = ui->Writer->text().toUtf8().data();
    publisher = ui->Publisher->text().toUtf8().data();
    if(!(name != "" || isbn != "" || author != "" || publisher != "")){
        Update_Full_Message();
        return;
    }

    //处理接下来需要上传的数据
    int size;
    if(!Combine_Check_Book_Illegal_Input(name,isbn,author,publisher)){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入有不合法的内容，通常是与sql注入有关，请重新确认后再进行插入（如',\"等符号是不被允许的）。"),QMessageBox::Yes);
        return;
    }
    ExecSentence  = "SELECT * FROM mylibrary WHERE `status` = 1 ";
    if(name != ""){
        ExecSentence += "and ";
        ExecSentence += "`BookName` like '%" + name + "%'";
    }
    if(isbn != ""){
        ExecSentence += " and ";
        ExecSentence += "`ISBN` = '" + isbn + "'";
    }
    if(author != ""){
        ExecSentence += " and ";
        ExecSentence += "`Author` like '%" + author + "%'";
    }
    if(publisher != ""){
        ExecSentence += " and ";
        ExecSentence += "`Publisher` like '%" + publisher + "%'";
    }

    if(OrderType <= 1){
        ExecSentence += " order by `TotBorrowedNum` ";
    }
    else{
        ExecSentence += " order by (`TotNum` - `AlreadyBorrowedNum`) ";
    }

    if(OrderType % 2 == 1){
        ExecSentence += "ASC;";
    }
    else{
        ExecSentence += "DESC;";
    }

    qDebug()<<ExecSentence<<endl;

    Query.exec(ExecSentence);
    size = Query.numRowsAffected();
    ui->tableWidget->setRowCount(size);
    qDebug()<<"After Search Size is:"<<size<<endl;
    int row = 0,col = 0;
    while(Query.next()){
        col = 0;
        rec = Query.record();
        name = rec.value("BookName").toString();
        author = rec.value("Author").toString();
        isbn = rec.value("ISBN").toString();
        publisher = rec.value("Publisher").toString();
        price = rec.value("Price").toFloat();
        TotBookNum = rec.value("TotNum").toInt();
        AlreadyBorrowedNum = rec.value("AlreadyBorrowedNum").toInt();
        TotBorrowedNum = rec.value("TotBorrowedNum").toInt();
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(name));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(author));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(isbn));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(publisher));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(TotBookNum)));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(AlreadyBorrowedNum)));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(TotBookNum-AlreadyBorrowedNum)));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(price,'f',2)));
        ui->tableWidget->setItem(row,col++,new QTableWidgetItem(QString::number(TotBorrowedNum)));
        row++;
    };
    return;
}

void User_Widget::on_Search_RecordInfo_clicked()
{
    QSqlQuery Query;
    QString ExecSentence,ISBN,BookName;
    QSqlRecord rec;
    ISBN = ui->ISBN_Record->text().toUtf8().data();
    BookName = ui->BookName_Record->text().toUtf8().data();
    if(!(ISBN != "" || BookName != "")){
        Update_Full_Message();
        return;
    }

    //处理接下来需要上传的数据
    int size;
    if(!Combine_Check_Book_Illegal_Input(ISBN,BookName)){
        QMessageBox::warning(NULL,QObject::tr("警告"),QObject::tr("您的输入有不合法的内容，通常是与sql注入有关，请重新确认后再进行插入（如',\"等符号是不被允许的）。"),QMessageBox::Yes);
        return;
    }
    ExecSentence  = "SELECT * FROM record WHERE `userid` = '" + Instance_User_Id +"'";
    int flag = 0;
    if(ISBN != ""){
        ExecSentence += " and ";
        ExecSentence += "`isbn` = '" + ISBN + "'";
    }
    if(BookName != ""){
        ExecSentence += " and ";
        ExecSentence += "`name` like '%" + BookName + "%'";
    }
    if(ui->RecordOrderType->currentIndex()){
        ExecSentence += " order by `isbn` DESC,`index` DESC;";
    }
    else{
        ExecSentence += " order by `index` DESC,`isbn` DESC;";
    }
    qDebug()<<ExecSentence<<endl;

    Query.exec(ExecSentence);
    size = Query.numRowsAffected();
    ui->Borrow_Return_table->setRowCount(size);
    qDebug()<<"Second size is:"<<size<<endl;
    int row = 0,col,status;
    QString start_date,end_date;
    while(Query.next()){
        col = 0;
        rec = Query.record();
        ISBN = rec.value("isbn").toString();
        BookName = rec.value("name").toString();
        start_date = rec.value("start_date").toString();
        end_date = rec.value("end_date").toString();
        status = rec.value("status").toInt();
        ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem(ISBN));
        ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem(BookName));
        ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem(start_date));
        ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem(end_date));
        if(status){
            ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem("已归还"));
        }
        else{
            ui->Borrow_Return_table->setItem(row,col++,new QTableWidgetItem("未归还"));
        }
        row++;
    };
    return;
}

void User_Widget::on_Log_Out_clicked()
{
    emit Show_Father_Widget();
    this->close();
}

void User_Widget::on_Change_Password_clicked()
{
    CPW.current_User_Id = Instance_User_Id;
    CPW.show();

}
