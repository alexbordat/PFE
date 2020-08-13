#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>

namespace Ui {
class graph;
}

class graph : public QDialog
{
    Q_OBJECT

public:
    explicit graph(QWidget *parent = 0);
    ~graph();

public slots:
    void makePlot_I_Q(QVector<double> const& I1,QVector<double> const& Q1,QVector<double> const& Time);

private:
    Ui::graph *ui;
};

#endif // GRAPH_H
