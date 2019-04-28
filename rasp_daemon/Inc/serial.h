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
	int m_BaudRate;
    int m_fd;
	
public:
	constexpr static int BUFFLEN = 64;
	char m_buffer[BUFFLEN] = "";
	
	Serial(int baud_rate);
	void OpenPort(void);
	void Init(void);
    int fd(void) const { return m_fd; }
    void ClearBuffer(void);
    std::string ReadPort(void);
    void WritePort(std::string data);
    void ClosePort(void);
};
