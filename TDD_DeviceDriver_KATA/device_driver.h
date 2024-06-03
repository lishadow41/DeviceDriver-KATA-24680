#pragma once
#include "flash_memory_device.h"

#include <stdexcept>

class ReadFailException
    : public std::exception
{
public:
    explicit ReadFailException(char const* const _Message)
        : std::exception(_Message) {}
};

class WriteFailException
    : public std::exception
{
public:
    explicit WriteFailException(char const* const _Message)
        : std::exception(_Message) {}
};

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};
