#ifndef PROPORTIONA_TEMPERATURE_CONTROLLER_H
#define PROPORTIONA_TEMPERATURE_CONTROLLER_H

#include <Arduino.h>
#include "controllers/Controller.h"
#include "units/Singal.h"
#include "units/Temperature.h"

class ProportionlTemperatureController : public Controller<Temperature>
{
    private:
        float kp;
    public:
    ProportionlTemperatureController(int8_t id_cont, float kp) : Controller<Temperature>(id_cont) {
        this->kp = kp;

    }
    Signal control(Temperature input, Temperature setpoint) override
    {
        Temperature error = setpoint - input;
        float output = this->kp * error.getValue();
        return Signal(output, this->id_cont);
    }
};

#endif // PROPORTIONA_TEMPERATURE_CONTROLLER_H