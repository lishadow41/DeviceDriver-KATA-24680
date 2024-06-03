#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../TDD_DeviceDriver_KATA/device_driver.cpp"
#include "mock_flash_memory_device.cpp"

using testing::_;
using testing::Return;

TEST(DeviceDriverTest, ReadZeroTest) {
	MockFlashMemoryDevice mock_device;
	EXPECT_CALL(mock_device, read(_))
		.Times(5)
		.WillRepeatedly(Return(0));

	DeviceDriver app(&mock_device);
	int expected = 0x00;
	int actual = app.read(0x00);

	EXPECT_EQ(actual, expected);
}

TEST(DeviceDriverTest, ReadFailExceptionTest) {
	MockFlashMemoryDevice mock_device;
	EXPECT_CALL(mock_device, read(_))
		.WillOnce(Return(1))
		.WillRepeatedly(Return(0x00));

	DeviceDriver app(&mock_device);

	EXPECT_THROW(app.read(0x00), ReadFailException);
}

TEST(DeviceDriverTest, WriteAtEmptyArea) {
	MockFlashMemoryDevice mock_device;
	EXPECT_CALL(mock_device, read(_))
		.Times(5)
		.WillRepeatedly(Return(0xFF));

	DeviceDriver app(&mock_device);
	app.write(0x00, 0x05);
}

TEST(DeviceDriverTest, WriteAtAlreadyFilledArea) {
	MockFlashMemoryDevice mock_device;
	EXPECT_CALL(mock_device, read(_))
		.Times(5)
		.WillRepeatedly(Return(0));

	DeviceDriver app(&mock_device);
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
