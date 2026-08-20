#include "CppUTest/CommandLineTestRunner.h"

/* This creates a "Group" of tests to run together. You can have multiple groups 
of tests in a single file. Then you can test indiviual drivers */
TEST_GROUP(DummyGroup) {
    void setup() {
        // This runs before every single test
    }
    void teardown() {
        // This runs after every single test
    }
};

// This is the actual test
TEST(DummyGroup, MathShouldWork) {
    CHECK_EQUAL(1, 1);
}

// The main function that runs the framework everytest outside of this
int main(int ac, char** av) {
    return CommandLineTestRunner::RunAllTests(ac, av);
}