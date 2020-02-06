#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <libusb.h>

void error(){printf("Detection Encounter Issues.");}
int is_interested(libusb_device *device){
}

void discover_devices(){
    // discover devices
    libusb_device **list;
    libusb_device *found = NULL;
    ssize_t num_detectedDevices = libusb_get_device_list(NULL, &list);
    ssize_t i = 0;
    int err = 0;

    printf("%d\n", num_detectedDevices);
    printf("%d\n", err);

    if (err == 0)
    {
        error();
    }
    else
    {
        for (i = 0; i < num_detectedDevices; i++) {
            libusb_device *device = list[i];
            if (is_interested(device)) {
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



/* Wait to be added

int libusb_open	(	libusb_device * 	dev,libusb_device_handle ** 	dev_handle )

libusb_device* libusb_get_device	(	libusb_device_handle * 	dev_handle	)

*/


