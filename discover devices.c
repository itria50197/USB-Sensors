#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <libusb.h>

void discover_devices(){ // discover devices
    int num_detectedDevices, device_open_status, get_device_descriptor;

    libusb_context *context = NULL;
    libusb_device **list = NULL;

    libusb_device *found = NULL;
    libusb_device_handle *device_handle;

    num_detectedDevices = libusb_get_device_list(context, &list); //ssize_t num_detectedDevices = libusb_get_device_list(NULL, &list);
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
<<<<<<< HEAD
            struct libusb_device_descriptor device_descriptor;
            get_device_descriptor = libusb_get_device_descriptor(device, &device_descriptor);

            printf("Vendor:Device = %04x:%04x\n", device_descriptor.idVendor, device_descriptor.idProduct);
=======
            device = list[i];

            /*
            if (interested_device(device, &device_handle)) {
                libusb_device_handle *handle;
                device_open_status = libusb_open(device, &handle);
                printf("device_open_status = %d\n", device_open_status);

                if (device_open_status != 0){
                    switch(device_open_status)
                    {
                        case LIBUSB_ERROR_NO_MEM:
                            printf("Memory Allocation Failure");
                            break;

                        case LIBUSB_ERROR_ACCESS:
                            printf("Insufficient Permissions");
                            break;

                        case LIBUSB_ERROR_NO_DEVICE:
                            printf("Device Disconnected");
                            break;

                        default:
                            printf("Unknown Failure");
                    }
                }
            }
            */
                // etc
            //}
>>>>>>> d018b882154ff3f1e81c605619b5ef932cda376d
        }
        libusb_free_device_list(list, num_detectedDevices);
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


