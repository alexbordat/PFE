#include "graph.h"
#include "ui_graph.h"

graph::graph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graph)
{
    ui->setupUi(this);
}

graph::~graph()
{
    delete ui;
}

void graph::makePlot_I_Q(QVector<double> const& I1,QVector<double> const& Q1,QVector<double> const& Time)
{
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::green));
    ui->customPlot->graph(0)->setData(Time, I1);
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::yellow));
    ui->customPlot->graph(1)->setData(Time, Q1);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("T : Time");
    ui->customPlot->yAxis->setLabel("Value");
    // set axes ranges, so we see all data:

    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->graph(1)->rescaleAxes(true);
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->customPlot->replot();
}
