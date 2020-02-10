#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <libusb.h>

void discover_devices(){ // discover devices
    int num_detectedDevices, i, err;
    libusb_device **list, *device;
    libusb_device *found = NULL;
    libusb_device_handle *device_handle;

    num_detectedDevices = (int)libusb_get_device_list(NULL, &list); //ssize_t num_detectedDevices = libusb_get_device_list(NULL, &list);
    printf("num_detectedDevices = %d\n", num_detectedDevices);

    //i = 0; //ssize_t i = 0;
    err = 0;

    if (num_detectedDevices < 0)
    {
        error();
    }
    else
    {
        for (i = num_detectedDevices; i > 0; i--) {
            device = list[i];
            found = device;
            /*
            if (interested_device(device, device_handle)) {
                found[i] = device;
                break;
            }
            */

            //if (found) {
            libusb_device_handle *handle;

            err = libusb_open(found, &handle);
            if (err)
                error();
                // etc
            //}
        }
    }



    //libusb_close();
    libusb_free_device_list(list, 1);
}

void print_messages_discover(ssize_t num_detectedDevices, int err){
    printf("From discover_devices()\n");
    printf("num_detectedDevices = %d\n", num_detectedDevices);
    printf("err = %d\n", err);
    printf("End of discover_devices()\n");
}

void error(){printf("Detection Encounter Issues");}

int interested_device(libusb_device *device, libusb_device_handle **device_handle){
    libusb_open(device, &device_handle);
}

/* Wait to be added

int libusb_open	(	libusb_device * 	dev,libusb_device_handle ** 	dev_handle )

libusb_device* libusb_get_device	(	libusb_device_handle * 	dev_handle	)

*/


