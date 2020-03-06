#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iomanip>
#include "generator.hpp"

class Request {
public:

    Request();
    ~Request();

    void setGenerator(Generator *generator_);
    Generator* getGenerator();

    void setGeneratedTime(const double gen_time);
    double getGeneratedTime();

    void setWaitingTime(double waiting_time);
    double getWaitingTime();

    void setFullTime(double full_time);
    double getFullTime();

private:
    Generator* mGenerator;
    double mGeneratedTime;
    double mWaitingTime;
    double mFullTime;
};


#endif // REQUEST_HPP
