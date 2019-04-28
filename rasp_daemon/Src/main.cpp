#include "main.h"


struct BCM2835_Peripheral gpio = { GPIO_BASE };


int main(void)
{
    //Database sql("tcp://192.168.10.48:3306", "root", "", "home_automation");
    Serial serial(B9600);
    RF_Module RF;
    CyclicRedundancyCheck CRC;
    
    std::string SerialBuffer;
    std::string acknowledgement;

    MapPeripheral(&gpio);
    
    RF.Init();
    
    serial.OpenPort();
    serial.Init();
    
    RF.SetTransmissionMode();
    
    while (1)
    {
        RF.SetReceiverMode();
        serial.ClearBuffer();
        SerialBuffer = serial.ReadPort();

        std::cout << SerialBuffer << std::endl;
        if (CRC.VerifyData(SerialBuffer))
        {
            acknowledgement = "ACK";
        }
        else
        {
            acknowledgement = "NAK";
        }
        
        RF.SetTransmissionMode();
        serial.WritePort(acknowledgement);
    }

    serial.ClosePort();
    UnmapPeripheral(&gpio);
    
	return 0;
}
