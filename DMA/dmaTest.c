/* dmaTest.c
 *
 */

#include "xaxidma.h"
#include "xparameters.h"


int main()
{
	u32 a[] = {1,2,3,4,5,6,7,8};

	XAxiDma dma;
	XAxiDma_Config * dma_config;

	u32 status;

	dma_config = XAxiDma_LookupConfigBaseAddr(XPAR_AXI_DMA_0_BASEADDR);
	status = XAxiDma_CfgInitialize(&dma, dma_config);
	if (status != XST_SUCCESS)
		{
			print("XAxiDma_CfgInitialize failed...\n");
		}
	print("DMA initialize success\n");

	status = XAxiDma_SimpleTransfer(&dma, (u8*) a, 8* sizeof(u32), XAXIDMA_DMA_TO_DEVICE);
	if (status != XST_SUCCESS)
	{
		print("XAxiDma_SimpleTransfer failed...\n");
	}

	print("DMA transfer success\n");
	xil_printf("a[0]=%0x\n", a[0]);

}
