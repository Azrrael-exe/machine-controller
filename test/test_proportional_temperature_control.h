#ifndef TEST_POPORTIONAL_TEMPERATURE_CONTROLLER_H
#define TEST_POPORTIONAL_TEMPERATURE_CONTROLLER_H

#include <Arduino.h>
#include <unity.h>
#include "controllers/proportional.h"
#include "units/Temperature.h"

namespace proportional_temperature_controller {

    void test_initial_state() {
        ProportionlTemperatureController controller(0x00,1.0);
        Temperature input(25.0, 0x00);
        Temperature setpoint(25.0, 0x00);
        Signal output = controller.control(input, setpoint);
        TEST_ASSERT_EQUAL(0.0, output.getValue());
    }

    void run_tests() {
        RUN_TEST(test_initial_state);
    }
} 

#endif // TEST_POPORTIONAL_TEMPERATURE_CONTROLLER_H