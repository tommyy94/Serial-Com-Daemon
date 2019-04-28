#include "serial.h"


Serial::Serial(int baud_rate)
{
	m_BaudRate = baud_rate;
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
	cfsetspeed(&tios, m_BaudRate);
	tcsetattr(m_fd, TCSAFLUSH, &tios);
	sleep(1);
}


void Serial::ClearBuffer(void)
{
    for (int i = 0; i < BUFFLEN; i++)
    {
        m_buffer[i] = 0;
    }
}


std::string Serial::ReadPort(void)
{
    int bytes_read = 0;
    
    for (int i = 0; i < BUFFLEN; i += bytes_read)
    {
        bytes_read = read(m_fd, &m_buffer[i], 1);

        if (bytes_read < 0)
        {
            std::cerr << "Error reading serial port!\nerrno: " << errno << std::endl;
        }

        if (m_buffer[i] == '\004')
        {
            break;
        }
    }
    
    std::string serial_buf(m_buffer); /* Convert C string to std::string */
    
    return serial_buf;
}


void Serial::WritePort(std::string data)
{
    if (!write(m_fd, data.c_str(), data.length()))
    {
        std::cerr << "Error writing serial port!\nerrno: " << errno << std::endl;
    }
}


void Serial::ClosePort(void)
{
    close(m_fd);
}
