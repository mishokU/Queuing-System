#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <math.h>
#include <stdlib.h>

#include <ctime>
#include <iomanip>
#include <iostream>
#include <request.hpp>
#include <QRandomGenerator>


class Device {
  public:

    Device();
    ~Device();

    void work(Request *request,double systemTime);
    void bufferWork(Request *request);
    bool isBusy();

    void setWaitingTime(double time);
    void setProductionNumber(int number);

    Request getCurrentRequest();

    double getWorkingTime();
    double getReleaseTime();
    double getWaitingTime();
    int getProductionNumber();

    int getCurrentIterator();
    void setCurrentIterator(int index);

  private:

    double releaseTime;
    double workingTime;
    double waitingTime;

    Request mRequest;

    int productionNumber;

    int currentIndex;
};

#endif 
