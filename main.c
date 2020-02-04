#include <stdio.h>
#include <stdlib.h>
#include "libusb.h"

void main()
{
    int return_init, return_setOption;

    return_init = libusb_init(NULL);
    //return_setOption = libusb_set_option(NULL,LIBUSB_LOG_LEVEL_WARNING);

    //libusb_exit(NULL);
}
