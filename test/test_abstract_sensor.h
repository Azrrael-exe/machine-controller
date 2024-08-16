#ifndef TEST_ABSTRACT_SENSOR_H
#define TEST_ABSTRACT_SENSOR_H

#include <Arduino.h>
#include <unity.h>
#include "sensors/AbstractSensor.h"
#include "Read.h"


class TestRead : public Read<float> {
    public:
        TestRead(float value) : Read<float>(value, ADIMENTIONAL) {}
};

class TestSensor : public Sensor<TestRead, float, 5> {
    public:
        float read() override {
            return 0.7;
        }

        TestRead getRead() override {
            return TestRead(this->buffer[0]);
        }
};

void test_initial_state() {
    TestSensor sensor;
    sensor.takeSample();
    TEST_ASSERT_EQUAL(TestRead(0.7).getValue(), sensor.getRead().getValue());
    TEST_ASSERT_EQUAL(ADIMENTIONAL, sensor.getRead().getUnits());
}


void run_sensor_tests() {
    RUN_TEST(test_initial_state);
}

#endif // TEST_ABSTRACT_SENSOR_H