#include <stdio.h>
#include <stdlib.h>
#include "libusb.h"

void main(){
    int init_success = libusb_init(NULL);
    int libusb_success = libusb_set_option(NULL, LIBUSB_OPTION_USE_USBDK);

    // discover devices
    libusb_device **list;
    libusb_device *found = NULL;
    ssize_t cnt = libusb_get_device_list(NULL, &list);
    ssize_t i = 0;
    int err = 0;
    if (cnt < 0)
        error();

    for (i = 0; i < cnt; i++) {
        libusb_device *device = list[i];
        if (is_interesting(device)) {
            found = device;
            break;
        }
    }

    if (found) {
        libusb_device_handle *handle;

        err = libusb_open(found, &handle);
        if (err)
            error();
        // etc
    }

    libusb_free_device_list(list, 1);
}
