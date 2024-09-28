#include <Arduino.h>
#include "settings.h"
#include "sensors/temperatureSensor.h"
#include "controllers/proportional.h"
#include "processJson.h"
#include "serializers/serializers.h"

#include <WiFiS3.h>
#include <PubSubClient.h>

const char* ssid = "Azrrael";
const char* password = "3006750425ABC";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic_pub = "sda-2024/20240928";
const char* mqtt_topic_sub = "sda/test-iot/control";

WiFiClient wifiClient;
PubSubClient client(wifiClient);

TemperatureSensor tempSensor(Settings::TEMP_SENSOR_ID, A0);
ProportionlTemperatureController controller(0x00, 0.5);

void reconnect() {
    while (!client.connected()) {
        Serial.print("Intentando conexion MQTT...");
        String clientId = "ArduinoClient-" + String(random(0xffff), HEX);
        if (client.connect(clientId.c_str())) {
            Serial.println("conectado");
        } else {
            Serial.print("fallo, rc=");
            Serial.print(client.state());
            Serial.println(" intentando de nuevo en 5 segundos");
            delay(5000);
        }
    }
}

void setup_wifi() {
    delay(10);
    Serial.println("Conectando a WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi conectado");
    Serial.println("Dirección IP: ");
    Serial.println(WiFi.localIP());
}

void setup() {
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, mqtt_port);
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
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
    Serial.println(jsonString);
    client.publish(mqtt_topic_pub, jsonString.c_str());

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