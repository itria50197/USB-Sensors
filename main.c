#include <stdio.h>
#include <stdlib.h>
#include "libusb.h"

void main()
{
    int return_init, return_getOption;

    return_init = libusb_init(NULL);
    return_getOption = libusb_set_option(NULL, LIBUSB_OPTION_USE_USBDK);

    discover_devices();



    libusb_exit(NULL);
}
