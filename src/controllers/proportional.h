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
    ProportionlTemperatureController(float kp) : Controller() {
        this->kp = kp;

    }
    Signal control(Temperature input, Temperature setpoint) override
    {
        Temperature error = setpoint - input;
        float output = this->kp * error.getValue();
        return Signal(output, 0x00);
    }
};

#endif // PROPORTIONA_TEMPERATURE_CONTROLLER_H