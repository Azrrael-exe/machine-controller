#ifndef TEST_ABSTRACT_SENSOR_H
#define TEST_ABSTRACT_SENSOR_H

#include <Arduino.h>
#include <unity.h>
#include "sensors/AbstractSensor.h"
#include "Read.h"


class TestRead : public Read<float> {
    public:
        TestRead(float value, uint8_t source) : Read<float>(value, ADIMENTIONAL, source) {}
};

class TestSensor : public Sensor<TestRead, float, 5> {
    public:
        TestSensor(uint8_t id) : Sensor<TestRead, float, 5>(id) {}
        float read() override {
            return 0.7;
        }

        TestRead getRead() override {
            return TestRead(this->buffer[0], this->id);
        }
};

void test_initial_state() {
    TestSensor sensor(0xAA);
    sensor.takeSample();
    TEST_ASSERT_EQUAL(TestRead(0.7, 0xAA).getValue(), sensor.getRead().getValue());
    TEST_ASSERT_EQUAL(ADIMENTIONAL, sensor.getRead().getUnits());
    TEST_ASSERT_EQUAL(0xAA, sensor.getId());
}


void run_sensor_tests() {
    RUN_TEST(test_initial_state);
}

#endif // TEST_ABSTRACT_SENSOR_H