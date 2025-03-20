#ifndef __COMMUNICATION_H__
#define __COMMUNICATION_H__

#include "config.h"
#include "Constants.h"
#include "Stepper.h"
#include "Encoder.h"
#include "Storage.h"

#define NULL_NUMBER 998877

class CommunicationClass
{
public:
    CommunicationClass();
    void init();
    void execute();
private:
    void parseCommand();
    void resetParameters();

    String inputString;
    bool isStringCompleted;
    float M, R, E, P, S, T;
};

extern CommunicationClass Communication;

#endif // __COMMUNICATION_H__