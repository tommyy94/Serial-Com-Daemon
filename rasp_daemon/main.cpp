#include "main.h"
	

int main(void)
{
	Serial serial;
	Database sql("tcp://127.0.0.1:3306", "root", "", "home_automation");
	
	std::string query;
	std::string timestamp;
	
	int fd = serial.open_port();
	serial.con_init(fd);
			
	while (1)
	{
		if (read(fd, serial.buf, serial.BUFFLEN) > 0)
		{
			// TODO:
			// Convert string to integer
			// Calculate temperature values from the integer
			//query = (boost::format("INSERT INTO temperature (celsius, fahrenheit, kelvin) VALUES (%s, 5, 7)") % serial.buf).str();
			query = "INSERT INTO temperature (celsius, fahrenheit, kelvin) VALUES (1.0, 25.4, 132.55)";
			sql.send_query(query);
		}
		else
		{
			std::cerr << "Error reading serial port!" << std::endl;
		}
				
		sleep(1);    
	}
		
	close(fd);
	return 0;
}
