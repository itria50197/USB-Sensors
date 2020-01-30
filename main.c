#include <stdio.h>
#include <stdlib.h>
#include <libusb.h>

int main()
{
    libusb_init(NULL);
    libusb_set_option(NULL, LIBUSB_OPTION_USE_USBDK);

    libusb_exit(NULL);
}
