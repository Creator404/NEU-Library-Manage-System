#ifndef BORROWED_CHART_WIDGET_H
#define BORROWED_CHART_WIDGET_H

#include <QWidget>

namespace Ui {
class Borrowed_Chart_Widget;
}

class Borrowed_Chart_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Borrowed_Chart_Widget(QWidget *parent = nullptr);
    ~Borrowed_Chart_Widget();
    void GenerateChart();

private:
    Ui::Borrowed_Chart_Widget *ui;
};

#endif // BORROWED_CHART_WIDGET_H
