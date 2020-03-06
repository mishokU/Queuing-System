    #include "cmo_system.hpp"

MainCMOSystem::MainCMOSystem(){

  buffer = nullptr;
  requests.clear();

  generators.clear();
  devices.clear();

  numberOfRequests = 0;
  //maxTime = 0;

  find = false;

  steps = nullptr;

  lyambda = 0;
  beta = 0;
  alpha = 0;
  requestCount = 0;
  firstReq = 0;
  systemTime = 0;
}

MainCMOSystem::~MainCMOSystem(){

  if(buffer)
    delete buffer;

  generators.clear();
  devices.clear();
}

void MainCMOSystem::init(std::vector<double> values){

  generators.resize(static_cast<unsigned long>(values.at(0)));
  buffer = new Buffer(static_cast<int>(values.at(1)));
  devices.resize(static_cast<unsigned long>(values.at(2)));
  requestCount = static_cast<size_t>(values.at(3));
  alpha = values.at(4);
  beta = values.at(5);
  lyambda = values.at(6);

  deviceRingIterator = devices.begin();

  int numberD = 1;
  for(auto &dev : devices){
    dev.setProductionNumber(numberD);
    ++numberD;
  }

  int number = 1;

  for(auto &gen : generators){
      gen.setLyambda(lyambda);
      gen.setFullRequests(requestCount);
      gen.setProductionNumber(number);
      gen.setAlpha(alpha);
      gen.setBeta(beta);

      ++number;
  }
}

void MainCMOSystem::generateAllRequests(){
    while(getAllProcessedApplications() < requestCount) {
        for(auto &generator: generators) {

            generator.generateRequest();
            generator.setGeneratedRequests(1);

            Request request;
            request.setGeneratedTime(generator.getArrivalTime());
            request.setGenerator(&generator);

            requests.push_back(request);

            if(getAllProcessedApplications() >= requestCount) {
                break;
            }
        }

        std::sort(requests.begin(), requests.end(), [](Request &req1, Request &req2) {
            return req1.getGeneratedTime() < req2.getGeneratedTime();
        });
    }
}

void MainCMOSystem::setSteps(std::vector<Step> *steps){
    this->steps = steps;
    buffer->setStatistics(steps);
}

void MainCMOSystem::start(){
    //std::cout << "Modeling..." << std::endl;

    // 1)Генерируем время всех заявок
    // 2)Пока не закончились заявки, то в буфер, если в буфере больше, чем 1 заявка, то добавляем ко всем остальным время пришедшей - время текущих(время ожидания)
    // 3)Буфер будет заполняться, пока хотя бы одна заявка не будет с большим временем жизни + временем ожидания больше, чем время освобождения прибора
    // 4)Прибор будет освобождаться из времени заявки + времени работы прибора

    for(auto &request : requests) {
        //std::cout << "------- request in system -------" << std::endl;

        systemTime = request.getGeneratedTime();

        if(steps != nullptr) {
           steps->push_back({0,request.getGenerator()->getProductionNumber(),request.getGeneratedTime(), systemTime});
        }

        if(buffer->hasEmptyCell()) {
           buffer->addRequest(request);
        } else {
           buffer->rejectRequest();
           buffer->replaceRejected(request);
        }

        buffer->setStartIter();
        find = false;

        putRequestToDevice(buffer->getRequestWithPriority());

        buffer->setStartIter();
        find = false;
    }


    while(!buffer->empty()){
        Cell &cell = buffer->getRequestWithPriority();

        cell.getRequest()->getGenerator()->setWaitingTime(std::abs(cell.getRequest()->getGeneratedTime() - deviceRingIterator->getReleaseTime()));
        cell.getRequest()->getGenerator()->setCountOfProcessedApplications(1);

        deviceRingIterator->work(cell.getRequest(),systemTime);

        cell.setEmpty(true);
        increaseDeviceIter();

        if(steps != nullptr) {
            steps->push_back({2, cell.getNumber(),
                                 cell.getRequest()->getGenerator()->getProductionNumber(),
                                 cell.getRequest()->getGeneratedTime(),
                                 buffer->getRingIterator()->getNumber()});

            steps->push_back({3, deviceRingIterator->getProductionNumber(),
                                 cell.getRequest()->getGenerator()->getProductionNumber(),
                                 cell.getRequest()->getGeneratedTime(),
                                 deviceRingIterator->getProductionNumber()});

            steps->push_back({4, deviceRingIterator->getProductionNumber(), deviceRingIterator->getReleaseTime(),systemTime});
        }

    }

    maxTime = 0;
    for(auto& dev: devices){
        if(dev.getReleaseTime() > maxTime){
           std::cout << "rel time: " << dev.getReleaseTime() << "\n";
           maxTime = dev.getReleaseTime();
        }
    }
    maxTime -= firstReq;
    std::cout << "max time: " << maxTime << std::endl;
}

