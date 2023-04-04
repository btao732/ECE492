#include <stdlib.h>
#include <stdio.h>
#include "xparameters.h"
#include "xuartps.h"
#include "xgpio.h"
#include "xil_printf.h"
#include "xil_types.h"
#include "sleep.h"

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define UART_DEVICE_ID                  XPAR_XUARTPS_0_DEVICE_ID
#define GPIO_DEVICE_ID 					XPAR_GPIO_0_DEVICE_ID
#define BUFFER_SIZE						10
#define UART_DELAY_MICROSECONDS			10000
#define CLOCK_DELAY_MICROSECONDS 		200000

int UartPsSetUp(u16 DeviceId);
int GpioSetup(u16 DeviceId);

XUartPs uart;		/* The instance of the UART Driver */
XGpio gpio;			/* The instance of the GPIO Driver */

// Convert u8 buffer to u32 data
u32 bufferToUnsigned32(u8* buffer, u32 index) {
	return (buffer[index] << 24) + (buffer[index + 1] << 16) + (buffer[index + 2] << 8) + buffer[index + 3];
}

// Convert u8 buffer to u16 data
u16 bufferToUnsigned16(u8* buffer, u32 index) {
	return (buffer[index] << 8) + buffer[index + 1];
}

// If we go back to PISO shift registers...
u16* loadChannelDataPISO(u8* buffer, u32 numberOfChannels, u32 numberOfSamples, u32 size) {
	u16* data = (u16 *) malloc(size);
	for (int i = 0; i < size / 2; i++) {
		data[i] = bufferToUnsigned16(buffer, i * 2);
	}

	return data;
}

// Max of 30 channels
void sendChannelData(u8 channelData[], u32 numberOfChannels, u32 samplesPerChannel) {
	for (int sample = 0; sample < samplesPerChannel; sample++) {
		for (int byte = 1; byte >= 0; byte--) {
			for (int bit = 0; bit < 8; bit++) {
				u32 outputData = 0; // Datatype determines max number of channels
				u8 dataMask = 1 << bit;
				for (int channel = 0; channel < numberOfChannels; channel++) {
					u8 rawData = channelData[channel * samplesPerChannel * 2 + sample * 2 + byte];
					outputData |= ((rawData & dataMask) >> bit) << (channel + 2);
				}
				XGpio_DiscreteWrite(&gpio, 1, outputData);
				usleep(CLOCK_DELAY_MICROSECONDS);
				outputData |= 1 | (((!byte) + bit) >> 2); // Clock and Latch signals
				XGpio_DiscreteWrite(&gpio, 1, outputData);
				usleep(CLOCK_DELAY_MICROSECONDS);
			}
		}
	}
}

int main(void)
{
	u8 buffer[BUFFER_SIZE] = { 0 };
	u8 metaData[8] = { 0 };
	u8* data = 0;
	int status;

	status = UartPsSetUp(UART_DEVICE_ID);
	if (status != XST_SUCCESS) {
		return status;
	}

	status = XGpio_Initialize(&gpio, GPIO_DEVICE_ID);
	if (status != XST_SUCCESS) {
		return status;
	}

	XGpio_SetDataDirection(&gpio, 1, 0xF);

	xil_printf("SPARC Initialized\r\n");

	while (1) {
		// Get Number of channel and samples per channel over UART
		u32 byteSum = 0;
		while (byteSum < 8) {
			u32 receivedBytes = XUartPs_Recv(&uart, buffer, 8 - byteSum);
			for (int i = 0; i < receivedBytes; i++) {
				metaData[byteSum + i] = buffer[i];
			}
			byteSum += receivedBytes;
			usleep(UART_DELAY_MICROSECONDS);
		}

		u32 numberOfChannels = bufferToUnsigned32(metaData, 0);
		u32 numberOfSamples = bufferToUnsigned32(metaData, 4);

		xil_printf("Channels: %u\r\n", numberOfChannels);
		xil_printf("Samples per channel: %u\r\n", numberOfSamples);

		u32 totalDataBytes = numberOfChannels * numberOfSamples * 2;

		// So we don't blow up the fpga by asking for too much memory
		if (totalDataBytes < 10000) {
			data = (u8*) malloc(totalDataBytes); // 2 Bytes per sample
			byteSum = 0;
			while (byteSum < totalDataBytes) {
				u32 receivedBytes = XUartPs_Recv(&uart, buffer, totalDataBytes - byteSum);
				for (int i = 0; i < receivedBytes; i++) {
					data[byteSum + i] = buffer[i];
				}
				byteSum += receivedBytes;
				usleep(UART_DELAY_MICROSECONDS);
			}

			// Print channel data
			for (int i = 0; i < totalDataBytes; i++) {
				xil_printf("%x ", data[i]);
			}
			xil_printf("\r\n");

			// Output to PMOD
			sendChannelData(data, numberOfChannels, numberOfSamples);
			free(data);

		} else {
			xil_printf("Error - Data Overflow\r\n");
		}
	}

	return 0;
}

// Configure and start UART protocol
int UartPsSetUp(u16 DeviceId)
{
	int Status;
	XUartPs_Config *Config;

	/*
	 * Initialize the UART driver so that it's ready to use
	 * Look up the configuration in the config table and then initialize it.
	 */
	Config = XUartPs_LookupConfig(DeviceId);
	if (NULL == Config) {
		return XST_FAILURE;
	}

	Status = XUartPs_CfgInitialize(&uart, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	XUartPs_SetBaudRate(&uart, 115200);

	return Status;
}
