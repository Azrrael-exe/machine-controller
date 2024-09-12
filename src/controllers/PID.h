#ifndef PID_TEMPERATURE_CONTROLLER_H
#define PID_TEMPERATURE_CONTROLLER_H

#include <Arduino.h>
#include "controllers/Controller.h"
#include "units/Singal.h"
#include "units/Temperature.h"

class PIDTemperatureController : public Controller<Temperature>
{
    private:
        float kp;   
        float ki;   
        float kd;   
        float previousError; // Error anterior para la parte derivativa
        float integral;      // Acumulador de la integral
        unsigned long previousTime; // Tiempo anterior para la derivativa
    public:
    PIDTemperatureController(int8_t id_cont, float kp, float ki, float kd) : Controller<Temperature>(id_cont) {
        this->kp = kp;
        this->ki = ki;
        this->kd = kd;
        this->previousError = 0;
        this->integral = 0;
        this->previousTime = millis();
    }

    Signal control(Temperature input, Temperature setpoint) override
    {
        // Cálculo del error
        Temperature error = setpoint - input;

        // Tiempo actual y delta de tiempo
        unsigned long currentTime = millis();
        float deltaTime = (currentTime - previousTime) / 1000.0; // Convertir a segundos
        previousTime = currentTime;

        // Parte proporcional
        float P = this->kp * error.getValue();

        // Parte integral
        this->integral += error.getValue() * deltaTime;
        float I = this->ki * this->integral;

        // Parte derivativa
        float derivative = (error.getValue() - this->previousError) / deltaTime;
        float D = this->kd * derivative;
        this->previousError = error.getValue();

        // Salida total
        float output = P + I + D;
        return Signal(output, this->id_cont);
    }
};

#endif // PID_TEMPERATURE_CONTROLLER_H