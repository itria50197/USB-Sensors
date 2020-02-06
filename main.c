#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <libusb.h>

void main()
{
    int return_init, return_getOption, testing_i;

    return_init = libusb_init(NULL);
    testing_i = libusb_set_option(NULL, LIBUSB_OPTION_USE_USBDK);
    return_getOption = libusb_set_option(NULL, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_WARNING);

    printf("return_init = %d\n", return_init);
    printf("return_getOption = %d\n", return_getOption);
    printf("%d\n", testing_i);

    //discover_devices();

    libusb_exit(NULL);
}
