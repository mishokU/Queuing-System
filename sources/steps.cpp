#include "statictis.h"

Step::Step(){

}

Step::Step(int command, int number, int generator, double time, int reference){
    this->command   = command;
    this->number    = number;
    this->generator = generator;
    this->time      = time;
    this->reference = reference;
}

Step::Step(int command, int number, int generator, double time){
    this->command   = command;
    this->number    = number;
    this->generator = generator;
    this->time      = time;
}

Step::~Step(){

}



Step::Step(int command, int generator, double time,double systemTime){
    this->command = command;
    this->generator = generator;
    this->time = time;
    this->systemTime = systemTime;
}

int Step::getReference(){
    return reference;
}

int Step::getCommand(){
    return command;
}

int Step::getNumber(){
    return number;
}

int Step::getGenerator(){
    return generator;
}

double Step::getTime(){
    return time;
}


double Step::getSystemTime(){
    return systemTime;
}
