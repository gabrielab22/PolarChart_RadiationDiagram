#include "chartview.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPolarChart>
#include <QtCore/QDebug>
#include <QAreaSeries>
#include <QDateTimeAxis>
#include <QString>
#include <QFile>
#include <QTextStream>


QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    const qreal angularMin = 0;
    const qreal angularMax = 360;

    const qreal radialMin = 0;
    const qreal radialMax = 1.0;

    QString line;
    QString file = "primjer3.txt";

    QFile myFile(file);

    if (!myFile.open(QFile::ReadOnly))
    {
        qDebug() << "Cannot open file ";
        return -1;
    }

    QTextStream in(&myFile);
 
 
  
    QSplineSeries* series2 = new QSplineSeries();
    series2->setName("spline");
    for (int i = angularMin; i <= 360; i++) {
        
        line = in.readLine();
     
        series2->append(i, line.split(" ")[0].toDouble());
    }
        
   
    //![1]
    QPolarChart *chart = new QPolarChart();
    chart->addSeries(series2);
 

    chart->setTitle("Use arrow keys to scroll, +/- to zoom, and space to switch chart type.");

    //![2] DIJAGRAM
    QValueAxis *angularAxis = new QValueAxis();
    angularAxis->setTickCount(9); // First and last ticks are co-located on 0/360 angle.
    angularAxis->setLabelFormat("%d");
    angularAxis->setShadesVisible(true);
    angularAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));
    chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);

    QValueAxis *radialAxis = new QValueAxis();
    radialAxis->setTickCount(6);
    radialAxis->setLabelFormat("%.2f");
    chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);
    //![2]

    radialAxis->setRange(radialMin, radialMax);
    angularAxis->setRange(angularMin, angularMax);

    ChartView *chartView = new ChartView();
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(800, 600);
    window.show();

    return a.exec();
}
