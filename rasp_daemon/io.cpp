#include "io.h"


//
// Set up a memory regions to access GPIO
//
void IO_Init()
{
    int  mem_fd;
    void *gpio_map;
    
    /* open /dev/mem */
    if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
    {
        std::cout << "Can't open /dev/mem\nerrno: " << errno << std::endl;
        std::exit(EXIT_FAILURE);
    }

    /* mmap GPIO */
    gpio_map = mmap(
       NULL,                                //Any adddress in will do
       BLOCK_SIZE,                          //Map length
       PROT_READ | PROT_WRITE,              //Enable reading & writing to mapped memory
       MAP_SHARED,                          //Shared with other processes
       mem_fd,                              //File to map
       GPIO_BASE                            //Offset to GPIO peripheral
    );

    close(mem_fd);                          //Close mem_fd after mmap

    if(gpio_map == MAP_FAILED)
    {
        std::cout << "mmap error " << (int)gpio_map << "\nerrno: " << errno << std::endl;
        std::exit(-1);
    }

    // Always use volatile pointer!
    gpio = (volatile unsigned *)gpio_map;

} // setup_io
