#include "serial.h"


Serial::Serial(int baud_rate)
{
	m_baud_rate = baud_rate;
}


void Serial::OpenPort(void)
{
	int fd = open(dev_tty, O_RDWR);
	if (fd == -1)
	{
		perror(dev_tty);
    	std::exit(EXIT_FAILURE);
	}
	
	m_fd = fd;
}


void Serial::Init()
{
	struct termios tios;
	tcgetattr(m_fd, &tios);
	tios.c_iflag = IGNBRK | IGNPAR;
	tios.c_oflag = 0;
	tios.c_lflag = 0;
	cfsetspeed(&tios, m_baud_rate);
	tcsetattr(m_fd, TCSAFLUSH, &tios);
	sleep(1);
}
