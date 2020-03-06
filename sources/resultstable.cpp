#include "resultstable.h"
#include "ui_resultstable.h"

resultsTable::resultsTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::resultsTable)
{
    ui->setupUi(this);

    table = ui->tableWidget;
    devices = ui->deviceTable;
    row = 0;
    drow = 0;

    generated = 0;
    rejected = 0;
    rejectProb = 0;
    waitDisp = 0;
    servDisp = 0;
    processed = 0;
    timeInSystem = 0;
}

resultsTable::~resultsTable()
{
    delete ui;
}

void resultsTable::initTable(int generators, int device){
    table->setColumnCount(7);
    table->setRowCount(generators + 1);

    table->setHorizontalHeaderLabels(QStringList() << "Generated"
                                     << "Processed" << "Rejected" << "Reject Prob" << "Time in System"
                                     << "Waiting Disp" << "Servising Disp");

    table->setVerticalHeaderLabels(QStringList() << "Generator 1" << "Generator 2" << "Generator 3" << "Generator 4");

    devices->setColumnCount(1);
    devices->setRowCount(device);

    devices->setHorizontalHeaderLabels(QStringList() << "Usage Devices");

}

void resultsTable::insertDevice(double usage){
    devices->setItem(drow, 0, new QTableWidgetItem(QString::number(usage * 100)));

    ++drow;
}

void resultsTable::insertRow(int generated, int processed, int rejected, double rejectProb, double timeInSystem, double tof, double top){
    this->generated += generated;
    this->processed += processed;
    this->rejected += rejected;
    this-> rejectProb += rejectProb;
    this-> timeInSystem += timeInSystem;
    this->waitDisp += tof;
    this->servDisp += top;

    table->setItem(row,0, new QTableWidgetItem(QString::number(generated)));
    table->setItem(row,1, new QTableWidgetItem(QString::number(processed)));
    table->setItem(row,2, new QTableWidgetItem(QString::number(rejected)));
    table->setItem(row,3, new QTableWidgetItem(QString::number(rejectProb)));
    table->setItem(row,4, new QTableWidgetItem(QString::number(timeInSystem)));
    table->setItem(row,5, new QTableWidgetItem(QString::number(tof)));
    table->setItem(row,6, new QTableWidgetItem(QString::number(top)));
    ++row;
}

void resultsTable::insertAverageResults(){
    table->setItem(row,0, new QTableWidgetItem(QString::number(generated / (table->rowCount() - 1))));
    table->setItem(row,1, new QTableWidgetItem(QString::number(processed / (table->rowCount() - 1))));
    table->setItem(row,2, new QTableWidgetItem(QString::number(rejected / (table->rowCount() - 1))));
    table->setItem(row,3, new QTableWidgetItem(QString::number(rejectProb / (table->rowCount() - 1))));
    table->setItem(row,4, new QTableWidgetItem(QString::number(timeInSystem / (table->rowCount() - 1))));
    table->setItem(row,5, new QTableWidgetItem(QString::number(waitDisp / (table->rowCount() - 1))));
    table->setItem(row,6, new QTableWidgetItem(QString::number(servDisp / (table->rowCount() - 1))));
}
