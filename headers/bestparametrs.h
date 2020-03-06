#ifndef BESTPARAMETRS_H
#define BESTPARAMETRS_H

#include <QWidget>
#include <QTableWidget>

namespace Ui {
class BestParametrs;
}

class BestParametrs : public QWidget
{
    Q_OBJECT

public:
    explicit BestParametrs(QWidget *parent = nullptr);
    ~BestParametrs();

    void initTable(size_t modeling);
    void insertRow(int generators, int buffers, int devices, int requests, double l, double alpha,double beta,double rejectProb, double waitProb, double deviceUs);

private:
    QTableWidget *table;
    Ui::BestParametrs *ui;
    int row;
};

#endif // BESTPARAMETRS_H
