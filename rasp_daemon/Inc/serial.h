#pragma once
#include <iostream>
#include <unistd.h>

#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>


class Serial
{
private:
	const char *dev_tty = "/dev/ttyAMA0";
	int m_baud_rate;
	
public:
	constexpr static int BUFFLEN = 32;
	char m_buf[BUFFLEN] = "";
	
	Serial(int baud_rate);
	int open_port(void);
	void con_init(int fd);
};
