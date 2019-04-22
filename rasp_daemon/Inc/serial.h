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
    int m_fd;
	
public:
	constexpr static int BUFFLEN = 32;
	char m_buf[BUFFLEN] = "";
	
	Serial(int baud_rate);
	void OpenPort(void);
	void Init(void);
    int fd(void) const { return m_fd; }
};
