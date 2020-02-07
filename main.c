#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <libusb.h>

void main()
{
    int return_init, return_setOption, return_getOption;

    return_init = libusb_init(NULL);
    return_setOption = libusb_set_option(NULL, LIBUSB_OPTION_USE_USBDK);
    return_getOption = libusb_set_option(NULL, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_WARNING);

    print_messages();
    discover_devices();

    libusb_exit(NULL);
}

void print_messages(int return_init, int return_setOption, int return_getOption){
    printf("From main()\n");
    printf("return_init = %d\n", return_init);
    printf("return_setOption = %d\n", return_setOption);
    printf("return_getOption = %d\n", return_getOption);
    printf("End of main()\n");
}
