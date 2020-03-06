#include "generator.hpp"

//Constructor
Generator::Generator() {
  generatedRequests = 0;
  countOfProcessedApplications = 0;
  countOfRejectedApplications = 0;
  lyambda = 0;

  arrivalTime = 0.0;
  waitingTime = 0.0;
  workingTime = 0.0;

  countOfGeneratedRequests = 0;

  alpha = 0;
  beta = 0;

  productionNumber = 0;
  fullRequests = 0;

}

//Destructor
Generator::~Generator() {

}

//Method
void Generator::generateRequest(){
  //(static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX))
    //static_cast<double>(qrand()) / static_cast<double>(RAND_MAX) * (beta - alpha) + alpha;
  arrivalTime += (double)alpha + (double)(beta - alpha) * (std::rand() % 100) / 100;
  ++countOfGeneratedRequests;
}

int Generator::getCountOfGeneratedRequests() {
    return countOfGeneratedRequests;
}

//Setters
void Generator::setGeneratedRequests(int generatedRequests_){
  generatedRequests += generatedRequests_;
}

void Generator::setCountOfProcessedApplications(int processedApplications){
  countOfProcessedApplications += processedApplications;
}

void Generator::setFullRequests(int request_){
   fullRequests = request_;
}

void Generator::setCountOfRejectedApplications(int rejectedApplications){
  countOfRejectedApplications += rejectedApplications;
}

void Generator::setWorkingTime(double time){
    workingTime += time;
}

void Generator::setLyambda(double lyambda_){
  lyambda = lyambda_;
}

void Generator::setAlpha(double alpha_){
    alpha = alpha_;
}

void Generator::setBeta(double beta_) {
    beta = beta_;
}

void Generator::setArrivalTime(double arrivalTime_){
  arrivalTime = arrivalTime_;
}

void Generator::setWaitingTime(double waitingTime_){
  waitingTime += waitingTime_;
}

void Generator::setProductionNumber(int number) {
  productionNumber = number;
}

//Getters
int Generator::getGeneratedRequests(){
  return generatedRequests;
}

int Generator::getProductionNumber(){
    return productionNumber;
}

bool Generator::isWorking(){
    return generatedRequests < fullRequests;
}

int Generator::getCountOfProcessedApplications(){
  return countOfProcessedApplications;
}

int Generator::getCountOfRejectedApplications(){
  return countOfRejectedApplications;
}

double Generator::getLyambda(){
  return lyambda;
}

double Generator::getArrivalTime(){
  return arrivalTime;
}

double Generator::getWaitingTime(){
  return waitingTime;
}

double Generator::getAlpha() {
    return alpha;
}

double Generator::getWorkingTime(){
    return workingTime;
}

double Generator::getBeta() {
    return beta;
}
