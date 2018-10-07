#include "main.h"


int main(int argc, char *argv[])
{
	char serial_buf[BUFFLEN];
	
	Database sql;
	sql.con_init();
	int fd = open_port();
	serial_init(fd);
		
	while (1)
	{
		if (read(fd, serial_buf, BUFFLEN) > 0)
		{
			std::cout << "Data:" << serial_buf << std::endl;
			sql.send_query("INSERT INTO temperature (id, value) VALUES (33, 95)");
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
