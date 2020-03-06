#ifndef MYBUFFER_HPP
#define MYBUFFER_HPP

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <QTime>
#include <QCoreApplication>

#include "generator.hpp"
#include "statictis.h"
#include "device.hpp"
#include "cell.hpp"


typedef std::vector<Cell>::iterator BuffIterator;


class Buffer {

  public:

    Buffer(int capacity);
    ~Buffer();

    void addRequest(Request &request);
    void rejectRequest();
    void replaceRejected(Request &request);

    void increaseBuffIterator();
    bool hasEmptyCell();
    void setStartIter();
    void setSystemTime();

    void setStatistics(std::vector<Step> *steps);

    bool getAllCells();

    Cell getCurrentStateRequest();
    Request& getFindedRequest();
    void setFindedRequest();

    bool empty();
    BuffIterator& getRingIterator();
    Cell& getRequestWithPriority();

private:
    //Useless variable
    std::vector<Cell> cells;
    unsigned long index;
    Cell* tmpCell;
    std::vector<Step> *stepts;
    BuffIterator tmpRinfIterator;
    Request* request;
    BuffIterator ringIterator;
};

#endif
