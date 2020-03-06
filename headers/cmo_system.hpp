#ifndef CMOSYSTEM
#define CMOSYSTEM


#include <list>
#include <QTextEdit>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <QTime>

#include "device.hpp"
#include "statictis.h"
#include "buffer.hpp"
#include "generator.hpp"
#include "request.hpp"
#include "cell.hpp"

class MainCMOSystem {

  public:

    MainCMOSystem();
    ~MainCMOSystem();

    typedef std::vector<Device>::iterator deviceIterator;

    void init(std::vector<double> values);
    void setSteps(std::vector<Step> *steps);
    void generateAllRequests();
    void start();

    void putRequestToDevice(Cell &cell);

    void increaseDeviceIter();

    size_t getCountGenerators();
    size_t getCountDevices();

    double getMaxRealizationTime();
    double getSystemTime();

    int getAllProcessedApplications();

    std::vector<Generator>& getResults();
    std::vector<Device>& getDevices();

  private:
    Buffer* buffer;
    deviceIterator deviceRingIterator;

    std::vector<Generator> generators;
    std::vector<Device> devices;
    std::vector<Request> requests;

    std::vector<Step> *steps;

    Request* request;

    bool find;

    int numberOfRequests;
    int requestCount;
    double systemTime;
    double firstReq;
    double maxTime;
    double lyambda;
    double alpha;
    double beta;
};

#endif //CMOSYSTEM
