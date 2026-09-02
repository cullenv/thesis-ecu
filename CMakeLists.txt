# 1. State the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)
project(ThesisECU C CXX) # C and CXX which is c++ which is the tests.

#2. Our firmware creation
add_executable(ecu_firmware app/main.c)

# 3. Test only executable creation
add_executable(run_tests 
    tests/test_dummy.cpp
    tests/mocks/MockPWM.cpp
    tests/mocks/MockADC.cpp
    app/scheduler.c
)

# Add coverage tracking during compilation
target_compile_options(run_tests PRIVATE --coverage)

# Add coverage library during linking
target_link_options(run_tests PRIVATE --coverage)

# 4. Link the test executable to the CppUTest framework
target_link_libraries(run_tests CppUTest CppUTestExt)