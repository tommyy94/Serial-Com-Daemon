#pragma once
#include <iostream>
#include <unistd.h>

#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFLEN 9

int open_port(void);
void serial_init(int fd);