void MainCMOSystem::putRequestToDevice(Cell &cell){

    for(deviceIterator device = deviceRingIterator; device != devices.end(); ++device){
        if(device->getReleaseTime() <= cell.getRequest()->getGeneratedTime() || (systemTime > device->getReleaseTime())){

           cell.getRequest()->getGenerator()->setWaitingTime(std::abs(cell.getRequest()->getGeneratedTime() - device->getReleaseTime()));

           device->work(cell.getRequest(),systemTime);

           if(firstReq == 0.0){
              firstReq = device->getReleaseTime();
           }

           cell.getRequest()->getGenerator()->setCountOfProcessedApplications(1);
           cell.setEmpty(true);
           deviceRingIterator = device;
           increaseDeviceIter();
           find = true;
           if(steps != nullptr) {
               steps->push_back({2, cell.getNumber(),
                                    cell.getRequest()->getGenerator()->getProductionNumber(),
                                    cell.getRequest()->getGeneratedTime(),
                                    buffer->getRingIterator()->getNumber()});

               steps->push_back({3, device->getProductionNumber(),
                                    cell.getRequest()->getGenerator()->getProductionNumber(),
                                    cell.getRequest()->getGeneratedTime(),
                                    deviceRingIterator->getProductionNumber()});

               steps->push_back({4, device->getProductionNumber(), device->getReleaseTime(),systemTime});
           }

           break;
        }
    }

    if(!find) {
        for(deviceIterator device = devices.begin(); device != deviceRingIterator; ++device){
            if(device->getReleaseTime() <= cell.getRequest()->getGeneratedTime() || (systemTime > device->getReleaseTime())){

               cell.getRequest()->getGenerator()->setWaitingTime(std::abs(cell.getRequest()->getGeneratedTime() - device->getReleaseTime()));

               device->work(cell.getRequest(),systemTime);
               cell.getRequest()->getGenerator()->setCountOfProcessedApplications(1);
               cell.setEmpty(true);
               deviceRingIterator = device;
               increaseDeviceIter();
               find = true;

               if(steps != nullptr) {
                   steps->push_back({2, cell.getNumber(),
                                        cell.getRequest()->getGenerator()->getProductionNumber(),
                                        cell.getRequest()->getGeneratedTime(),
                                        buffer->getRingIterator()->getNumber()});

                   steps->push_back({3, device->getProductionNumber(),
                                        cell.getRequest()->getGenerator()->getProductionNumber(),
                                        cell.getRequest()->getGeneratedTime(),
                                        deviceRingIterator->getProductionNumber()});

                   steps->push_back({4, device->getProductionNumber(), device->getReleaseTime(),systemTime});
               }
               break;
            }
        }
    }

    if(!buffer->getAllCells() && !find){
        putRequestToDevice(buffer->getRequestWithPriority());
    }
}

size_t MainCMOSystem::getCountGenerators(){
    return generators.size();
}

void MainCMOSystem::increaseDeviceIter(){
    deviceRingIterator->getProductionNumber() == devices.size() ? deviceRingIterator = devices.begin() : ++deviceRingIterator;
}

int MainCMOSystem::getAllProcessedApplications(){
    int sum = 0;
    for(auto &gen : generators) {
       sum += gen.getCountOfGeneratedRequests();
    }
    return sum;
}

double MainCMOSystem::getMaxRealizationTime(){
    std::cout << "maxTime: " << maxTime << std::endl;
    return maxTime;
}

double MainCMOSystem::getSystemTime(){
    return systemTime;
}

size_t MainCMOSystem::getCountDevices(){
    return devices.size();
}

std::vector<Device>& MainCMOSystem::getDevices(){
    return devices;
}

std::vector<Generator>& MainCMOSystem::getResults(){

    return generators;
}
