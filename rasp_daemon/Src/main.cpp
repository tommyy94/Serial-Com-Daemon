#include "main.h"

struct BCM2835_Peripheral gpio = { GPIO_BASE };

int main(void)
{
    Database sql("tcp://192.168.10.48:3306", "root", "", "home_automation");
    Serial serial(B9600);
    RF_Module RF;

    MapPeripheral(&gpio);
    
    RF.Init();
    
    // Initialize serial connection
    serial.OpenPort();
    serial.Init();
    int ser_fd = serial.fd();
    
    RF.SetTransmissionMode();
    RF.SetReceiverMode();
    
    while (1)
    {
//        if (!write(ser_fd, "ABC", 3))
//        {
//            std::cerr << "Error writing serial port!\nerrno:" << errno << std::endl;
//        }
    
        //RF.SetReceiverMode();
        if (read(ser_fd, serial.m_buf, serial.BUFFLEN) > 0)
        {
            std::cout << "Serial data: " << serial.m_buf << std::endl;
        }
        else
        {
            std::cerr << "Error reading serial port!\nerrno:" << errno << std::endl;
        }
        
        usleep(100000);
    }
    	
    close(ser_fd);
    UnmapPeripheral(&gpio);
    
	return 0;
}
