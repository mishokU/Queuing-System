#include "request.hpp"

Request::Request() {
    mGenerator = nullptr;
    mGeneratedTime = 0;
    mWaitingTime = 0;
    mFullTime = 0;
}

Request::~Request() {

}

void Request::setGenerator(Generator* generator){
    mGenerator = generator;
    setGeneratedTime(mGenerator->getArrivalTime());
}

void Request::setGeneratedTime(const double gen_time) {
    mGeneratedTime = gen_time;
}

void Request::setWaitingTime(double waiting_time) {
    mWaitingTime = waiting_time - mGeneratedTime;
}

void Request::setFullTime(double full_time) {
    mFullTime += full_time;
}

Generator* Request::getGenerator() {
    return mGenerator;
}

double Request::getFullTime() {
    return mGeneratedTime + mWaitingTime;
}

double Request::getWaitingTime() {
    return mWaitingTime;
}

double Request::getGeneratedTime() {
    return mGeneratedTime;
}



