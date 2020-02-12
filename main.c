#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <libusb.h>

void main()
{
    int return_init, return_setOption, return_getOption;
    libusb_context *context = NULL;

    return_init = libusb_init(&context);
    return_setOption = libusb_set_option(NULL, LIBUSB_OPTION_USE_USBDK);
    return_getOption = libusb_set_option(NULL, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_WARNING);

    discover_devices();

    libusb_exit(context);
}
