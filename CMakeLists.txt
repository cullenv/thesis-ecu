cmake_minimum_required(VERSION 3.10)  #gggg
project(ThesisECU C CXX)

# Global architectural include paths
set(ECU_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/app
    ${CMAKE_SOURCE_DIR}/services
    ${CMAKE_SOURCE_DIR}/hal
    ${CMAKE_SOURCE_DIR}/mcal
    ${CMAKE_SOURCE_DIR}/tests/mocks # Intercepts stm32g4xx.h for host builds
)

# ---------------------------------------------------------
# 1. Host Target Firmware Executable
# ---------------------------------------------------------
add_executable(ecu_firmware EXCLUDE_FROM_ALL
    app/main.c
    app/motor_control.c
    app/com_manager.c
    app/pid.c
    app/ramp.c
    services/scheduler.c
    services/fault_manager.c
    mcal/mcal_pwm.c
    mcal/mcal_encoder.c
)

target_include_directories(ecu_firmware PRIVATE ${ECU_INCLUDE_DIRS})

# ---------------------------------------------------------
# 2. Host Unit Testing Executable (CppUTest + gcov)
# ---------------------------------------------------------
add_executable(run_tests
    # Production source units under test
    app/motor_control.c
    app/com_manager.c
    app/pid.c
    app/ramp.c
    services/scheduler.c
    services/fault_manager.c

    # Mocks
    tests/mocks/MockADC.cpp
    tests/mocks/MockPWM.cpp
    tests/mocks/MockHalAndServices.cpp

    # Test Suites
    tests/test_dummy.cpp
    tests/test_scheduler.cpp
    tests/test_motor_control.cpp
    tests/test_com_manager.cpp
)

target_include_directories(run_tests PRIVATE
    ${ECU_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/tests
)

# Compiler & Linker flags for gcov code coverage instrumentation
target_compile_options(run_tests PRIVATE --coverage -Wall -Wextra)
target_link_options(run_tests PRIVATE --coverage)

# CppUTest framework libraries
target_link_libraries(run_tests CppUTest CppUTestExt)