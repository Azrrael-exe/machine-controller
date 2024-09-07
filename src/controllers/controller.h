#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include "units/Singal.h"

template <typename T>
class Controller
{   
protected:
    int8_t id_cont;

public:
    Controller(int8_t id_cont) {
        this->id_cont = id_cont;
    }

    virtual Signal control(T input, T setpoint) = 0;

    int8_t getIdCont() const {
        return this->id_cont;
    }
};

#endif // CONTROLLER_H