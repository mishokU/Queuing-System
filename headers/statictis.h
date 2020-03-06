#ifndef STATICTIS_H
#define STATICTIS_H


class Step{
public :
    Step();

    Step(int command, int number, int generator, double time);
    Step(int command, int number, int generator, double time, int reference);
    Step(int command, int generator, double time,double systemTime);

    ~Step();


    int getCommand();
    int getNumber();
    int getGenerator();
    int getReference();
    double getSystemTime();

    double getTime();

private :
    int command     = 0;
    int number      = 0;
    int reference   = 0;
    int generator   = 0;
    double systemTime = 0;
    double time     = 0;
};

#endif // STATICTIS_H
