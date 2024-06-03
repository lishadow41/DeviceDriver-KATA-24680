
#include "device_driver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int result = m_hardware->read(address);
    for (int i = 0; i < 4; i++) {
        if (result != m_hardware->read(address)) {
            throw ReadFailException("Flash-Memory read another value!");
        }
    }
    return result;
}

void DeviceDriver::write(long address, int data)
{
    int result = read(address);
    if (result != 0xFF) {
        throw WriteFailException("Already Filled Area!");
    }
    m_hardware->write(address, (unsigned char)data);
}
