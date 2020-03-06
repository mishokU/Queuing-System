#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QProgressBar>
#include <QThread>
#include <QWaitCondition>
#include <QTime>
#include <QTextEdit>
#include <QCoreApplication>

#include "cmo_system.hpp"
#include "statictis.h"

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();

    void setValues(std::vector<double> values);


    void setRequests(int count);
    void setGenerator(int generator, double time);
    void setBuffer(int buffer, int generator, double time);
    void setDevice(int device, int generator, double time);

    void setBufferRef(int reference);
    void setDeviceReleaseTime(int device, double time);
    void setDeviceRef(int device);

    void setSystemTime(double systemTime);

    void setProgress(int progress);
    void setMaxProgressBar(unsigned long max);

    void manageSteps(int step);

    void setSystem(MainCMOSystem *system);
    void getBufferCell(int cell,int generator, double time);
    void setRejectedCell(Cell &cell);

    void clearDevices();
    void clearBuffers();
    void clearGenerators();

    void clearAll();

private slots:

    void on_pushButton_2_clicked();

    void on_prev_step_clicked();

    void on_go_to_step_clicked();

private:
    QTextEdit *count_of_request;
    QTextEdit *priority_request;

    QTextEdit *systemTime;
    QProgressBar *progress_bar;

    std::vector<QTextEdit*> generators;
    std::vector<QTextEdit*> buffers;
    std::vector<QTextEdit*> devices;

    std::vector<QTextEdit*> rejected_cells;
    std::vector<QTextEdit*> buffer_references;
    std::vector<QTextEdit*> device_references;
    std::vector<QTextEdit*> device_release_time;

    QWaitCondition *waitCond;
    std::vector<Step> steps;
    MainCMOSystem *CMOsystem;

    Cell* cell;

    QTextEdit *mMaxStep;
    QTextEdit *mMinStep;
    QTextEdit *mCurrentStep;

    size_t counter = 0;

    Ui::SecDialog *ui;
};

#endif // SECDIALOG_H
