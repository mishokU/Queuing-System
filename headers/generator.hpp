#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <QRandomGenerator>
#include <ctime>

class Generator {
  public:

    Generator();
    ~Generator();

    void generateRequest();

    void setGeneratedRequests(int generatedRequests_);
    void setCountOfProcessedApplications(int processedApplications_);
    void setCountOfRejectedApplications(int rejectedApplications_);

    void setLyambda(double lyambda_);
    void setArrivalTime(double arrivalTime_);
    void setWaitingTime(double waitingTime_);
    void setFullRequests(int request_);
    void setProductionNumber(int number);
    void setWorkingTime(double time);

    void setAlpha(double alpha_);
    void setBeta(double beta_);

    int getProductionNumber();
    int getGeneratedRequests();
    int getCountOfProcessedApplications();
    int getCountOfRejectedApplications(); 
    double getLyambda();
    int getCountOfGeneratedRequests();

    double getAlpha();
    double getBeta();

    double getArrivalTime();
    double getWaitingTime();
    double getWorkingTime();

    bool isWorking();
  private:

    int productionNumber;
    int generatedRequests;
    int fullRequests;
    int countOfProcessedApplications;
    int countOfRejectedApplications;

    double lyambda;
    int countOfGeneratedRequests;

    double arrivalTime;
    double waitingTime;
    double serviceTime;
    double workingTime;

    double alpha;
    double beta;
};

#endif //GENERATOR_HPP
