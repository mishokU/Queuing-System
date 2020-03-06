#ifndef CELL_HPP
#define CELL_HPP

#include "request.hpp"

class Cell {
public:

    Cell();
    ~Cell();

    void setRequest(Request &request);
    void setEmpty(bool empty);
    void setNumber(int number);

    bool isEmpty();
    int getNumber();
    Request* getRequest();

private:
    Request *request_;
    bool isEmpty_;
    int number;
};

#endif // CELL_HPP
