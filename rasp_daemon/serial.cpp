#include "serial.h"


int open_port(void)
{
	int fd = open("/dev/ttyAMA0", O_RDWR);
	if (fd == -1)
	{
		perror("/dev/ttyAMA0");
		exit(EXIT_FAILURE);
	}
	
	return fd;
}


void serial_init(int fd)
{
	struct termios tios;
	tcgetattr(fd, &tios);
	tios.c_iflag = IGNBRK | IGNPAR;
	tios.c_oflag = 0;
	tios.c_lflag = 0;
	cfsetspeed(&tios, B9600);
	tcsetattr(fd, TCSAFLUSH, &tios);
	sleep(1);
}
