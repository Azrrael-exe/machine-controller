#include <Arduino.h>
#include "sensors/temperatureSensor.h"
#include "controllers/proportional.h"

TemperatureSensor tempSensor(A0);
ProportionlTemperatureController controller(1);

class ByPassController : public Controller<Temperature>
{
public:
    Signal control(Temperature input, Temperature setpoint) override
    {
        return Signal(1);
    }
};

ByPassController controller;

void setup() {
    Serial.begin(115200);
}

void loop() {
    tempSensor.takeSample();
    Temperature input = tempSensor.getRead();
    Signal response = controller.control(input, Temperature(25.0));
    Serial.print("Input: ");
    Serial.println(input.getValue());
    Serial.print("Output: ");
    Serial.println(response.getValue());
    delay(1000);
}