#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtCharts/QPolarChart>

QT_CHARTS_USE_NAMESPACE

class ChartView : public QChartView
{
public:
    ChartView(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    void switchChartType();
};

#endif
