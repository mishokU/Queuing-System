    #include "device.hpp"

Device::Device(){
  waitingTime = 0.0;
  workingTime = 0.0;
  releaseTime = 0.0;
  currentIndex = 0;
  productionNumber = 0;
  std::srand(time(0));
}

Device::~Device(){

}

//get Requet from generator
void Device::work(Request *request,double systemTime){
  mRequest = *request;
  //(std::log(static_cast<double>(qrand()) + 1) - std::log(static_cast<double>(RAND_MAX))) / -request->getGenerator()->getLyambda();
  double work = (-1.0 / request->getGenerator()->getLyambda()) * std::log(std::rand() / (double)RAND_MAX);
  //double work = (std::log(static_cast<double>(qrand()) + 1) - std::log(static_cast<double>(RAND_MAX))) / -request->getGenerator()->getLyambda();
  std::cout << "Device" << this->getProductionNumber() << " worked: " << work << std::endl;
  std::cout << "System time: " << systemTime << std::endl;
  request->getGenerator()->setWorkingTime(work);
  workingTime += work;

      if(systemTime >= request->getGeneratedTime()){
         releaseTime = work + systemTime;
      }
      else{
         releaseTime = work + request->getGeneratedTime();
     }
  //releaseTime = work + systemTime;
  std::cout << "Освобождение " << productionNumber <<  " прибора в: " << releaseTime << std::endl;
}

void Device::bufferWork(Request *request)
{
    double work = (-1.0 / request->getGenerator()->getLyambda()) * std::log(std::rand() / (double)RAND_MAX);
    request->getGenerator()->setWorkingTime(work);
    workingTime += work;

}

void Device::setWaitingTime(double time) {
  workingTime += time;
}


Request Device::getCurrentRequest(){
    return mRequest;
}

double Device::getReleaseTime() {
    return releaseTime;
}

double Device::getWaitingTime() {
    return waitingTime;
}

double Device::getWorkingTime() {
    return workingTime;
}

int Device::getCurrentIterator() {
    return currentIndex;
}

void Device::setCurrentIterator(int index) {
    currentIndex = index;
}

void Device::setProductionNumber(int number) {
    productionNumber = number;
}

int Device::getProductionNumber() {
    return productionNumber;
}
