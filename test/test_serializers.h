#include <Arduino.h>
#include <unity.h>
#include "Read.h"
#include "serializers/serializers.h"

void test_byte_serializer(void) {
    Read<uint8_t> read(10, CELSIUS, 0xAA);
    byte* bytes = readToBytes(read);
    Read<uint8_t> read2 = readFromBytes<uint8_t>(bytes);
    TEST_ASSERT_EQUAL(10, read2.getValue());
    TEST_ASSERT_EQUAL(CELSIUS, read2.getUnits());
    TEST_ASSERT_EQUAL(0xAA, read2.getSource());
    TEST_ASSERT_EQUAL(0xAA, bytes[0]);
    TEST_ASSERT_EQUAL(0, bytes[1]);
    TEST_ASSERT_EQUAL(0, bytes[2]);
    TEST_ASSERT_EQUAL(0, bytes[3]);
    TEST_ASSERT_EQUAL(10, bytes[4]);
    TEST_ASSERT_EQUAL(CELSIUS, bytes[5]);
}

void run_serializer_tests() {
    RUN_TEST(test_byte_serializer);
}