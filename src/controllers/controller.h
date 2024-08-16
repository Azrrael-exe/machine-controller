#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include "units/Singal.h"

template <typename T>
class Controller
{   
    public:
    Controller(){};
    virtual Signal control(T input, T setpoint) = 0;
};

#endif // CONTROLLER_H