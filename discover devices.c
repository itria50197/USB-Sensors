#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <libusb.h>

void discover_devices(){ // discover devices
    int device_open_status, get_device_descriptor;
    libusb_context *context = NULL;
    libusb_device **list = NULL;
    libusb_device *found = NULL;
    libusb_device_handle *device_handle;

    ssize_t num_detectedDevices = libusb_get_device_list(context, &list);
    printf("num_detectedDevices = %d\n", num_detectedDevices);

    device_open_status = 0;

    if (num_detectedDevices < 0)
    {
        error();
    }
    else
    {
        for (ssize_t i = 0; i < num_detectedDevices; i++) {
            libusb_device *device = list[i];
            printf("i = %d\n", i);

            struct libusb_device_descriptor device_descriptor;
            get_device_descriptor = libusb_get_device_descriptor(device, &device_descriptor);

            printf("Vendor:Device = %04x:%04x\n", device_descriptor.idVendor, device_descriptor.idProduct);
        }
    }
    libusb_free_device_list(list, num_detectedDevices);
}

void error(){printf("Detection Encounter Issues");}

int interested_device(libusb_device *device, libusb_device_handle **device_handle){
    int open_result = libusb_open(device, &device_handle);

    if (open_result = 0)
        return 1;
    else
        return 0;
}

/* Wait to be added

int libusb_open	(	libusb_device * 	dev,libusb_device_handle ** 	dev_handle )

libusb_device* libusb_get_device	(	libusb_device_handle * 	dev_handle	)

*/


