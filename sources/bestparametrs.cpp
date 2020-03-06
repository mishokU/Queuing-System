#include "bestparametrs.h"
#include "ui_bestparametrs.h"

BestParametrs::BestParametrs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BestParametrs)
{
    ui->setupUi(this);
    table = ui->tableWidget;
    row = 0;
}

BestParametrs::~BestParametrs()
{
    delete ui;
}

void BestParametrs::initTable(size_t modeling)
{
    table->setColumnCount(10);
    table->setRowCount(static_cast<int>(modeling));

    table->setHorizontalHeaderLabels(QStringList() << "Generators" << "Buffers" << "Devices" <<
                                     "Requests" << "Alpha" << "Beta" << "Lyambda" << "Rejected Prob" << "Waiting Prob" << "Device Us");
}

void BestParametrs::insertRow(int generators, int buffers, int devices, int requests, double alpha, double beta,double l,double rejectProb, double waitProb, double deviceUs)
{
    table->setItem(row,0, new QTableWidgetItem(QString::number(generators)));
    table->setItem(row,1, new QTableWidgetItem(QString::number(buffers)));
    table->setItem(row,2, new QTableWidgetItem(QString::number(devices)));
    table->setItem(row,3, new QTableWidgetItem(QString::number(requests)));
    table->setItem(row,4, new QTableWidgetItem(QString::number(alpha)));
    table->setItem(row,5, new QTableWidgetItem(QString::number(beta)));
    table->setItem(row,6, new QTableWidgetItem(QString::number(l)));
    table->setItem(row,7, new QTableWidgetItem(QString::number(rejectProb * 100)));
    table->setItem(row,8, new QTableWidgetItem(QString::number(waitProb)));
    table->setItem(row,9, new QTableWidgetItem(QString::number(deviceUs * 100)));
    ++row;
}
