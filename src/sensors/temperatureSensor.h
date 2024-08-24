#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H


#include "AbstractSensor.h"
#include "units/Temperature.h"

class TemperatureSensor : public Sensor<Temperature, float, 3> {
private:
    int pin;
    float referenceVoltage;

public:
    TemperatureSensor(uint8_t id, int analogPin, float refVoltage = 5.0): Sensor<Temperature, float, 3>(id) {
        pin = analogPin;
        referenceVoltage = refVoltage;
    }

    float read() override {
        int rawValue = 512; // analogRead(pin);
        float voltage = (rawValue / 1023.0) * referenceVoltage;
        float temperatureCelsius = voltage;
        
        return temperatureCelsius;
    }

    void setPin(int newPin) {
        pin = newPin;
    }

    void setReferenceVoltage(float newVoltage) {
        referenceVoltage = newVoltage;
    }

    Temperature getRead() override {
        return Temperature(buffer.mean(), this->id);
    }
};

#endif // TEMPERATURE_SENSOR_H