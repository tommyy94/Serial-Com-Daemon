#include "crc.h"


int CyclicRedundancyCheck::GetCrc32(const void *str, int strLen)
{
    boost::crc_32_type result;
    result.process_bytes(str, strLen);
    return result.checksum();
}


bool CyclicRedundancyCheck::VerifyData(std::string serial_buf)
{
    std::string checksum;
    std::string msg;
    bool result;
    unsigned int msgCrc32;
    unsigned int calcCrc32 = 0;
    unsigned int crc32_pos = serial_buf.find("crc32:");
    
    /* Get message and CRC */
    if (crc32_pos != std::string::npos)
    {
        msg = serial_buf.substr(0, crc32_pos);
        checksum = serial_buf.substr(crc32_pos + CRC32_BEGIN, CRC32_LEN);
        
        try
        {
            calcCrc32 = std::stoi(checksum, 0, BASE16);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << "Invalid argument, conversion could not be performed!" << std::endl;
        }
        catch (std::out_of_range& e)
        {
            std::cerr << "Integer out of range!" << std::endl;
        }
        
        msgCrc32 = GetCrc32(&msg[0], msg.length());
    
        if (msgCrc32 == calcCrc32)
        {
            result = true;
        }
        else
        {
            result = false;
        }
    }
    else
    {
        std::cerr << "Couldn't find CRC!" << std::endl;
        result = false;
    }
    
    return result;
}
