#include <Arduino.h>
#include "settings.h"
#include "sensors/temperatureSensor.h"
#include "controllers/proportional.h"

TemperatureSensor tempSensor(Settings::TEMP_SENSOR_ID, A0);
ProportionlTemperatureController controller(1);

void setup() {
    Serial.begin(115200);
}

void loop() {
    // read_settings 
    tempSensor.takeSample();
    Temperature input = tempSensor.getRead();
    Signal response = controller.control(input, Temperature(25.0, 0x00));

    Serial.print("Input: ");
    Serial.println(input.getValue());
    Serial.print("Output: ");
    Serial.println(response.getValue());

    delay(1000);
}