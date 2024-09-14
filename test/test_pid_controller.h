#ifndef TEST_PID_CONTROLLER_H
#define TEST_PID_CONTROLLER_H

#include <Arduino.h>
#include <unity.h>
#include "controllers/PID.h"
#include "units/Temperature.h"

namespace pid_temperature_controller {

    // Test de inicialización y valores por defecto
    void test_initialization() {
        PIDTemperatureController controller(0x01, 1.0, 0.1, 0.01);
        
        // Verificar que los parámetros iniciales se han establecido correctamente
        TEST_ASSERT_EQUAL_FLOAT(1.0, controller.getKp());
        TEST_ASSERT_EQUAL_FLOAT(0.1, controller.getKi());
        TEST_ASSERT_EQUAL_FLOAT(0.01, controller.getKd());
        TEST_ASSERT_EQUAL_FLOAT(0.0, controller.getPreviousError());
        TEST_ASSERT_EQUAL_FLOAT(0.0, controller.getIntegral());
        TEST_ASSERT_GREATER_THAN(0, millis() - controller.getPreviousTime()); // Asegurarse de que el tiempo se ha inicializado
    }

    // Test de cálculo de error y actualización de parámetros
    void test_control_parameters() {
        PIDTemperatureController controller(0x01, 2.0, 0.5, 0.1);
        Temperature input(20.0, 0x01);
        Temperature setpoint(25.0, 0x01);
        
        // Ejecutar control para actualizar parámetros
        controller.control(input, setpoint);
        
        // Verificar valores después del primer control
        TEST_ASSERT_NOT_EQUAL_FLOAT(0.0, controller.getPreviousError());  // Error debería cambiar después de la primera llamada
        TEST_ASSERT_NOT_EQUAL_FLOAT(0.0, controller.getIntegral());        // Integral debería ser actualizado
        TEST_ASSERT_GREATER_THAN(0, millis() - controller.getPreviousTime()); // Asegurarse de que el tiempo se ha actualizado
    }

    void run_tests() {
        RUN_TEST(test_initialization);
        RUN_TEST(test_control_parameters);
    }
}

#endif // TEST_PID_CONTROLLER_H
