#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../TDD_DeviceDriver_KATA/device_driver.cpp"
#include "mock_flash_memory_device.cpp"

using testing::_;
using testing::Return;

class DeviceDriverTestFixture : public testing::Test {
public:
	MockFlashMemoryDevice mock_device;
	DeviceDriver app{ &mock_device };

	const int EMPTY_AREA_VALUE = 0xFF;
};

TEST_F(DeviceDriverTestFixture, ReadZeroTest) {
	EXPECT_CALL(mock_device, read(_))
		.Times(5)
		.WillRepeatedly(Return(0x00));

	EXPECT_EQ(app.read(0x00), 0x00);
}

TEST_F(DeviceDriverTestFixture, ReadFailExceptionTest) {
	EXPECT_CALL(mock_device, read(_))
		.WillOnce(Return(1))
		.WillRepeatedly(Return(0x00));

	EXPECT_THROW(app.read(0x00), ReadFailException);
}

TEST_F(DeviceDriverTestFixture, WriteAtEmptyArea) {
	EXPECT_CALL(mock_device, read(_))
		.Times(5)
		.WillRepeatedly(Return(EMPTY_AREA_VALUE));

	app.write(0x00, 0x05);
}

TEST_F(DeviceDriverTestFixture, WriteAtAlreadyFilledArea) {
	EXPECT_CALL(mock_device, read(_))
		.Times(5)
		.WillRepeatedly(Return(0x00));

	EXPECT_THROW(app.write(0x00, 0x05), WriteFailException);
}


GTEST_API_ int main(int argc, char** argv) {
	std::cout << "Running main() from gmock_main.cc\n";
	// Since Google Mock depends on Google Test, InitGoogleMock() is
	// also responsible for initializing Google Test.  Therefore there's
	// no need for calling testing::InitGoogleTest() separately.
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
