#include "main.h"
	

int main(void)
{
	Serial serial;
	Database sql("tcp : //127.0.0.1:3306", "root", "", "home_automation");
	
	std::string query;
	std::string timestamp;
	
	int fd = serial.open_port();
	serial.con_init(fd);
			
	while (1)
	{
		if (read(fd, serial.buf, serial.BUFFLEN) > 0)
		{
			query = (boost::format("INSERT INTO temperature (id, value) VALUES (33, %s)") % serial.buf).str();
			timestamp = get_timestamp();
			// Send timestamp to DB
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
