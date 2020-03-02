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

void discover_devices() // discover devices
{
    int device_open_status, get_device_descriptor;
    libusb_context *context = NULL;
    libusb_device **list = NULL;
    libusb_device *found = NULL;
    libusb_device_handle *device_handle;
    libusb_device *device;

    ssize_t num_detectedDevices = libusb_get_device_list(context, &list);
    printf("num_detectedDevices = %d\n", num_detectedDevices);

    device_open_status = 0;

    if (num_detectedDevices < 0)
    {
        error();
    }

    else
    {
        struct libusb_device_descriptor device_descriptor;
        for(ssize_t i = 0; i < num_detectedDevices; i++)
        {
            device = list[i];

            printf("i = %d\n", i);
            get_device_descriptor = libusb_get_device_descriptor(device, &device_descriptor); // IDs: 064b 784c
            printf("Vendor:Device = %04x:%04x\n", device_descriptor.idVendor, device_descriptor.idProduct);
        }

        interested_device(device, &device_handle, context);
        libusb_free_device_list(list, num_detectedDevices);
    }
}

void error(){printf("Issues Occur");}

/*
With the above information in mind, the process of opening a device can be viewed as follows:
1. Discover devices using libusb_get_device_list().
2. Choose the device that you want to operate, and call libusb_open().
3. Unref all devices in the discovered device list.
4. Free the discovered device list.
*/
void interested_device(libusb_device *device, libusb_device_handle **device_handle, libusb_context *context){

    int open_result = libusb_open(device, &device_handle);
    printf("open_result = %d\n", open_result);

    switch(open_result)
    {
    case 0:
        printf("Connection Status: Device open succeed\n");
        break;

    case LIBUSB_ERROR_IO:
        printf("Connection Status: IO Error\n");
        break;

    case LIBUSB_ERROR_INVALID_PARAM:
        printf("Connection Status: invalid parameters\n");
        break;

    case LIBUSB_ERROR_ACCESS:
        printf("Connection Status: Error Access\n");
        break;

    case LIBUSB_ERROR_NO_DEVICE:
        printf("Connection Status: No devices detected\n");
        break;

    case LIBUSB_ERROR_NOT_FOUND:
        printf("Connection Status: Devices not found\n");
        break;

    case LIBUSB_ERROR_BUSY:
        printf("Connection Status: Devices busy\n");
        break;

    case LIBUSB_ERROR_TIMEOUT:
        printf("Connection Status: Connection time-out\n");
        break;

    case LIBUSB_ERROR_OVERFLOW:
        printf("Connection Status: Overflow\n");
        break;

    case LIBUSB_ERROR_PIPE:
        printf("Connection Status: Pipe Error\n");
        break;

    case LIBUSB_ERROR_INTERRUPTED:
        printf("Connection Status: Interrupted\n");
        break;

    case LIBUSB_ERROR_NO_MEM:
        printf("Connection Status: No memory\n");
        break;

    case LIBUSB_ERROR_NOT_SUPPORTED:
        printf("Connection Status: Devices not supported\n");
        break;

    default:
        printf("Connection Status: other failure\n");
    }
}


/*
libusb_context *ctx = NULL; //a libusb session
 libusb_device_handle *dev_handle; //a device handle
 libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
    int r;
    ssize_t number_of_connected_devices; //holding number of devices in list
    r=libusb_init(&ctx);
    if(r < 0)
        QMessageBox::information(this,"Err","init err");
    else{
        if(dev_handle != NULL) {
        libusb_release_interface(dev_handle,0);
        libusb_close(dev_handle);
        }
        dev_handle= NULL;
        libusb_set_debug(ctx, 3); //set verbosity level to 3, as suggested in the documentation
        number_of_connected_devices = libusb_get_device_list(ctx, &devs); //get the list of devices
        if (number_of_connected_devices<0)
            QMessageBox::information(this,"DvcErr","Get Device Error");
        else{
        `QMessageBox::information(this,"number_of_connected_devices",QString::number(number_of_connected_devices));
        ssize_t k; //for iterating through the list
        int My_found_device_num=0;
        int which_device;
        for(k=0;k<number_of_connected_devices;k++){
            libusb_device_descriptor desc;
            int a = libusb_get_device_descriptor(devs[k], &desc);
            if (a < 0)
                QMessageBox::information(this,"err","failed to get device descriptor");
            else{
                QMessageBox::information(this,"inf","VendorID: "+QString::number(desc.idVendor));
                QMessageBox::information(this,"inf","ProductID: "+QString::number(desc.idProduct));
            }
            if ( (desc.idVendor == VENDOR_ID) && (desc.idProduct == PRODUCT_ID)){
                My_found_device_num++;
                which_device=k;
            }
        }
        if (My_found_device_num>1)
            QMessageBox::information(this,"err","more than one device connected!");
        else{
        //dev_handle = libusb_open_device_with_vid_pid(ctx, VENDOR_ID, PRODUCT_ID); //these are vendorID and productID I found for my usb device
        int b=libusb_open(devs[which_device],&dev_handle);
            if (libusb_open(devs[which_device],&dev_handle) < 0)
            QMessageBox::information(this,"err","cannot open device");
        else{
//REST OF MY CODE
*/
