#ifndef RESULTSTABLE_H
#define RESULTSTABLE_H

#include <QWidget>
#include <QTableWidget>
#include <generator.hpp>

namespace Ui {
class resultsTable;
}

class resultsTable : public QWidget
{
    Q_OBJECT

public:
    explicit resultsTable(QWidget *parent = nullptr);
    ~resultsTable();

    void initTable(int generators,int device);
    void insertRow(int generated, int processed, int rejected, double timeInSystem,
                   double processTime, double tof, double top);

    void insertDevice(double usage);
    void insertAverageResults();

private:
    Ui::resultsTable *ui;
    QTableWidget *table;
    QTableWidget *devices;

    int generated;
    int rejected;
    int processed;

    double rejectProb;
    double timeInSystem;
    double waitDisp;
    double servDisp;

    int row;
    int drow;
};

#endif // RESULTSTABLE_H
