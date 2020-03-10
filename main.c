#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <libusb.h>

void main(int argc, char *argv[])
{
    int return_init, return_setOption, return_getOption;
    libusb_context *context = NULL;

    return_init = libusb_init(&context);
    return_setOption = libusb_set_option(NULL, LIBUSB_OPTION_USE_USBDK);
    return_getOption = libusb_set_option(NULL, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL_WARNING);

    discover_devices();

    /* Release Memory */
    //libusb_free_device_list(&list, unref_devices);
    libusb_close(context);
    libusb_exit(context);
}

void discover_devices() // discover devices
{
    int device_open_status, get_device_descriptor;
    libusb_context *context = NULL;
    libusb_device **list = NULL;
    libusb_device *found = NULL;
    libusb_device_handle *device_handle = NULL;
    libusb_device *device;

    ssize_t num_detectedDevices = libusb_get_device_list(context, &list);
    printf("num_detectedDevices = %d\n\n", num_detectedDevices);

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

            libusb_get_device_descriptor(device, &device_descriptor);
            printf("Vendor ID = %04x : Product ID = %04x\n", device_descriptor.idVendor, device_descriptor.idProduct);
            interested_device(device, &device_handle, context);
            printf("\n");
        }
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

    //device = libusb_get_device(device_handle);
    int open_result = libusb_open(device, &device_handle);

    switch(open_result)
    {
    case 0:
        printf("Connection Status: Device open succeed\n");
        int portNum = 0;
        portNum = libusb_get_port_number(device);
        printf("Port Number: %d\n", portNum);

        int busNum = 0;
        busNum = libusb_get_bus_number(device);
        printf("Bus Number: %d\n", busNum);

        int deviceSpeed = 0;
        deviceSpeed = libusb_get_device_speed(device);
        printf("Device Speed: ");

        switch(deviceSpeed)
        {
        case LIBUSB_SPEED_UNKNOWN:
            printf("Speed Unknown\n");
            break;

        case LIBUSB_SPEED_LOW:
            printf("Speed Low\n");
            break;

        case LIBUSB_SPEED_FULL:
            printf("Speed Full\n");
            break;

        case LIBUSB_SPEED_HIGH:
            printf("Speed High\n");
            break;

        case LIBUSB_SPEED_SUPER:
            printf("Speed Super\n");
            break;

        case LIBUSB_SPEED_SUPER_PLUS:
            printf("Speed Super Plus\n");
            break;

        default:
            break;
        }

        int interface_claim = libusb_claim_interface(device_handle, 0);
        switch(interface_claim)
        {
        case 0:
            printf("Interface Claim Succeeds\n");
            //printf("Data to transfer: %s\n", data);

            int actual;
            struct libusb_endpoint_descriptor epDescriptor;
            printf("Endpoint Address: %d\n",epDescriptor.bEndpointAddress);

            struct libusb_interface_descriptor ifDescriptor;
            printf("Interface Number: %d\n", ifDescriptor.bInterfaceNumber);
            printf("Endpoint Number (Used by This Interface): %d\n", ifDescriptor.bNumEndpoints);

            /*////////////////////////////////// To be Adjusted /////////////////////////////////////////*/
            /*////////////////////////////////// To be Adjusted /////////////////////////////////////////*/
            /*////////////////////////////////// To be Adjusted /////////////////////////////////////////*/
            struct libusb_transfer *transfer = libusb_alloc_transfer(0);
            int config_set_result = libusb_set_configuration(device_handle, LIBUSB_TRANSFER_TYPE_ISOCHRONOUS);
            libusb_set_iso_packet_lengths(transfer, libusb_get_max_iso_packet_size(device, epDescriptor.bEndpointAddress));

            uint16_t buffer[128] = {0};
            memset(buffer, 0, sizeof(buffer));
            libusb_fill_iso_transfer(transfer,
                                     device_handle,
                                     epDescriptor.bEndpointAddress,
                                     buffer,
                                     128,
                                     (*transfer).num_iso_packets,
                                     (*transfer).callback,
                                     (*transfer).user_data,
                                     3000);

            int submit_transfer = libusb_submit_transfer(transfer);

            printf("Configure Value Returned = %d\n", config_set_result);
            printf("Callback: \n", (*transfer).callback);
            printf("Data = %s\n", (*transfer).user_data);
            printf("Data Buffer = %s\n", (*transfer).buffer);
            printf("Submit Transfer = %d\n", submit_transfer);

            /*////////////////////////////////// To be Adjusted /////////////////////////////////////////*/
            /*////////////////////////////////// To be Adjusted /////////////////////////////////////////*/
            /*////////////////////////////////// To be Adjusted /////////////////////////////////////////*/

            int active_or_not = libusb_kernel_driver_active(device_handle, 0);
            switch(active_or_not)
            {
            case 0:
                printf("no active driver\n");
                break;

            case 1:
                printf("driver active\n");
                break;

            case LIBUSB_ERROR_NO_DEVICE:
                printf("no device\n");
                break;

            case LIBUSB_ERROR_NOT_SUPPORTED:
                printf("not supported\n");
                break;

            default:
                printf("other error\n");
            }

            break;

        case LIBUSB_ERROR_NOT_FOUND:
            printf("Interface Claim not found\n");
            break;

        case LIBUSB_ERROR_BUSY:
            printf("Interface Claim busy\n");
            break;

        case LIBUSB_ERROR_NO_DEVICE:
            printf("Interface Claim no device\n");
            break;

        default:
            printf("Interface Claim other errors\n");
        }

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

void error_info(int error_in_number)
{
    switch(error_in_number)
    {
    case LIBUSB_SUCCESS:
        printf("Success\n");
        break;

    case LIBUSB_ERROR_IO:
        printf("Error IO\n");
        break;

    case LIBUSB_ERROR_INVALID_PARAM:
        printf("Invalid Parameters\n");
        break;

    case LIBUSB_ERROR_ACCESS:
        printf("Error Access\n");
        break;

    case LIBUSB_ERROR_NO_DEVICE:
        printf("No devices\n");
        break;

    case LIBUSB_ERROR_NOT_FOUND:
        printf("No found\n");
        break;

    case LIBUSB_ERROR_BUSY:
        printf("Busy\n");
        break;

    case LIBUSB_ERROR_TIMEOUT:
        printf("Timeout\n");
        break;

    case LIBUSB_ERROR_OVERFLOW:
        printf("Overflow\n");
        break;

    case LIBUSB_ERROR_PIPE:
        printf("Pipe Error\n");
        break;

    case LIBUSB_ERROR_INTERRUPTED:
        printf("Interrupted\n");
        break;

    case LIBUSB_ERROR_NO_MEM:
        printf("No member\n");
        break;

    case LIBUSB_ERROR_NOT_SUPPORTED:
        printf("Not supported\n");
        break;

    case LIBUSB_ERROR_OTHER:
        printf("Other errors\n");
        break;

    default:
        break;
    }
}
