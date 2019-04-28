#pragma once

#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <errno.h>


#define BCM2708_PERI_BASE       (0x3F000000)
#define GPIO_BASE               (BCM2708_PERI_BASE + 0x200000)

#define PAGE_SIZE               (4 * 1024)
#define BLOCK_SIZE              (4 * 1024)

// I/O access
struct BCM2835_Peripheral
{
    unsigned long addr_p;
    int mem_fd;
    void *map;
    volatile unsigned int *addr;
};


extern struct BCM2835_Peripheral gpio;


// Always use INP_GPIO(g) before using OUT_GPIO(g) or SET_GPIO_ALT(g,a)
#define INP_GPIO(g)             (*(gpio.addr+((g)/10)) &= ~(7<<(((g)%10)*3)))
#define OUT_GPIO(g)             (*(gpio.addr+((g)/10)) |=  (1<<(((g)%10)*3)))
#define SET_GPIO_ALT(g, a)      (*(gpio.addr+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3)))

#define GPIO_SET                (*(gpio.addr+7))
#define GPIO_CLR                (*(gpio.addr+10))

#define GPIO_READ(g)            (*(gpio.addr+13)&(1<<g))

#define GPIO_PULL               (*(gpio.addr+37))
#define GPIO_PULLCLK0           (*(gpio.addr+38))


void MapPeripheral(struct BCM2835_Peripheral *p);
void UnmapPeripheral(struct BCM2835_Peripheral *p);
