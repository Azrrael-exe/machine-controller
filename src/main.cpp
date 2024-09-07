#include <Arduino.h>
#include "settings.h"
#include "sensors/temperatureSensor.h"
#include "controllers/proportional.h"
#include "processJson.h"

TemperatureSensor tempSensor(Settings::TEMP_SENSOR_ID, A0);
ProportionlTemperatureController controller(0x00, 0.5);

void setup() {
    Serial.begin(115200);
}

void loop() {
    
    tempSensor.takeSample();
    Temperature input = tempSensor.getRead();
    Temperature setPoint = Temperature(25.0, 0x00);
    Signal response = controller.control(input, setPoint);

    StaticJsonDocument<200> jsonDoc;
    jsonDoc["error"] = readToJson(response);
    jsonDoc["input"] = readToJson(input);
    jsonDoc["setpoint"] = readToJson(setPoint);
    
    String jsonString;
    serializeJson(jsonDoc, jsonString);
    Serial.println(jsonString);

    delay(1000);
}