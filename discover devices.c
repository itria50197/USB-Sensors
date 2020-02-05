#include <stdio.h>
#include <stdlib.h>
#include "libusb.h"

void error(){}
int is_interesting(libusb_device *device){}

void discover_devices(){
    // discover devices
    libusb_device **list;
    libusb_device *found = NULL;
    ssize_t num_detectedDevices = libusb_get_device_list(NULL, &list);
    ssize_t i = 0;
    int err = 0;
    if (num_detectedDevices < 0)
    {
        error();
    }
    else
    {
        for (i = 0; i < num_detectedDevices; i++) {
            libusb_device *device = list[i];
            if (is_interesting(device)) {
                found = device;
                break;
            }
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


