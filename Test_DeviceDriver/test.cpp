#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../TDD_DeviceDriver_KATA/device_driver.cpp"

TEST(DeviceDriverTest, DummyTest) {
	DeviceDriver app(nullptr);
}


GTEST_API_ int main(int argc, char** argv) {
	std::cout << "Running main() from gmock_main.cc\n";
	// Since Google Mock depends on Google Test, InitGoogleMock() is
	// also responsible for initializing Google Test.  Therefore there's
	// no need for calling testing::InitGoogleTest() separately.
	testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
