#include "io.h"


//
// Set up a memory regions to access GPIO
//
void MapPeripheral(struct BCM2835_Peripheral *p)
{
    // open /dev/mem
    if ((p->mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
    {
        std::cout << "Can't open /dev/mem\nerrno: " << errno << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // mmap GPIO
    p->map = mmap(
       NULL,                                // Any adddress in will do
       BLOCK_SIZE,                          // Map length
       PROT_READ | PROT_WRITE,              // Enable reading & writing to mapped memory
       MAP_SHARED,                          // Shared with other processes
       p->mem_fd,                           // File descriptor to file /dev/mem
       p->addr_p                            // GPIO peripheral address
    );

    if(p->map == MAP_FAILED)
    {
        std::cout << "mmap error " << (int)p->map << "\nerrno: " << errno << std::endl;
        std::exit(-1);
    }

    p->addr = (volatile unsigned int *)p->map;
}


void UnmapPeripheral(struct BCM2835_Peripheral *p)
{
    munmap(p->map, BLOCK_SIZE);
    close(p->mem_fd);
}
