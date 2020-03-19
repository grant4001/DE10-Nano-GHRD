#include "hps_0.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <stdint.h>
#include <sys/mman.h>

#define HW_REGS_BASE (0xfc000000)
#define HW_REGS_SPAN (0x04000000)
#define ALT_LWFPGASLVS_OFST (0xff200000)
#define HW_REGS_MASK (HW_REGS_SPAN - 1)
#define LED_PIO_BASE (0x3000)
#define PIO_LED_DATA_WIDTH (7)

int main(int argc, char **argv) 
{
    int fd;
    uint32_t *h2p_lw_led_addr;
    void *virtual_base;

    if ( (fd = open("/dev/mem", (O_RDWR | O_SYNC) ) ) == -1) 
    {
        printf("ERROR: could not open \"/dev/mem\"...\n");
        return(1);
    }

    virtual_base = mmap(NULL, HW_REGS_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, HW_REGS_BASE);

    if (virtual_base == MAP_FAILED)
    {
        printf("ERROR: mmap() failed...\n");
        close( fd );
        return(1);
    }

    h2p_lw_led_addr = (virtual_base + ( (unsigned long)(ALT_LWFPGASLVS_OFST + LED_PIO_BASE) & (unsigned long)(HW_REGS_MASK)));
    
    int loop_count = 0;
    uint32_t led_mask = 0x01;
    int led_direction = 0;

    while (1) 
    {
        *(uint32_t *)h2p_lw_led_addr = led_mask;
        usleep(100*1000);
        if (led_direction == 0)
        {
            led_mask <<= 1;
            if (led_mask == (0x01 << (PIO_LED_DATA_WIDTH - 1)))
            {
                led_direction = 1;
            }
        }
        else
        {
            led_mask >>= 1;
            if (led_mask == 0x01)
            {
                led_direction = 0;
                loop_count++;
            }
        }
        
    }
}