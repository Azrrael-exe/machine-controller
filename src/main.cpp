#include <Arduino.h>
#include <LiquidCrystal.h>

#include "sensors/temperatureSensor.h"
#include "controllers/proportional.h"


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
TemperatureSensor tempSensor(0xAA, A0);
ProportionlTemperatureController controller(1);

void setup() {
    Serial.begin(115200);
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
    lcd.print("Temp Control");
    delay(2000);
    lcd.clear();
}

void loop() {
    tempSensor.takeSample();
    Temperature input = tempSensor.getRead();
    Signal response = controller.control(input, Temperature(25.0, 0x00));

    Serial.print("Input: ");
    Serial.println(input.getValue());
    Serial.print("Output: ");
    Serial.println(response.getValue());

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(input.getValue());
    lcd.setCursor(0, 1);
    lcd.print(input.getSource());

    delay(1000);
}