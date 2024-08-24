#include <Arduino.h>
#include <unity.h>
#include "test_abstract_sensor.h"
#include "test_circular_buffer.h"
#include "test_temperature_sensor.h"
#include "test_proportional_temperature_control.h"
#include "test_reads.h"

void setup() {
    delay(2000);
    UNITY_BEGIN();
    
    run_read_tests();
    // run_sensor_tests();
    // temperature_sensor::run_tests();
    // proportional_temperature_controller::run_tests();
    // run_circular_buffer_tests();
    
    UNITY_END();
}

void loop() {
}