#include <Arduino.h>
#include <unity.h>
#include "Read.h"

void test_read_initialization(void) {
    Read<float> read(42.0, CELSIUS, 0xAA);
    TEST_ASSERT_EQUAL(42.0, read.getValue());
    TEST_ASSERT_EQUAL(CELSIUS, read.getUnits());
}

void test_read_sum(void) {
    Read<float> a(42.0, CELSIUS, 0xAA);
    Read<float> b(42.0, CELSIUS, 0xAB);
    Read<float> c = a + b;
    TEST_ASSERT_EQUAL(84.0, c.getValue());
    TEST_ASSERT_EQUAL(0xAA, c.getSource());
    Read<float> d = c - b;
    TEST_ASSERT_EQUAL(42.0, d.getValue());
    TEST_ASSERT_EQUAL(0xAA, d.getSource());
}

void run_read_tests() {
    RUN_TEST(test_read_initialization);
}