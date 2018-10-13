#include "main.h"


int main(void)
{
	Serial serial(B9600);
	Database sql("tcp://192.168.10.48:3306", "root", "", "home_automation");
	Temperature temp;
	
	std::string query;
	int adc_value;
	
	// Initialize serial connection
	int fd = serial.open_port();
	serial.con_init(fd);
			
	while (1)
	{
		// Read sensor value from serial port
		if (read(fd, serial.m_buf, serial.BUFFLEN) > 0)
		{
			// Convert from ASCII to float
			adc_value = atof(serial.m_buf);
			
			// Convert to various temperatures
			temp.convert_to_temperature(adc_value);
			
			// Send to database
			query = temp.form_query();
			sql.send_query(query);
		}
		else
		{
			std::cerr << "Error reading serial port!" << std::endl;
		}
				
		usleep(500000); // 500 ms delay
	}
		
	// Close port
	close(fd);
	return 0;
}
