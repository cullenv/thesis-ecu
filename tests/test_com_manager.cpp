// tests/test_com_manager.cpp
#include "CppUTest/TestHarness.h"
#include "mocks/MockHalAndServices.h"

extern "C" {
#include "com_manager.h"
}

TEST_GROUP(ComManagerGroup) {
    void setup() override {
        MockCAN_Init();
    }

    void teardown() override {}
};

// Traces to REQ-011: Verify CAN frame ID, DLC, and Big-Endian IEEE-754 byte order
TEST(ComManagerGroup, SendMotorSpeedSerializesFloatBigEndian) {
    // 1000.0f in IEEE-754 32-bit float is 0x447A0000
    COM_SendMotorSpeed(1000.0f);

    LONGS_EQUAL(1, MockCAN_GetTxCount());
    CAN_Message_t frame = MockCAN_GetLastTxFrame();

    // Note: Log Defect #3 in your Defect Log if frame.id is 0x105 instead of REQ-011's 0x101!
    LONGS_EQUAL(0x101, frame.id);
    LONGS_EQUAL(4, frame.dlc);

    // Big-endian byte order verification: MSB in data[0], LSB in data[3]
    BYTES_EQUAL(0x44, frame.data[0]);
    BYTES_EQUAL(0x7A, frame.data[1]);
    BYTES_EQUAL(0x00, frame.data[2]);
    BYTES_EQUAL(0x00, frame.data[3]);
}

TEST(ComManagerGroup, SendZeroMotorSpeedTransmitsAllZeroBytes) {
    COM_SendMotorSpeed(0.0f);

    CAN_Message_t frame = MockCAN_GetLastTxFrame();
    LONGS_EQUAL(4, frame.dlc);
    BYTES_EQUAL(0x00, frame.data[0]);
    BYTES_EQUAL(0x00, frame.data[1]);
    BYTES_EQUAL(0x00, frame.data[2]);
    BYTES_EQUAL(0x00, frame.data[3]);
}