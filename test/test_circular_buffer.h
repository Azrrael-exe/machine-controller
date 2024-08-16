#include <Arduino.h>
#include <unity.h>
#include "CircularBuffer.h"

CircularBuffer<int, 5> buffer;

void setUpCircularBuffer(void) {}

void tearDownCircularBuffer(void) {}

void test_buffer_initially_empty(void) {
    TEST_ASSERT_TRUE(buffer.empty());
    TEST_ASSERT_EQUAL(0, buffer.size());
}

void test_push_and_pop_single_element(void) {
    buffer.push(42);
    TEST_ASSERT_FALSE(buffer.empty());
    TEST_ASSERT_EQUAL(1, buffer.size());
    TEST_ASSERT_EQUAL(42, buffer.pop());
    TEST_ASSERT_TRUE(buffer.empty());
}

void test_push_until_full(void) {
    for (int i = 0; i < 5; i++) {
        buffer.push(i);
    }
    TEST_ASSERT_TRUE(buffer.full());
    TEST_ASSERT_EQUAL(5, buffer.size());
}

void test_overwrite_oldest_element(void) {
    // Buffer should contain [0, 1, 2, 3, 4] from previous test
    buffer.push(5);
    TEST_ASSERT_EQUAL(5, buffer.size());
    TEST_ASSERT_EQUAL(1, buffer[0]);
    TEST_ASSERT_EQUAL(5, buffer[4]);
}

void test_mean_calculation(void) {
    // Buffer should contain [1, 2, 3, 4, 5] from previous tests
    TEST_ASSERT_EQUAL(3, buffer.mean());
}

void test_index_operator(void) {
    for (int i = 0; i < 5; i++) {
        TEST_ASSERT_EQUAL(i + 1, buffer[i]);
    }
}

void test_clear(void) {
    buffer.clear();
    TEST_ASSERT_TRUE(buffer.empty());
    TEST_ASSERT_EQUAL(0, buffer.size());
}

void run_circular_buffer_tests() {
    RUN_TEST(test_buffer_initially_empty);
    RUN_TEST(test_push_and_pop_single_element);
    RUN_TEST(test_push_until_full);
    RUN_TEST(test_overwrite_oldest_element);
    RUN_TEST(test_mean_calculation);
    RUN_TEST(test_index_operator);
}
