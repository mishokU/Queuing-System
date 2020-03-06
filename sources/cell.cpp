#include "cell.hpp"

Cell::Cell() {
    request_ = nullptr;
    isEmpty_ = true;
    number = 0;
}

Cell::~Cell() {

}

void Cell::setEmpty(bool empty) {
    isEmpty_ = empty;
}

int Cell::getNumber() {
    return number;
}

void Cell::setNumber(int number_) {
    number = number_;
}

void Cell::setRequest(Request &request) {
    request_ = &request;
}

bool Cell::isEmpty() {
    return isEmpty_;
}

Request* Cell::getRequest() {
    return request_;
}
