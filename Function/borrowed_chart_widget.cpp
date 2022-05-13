#include "borrowed_chart_widget.h"
#include "ui_borrowed_chart_widget.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QtCharts>
#include <cmath>
#include <QDate>

using namespace std;

Borrowed_Chart_Widget::Borrowed_Chart_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Borrowed_Chart_Widget)
{
    ui->setupUi(this);
}

Borrowed_Chart_Widget::~Borrowed_Chart_Widget()
{
    delete ui;
}

void Borrowed_Chart_Widget::GenerateChart()
{
    QBarSeries *series = new QBarSeries();
    QChart *chart = new QChart();
    QBarSet *set0 = new QBarSet("借阅本数");
    chart->setTitle("Simple barchart example");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QDate StartDate;
    StartDate = QDate::currentDate();
    StartDate = StartDate.addDays(qint64(-10));
    int currentDayBook = 0;

    QSqlQuery Query;
    QString ExecSentence,start_date;
    int size;
    QSqlRecord rec;

    ExecSentence  = "SELECT * FROM record order by `index` DESC;";
    qDebug()<<ExecSentence<<endl;

    qDebug()<<"StartDate:"<<StartDate<<endl;
    Query.exec(ExecSentence);
    size = Query.numRowsAffected();
    qDebug()<<"Graph Widget size is:"<<size<<endl;
    int Numbers[11] = {0};
    while(Query.next()){
        rec = Query.record();
        start_date = rec.value("start_date").toString();
        qDebug()<<start_date<<endl;
        QDate RecordDate = QDate::fromString(start_date,"yyyy-MM-dd");
        qDebug()<<RecordDate<<" "<<StartDate<<endl;
        if(RecordDate < StartDate){
            break;
        }
        qDebug()<<StartDate.daysTo(RecordDate)<<endl;
        Numbers[StartDate.daysTo(RecordDate)]++;
    };
    int maxn = 1;
    for(int i = 1;i < 10;i++)
    {
        *set0<<Numbers[i];
        maxn = max(maxn,Numbers[i]);
    }
    if(currentDayBook>maxn){
        maxn = currentDayBook;
    }
    series->append(set0);
    series->setVisible(true);
    series->setLabelsVisible(true);
    chart->addSeries(series);

    QBarCategoryAxis *axisX = new QBarCategoryAxis;
    axisX->append("9天前");
    axisX->append("8天前");
    axisX->append("7天前");
    axisX->append("6天前");
    axisX->append("5天前");
    axisX->append("4天前");
    axisX->append("3天前");
    axisX->append("2天前");
    axisX->append("1天前");
    axisX->append("0天前");
    axisX->setLabelsColor(QColor(7,28,96));
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0,maxn);
    axisY->setTitleText("本数");
    axisY->setLabelFormat("%d");

    chart->setAxisX(axisX,series);
    chart->setAxisY(axisY,series);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);//底部对齐
    chart->legend()->setBackgroundVisible(true);//设置背景是否可视
    chart->legend()->setAutoFillBackground(true);//设置背景自动填充
    chart->legend()->setColor(QColor(222,233,251));//设置颜色
    chart->legend()->setLabelColor(QColor(0,100,255));//设置标签颜色
    chart->legend()->setMaximumHeight(50);
    chart->setTitle("借阅次数统计表");
    setWindowTitle("图像绘制");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *pVLayout = new QVBoxLayout(this);
    pVLayout->addWidget(chartView);
}
