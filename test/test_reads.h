#include <Arduino.h>
#include <unity.h>
#include "Read.h"

void test_read_initialization(void) {
    Read<float> read(42.0, CELSIUS);
    TEST_ASSERT_EQUAL(42.0, read.getValue());
    TEST_ASSERT_EQUAL(CELSIUS, read.getUnits());
}

void test_read_sum(void) {
    Read<float> a(42.0, CELSIUS);
    Read<float> b(42.0, CELSIUS);
    Read<float> c = a + b;
    TEST_ASSERT_EQUAL(84.0, c.getValue());
    Read<float> d = c - b;
    TEST_ASSERT_EQUAL(42.0, d.getValue());
}

void run_read_tests() {
    RUN_TEST(test_read_initialization);
}