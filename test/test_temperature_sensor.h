#ifndef TEST_TEMPERATURE_SENSOR_H
#define TEST_TEMPERATURE_SENSOR_H

#include <Arduino.h>
#include <unity.h>
#include "sensors/TemperatureSensor.h"
#include "units/Temperature.h"

namespace temperature_sensor {
    void test_initial_state() {
        TemperatureSensor sensor(0x0A, A0);
        sensor.takeSample();
        TEST_ASSERT_EQUAL(Temperature(250.0, 0xAA).getValue(), sensor.getRead().getValue());
        TEST_ASSERT_EQUAL(CELSIUS, sensor.getRead().getUnits());
    }

    void test_read_value() {
        TemperatureSensor sensor(0x0A, A0);
        for(int i = 0; i < 5; i++) {
            sensor.takeSample();
        }
        TEST_ASSERT_EQUAL(Temperature(250.0, 0xAA).getValue(), sensor.getRead().getValue());
    }

    void run_tests() {
        RUN_TEST(test_initial_state);
        RUN_TEST(test_read_value);
    }
} 

#endif // TEST_ABSTRACT_SENSOR_H