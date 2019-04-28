#pragma once
#include <boost/crc.hpp>
#include <iostream>
#include <string>


class CyclicRedundancyCheck
{
private:
    constexpr static int  CRC32_BEGIN = 6;
    constexpr static int  CRC32_LEN = 8;
    constexpr static int BASE16 = 16;
    
public:
    CyclicRedundancyCheck() {};
    int GetCrc32(const void *str, int strLen);
    bool VerifyData(std::string serial_buf);
};
