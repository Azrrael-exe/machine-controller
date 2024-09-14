#include <Arduino.h>
#include "settings.h"
#include "sensors/temperatureSensor.h"
#include "controllers/proportional.h"
#include "controllers/PID.h"
#include "processJson.h"
#include "serializers/serializers.h"

TemperatureSensor tempSensor(Settings::TEMP_SENSOR_ID, A0);
//ProportionlTemperatureController controller(0x00, 0.5);
PIDTemperatureController Controller(0x00, 0.5, 0.1, 0.05);

void setup() {
    Serial.begin(115200);
}

void loop() {
    
    tempSensor.takeSample();
    Temperature input = tempSensor.getRead();
    Temperature setPoint = Temperature(25.0, 0xAA);
    Signal response = controller.control(input, setPoint);

    StaticJsonDocument<200> jsonDoc;
    jsonDoc["error"] = readToJson(response);
    jsonDoc["input"] = readToJson(input);
    jsonDoc["setpoint"] = readToJson(setPoint);
    
    String jsonString;
    serializeJson(jsonDoc, jsonString);
    // Serial.println(jsonString);

    BytesSerializer<3> serializer = BytesSerializer<3>(0x7E);
    serializer.addRead(input);
    serializer.addRead(setPoint);
    serializer.addRead(response);

    serializer.writeToStream(Serial);

    if (serializer.readIncommingBuffer(Serial)) {
        Serial.println("Data received");
    }

    delay(5000);
}

// 7E 06 0A 00 00 00 02 00 0C