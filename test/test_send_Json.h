#ifndef TEST_SEND_JSON_H
#define TEST_SEND_JSON_H

#include <Arduino.h>
#include <unity.h>
#include "processJson.h"
#include "controllers/proportional.h"
#include "units/Temperature.h"

void test_sendJson() {
    
    ProportionlTemperatureController controller(1, 0.5);

    Temperature setpoint(25.0, 0x00);
    Temperature input(20.0, 0x00);

    Signal response = controller.control(input, setpoint);
    StaticJsonDocument<200> json = readToJson(response);
    String jsonString;
    serializeJson(json, jsonString);
    String expected_json = "{\"id\":1,\"value\":2.5,\"unit\":1}";

    TEST_ASSERT_EQUAL_STRING(expected_json.c_str(), jsonString.c_str());
}

void run_Json_test() {
    RUN_TEST(test_sendJson);
}

#endif // TEST_SEND_JSON_H