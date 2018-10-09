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
	
public:
	constexpr static int BUFFLEN = 32;
	char buf[BUFFLEN];
	
	int open_port(void);
	void con_init(int fd);
};
