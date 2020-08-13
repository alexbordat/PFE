#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSpinBox>
#include <QMessageBox>
#include <QComboBox>
#include <QLabel>
#include <QFileDialog>
#include <QByteArray>
#include <QDialog>
#include <fstream>
#include <complex>
#include <fftw3.h>
#include "sdradar.h"
#include "graph.h"



// Constant defines
#define max_data_rate 2048000

#define REAL 0
#define IMAG 1



class MaFenetre : public QWidget // On hérite de QWidget (IMPORTANT)
{
    Q_OBJECT

    public:
    MaFenetre();
    ~MaFenetre();

    public slots:
    void initializeRadar();
    void updateRadar();
    void updateBandwith();
    void requestData();
    void processData();

private slots:
    QVector<double> linspace(double start, double end, double num);
    void fftwShift(std::vector<double>&data_shift);

private:
    QPushButton *m_bouton_initialize;
    QPushButton *m_bouton_update_radar;
    QPushButton *m_bouton_update_bandwith;
    QPushButton *m_bouton_request_data;
    QPushButton *m_bouton_process_data;

    QHBoxLayout *layout_button;
    QVBoxLayout *layoutPrincipal;

//    QVBoxLayout *layoutRecord;
    QVBoxLayout *layoutRecap;

    QVBoxLayout *layoutExtract;

    QFormLayout *formLayout_radar;

    QFormLayout *formLayout_bandwith;

    QLabel *label_radar;
    QLabel *label_Bandwith;

//    QLabel *labelRecord;
    QLabel *labelRecap;
    QLabel *labelExtract;

    QSpinBox *desiredSeconds_box;
    QComboBox *modulationScheme_box;
    QComboBox *numberOfChannel_box;
    QComboBox *sweepTime_box;
    QComboBox *samplingPerSweep_box;
    QDoubleSpinBox *freqStart_box;
    QDoubleSpinBox *freqStop_box;

//    QDialog *fenetreRecord;
    QDialog *fenetreRecap;
    QDialog *fenetreExtract;

    SDRadar *sdr;

    unsigned char *buffer_char;
    int return_code_init;
    quint32 SDRadar_model_num;
    bool init_done;
    bool updateRadar_done;
    bool updateBandwith_done;
    bool requestData_done;
    int sweepTime_index;
    double sweepTime;
    unsigned int NTS_max;
    unsigned int NTS;
    size_t desiredSeconds;
    int numberOfChannel;
    double freqStart;
    double freqStop;

    graph *graph_1;
    graph *graph_2;



};

#endif // MAFENETRE_H
