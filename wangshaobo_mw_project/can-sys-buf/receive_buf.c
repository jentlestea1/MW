#include <stdio.h>
#include "can_sys.h"

can_dev *device;

void canIrq_handler(){
	uint8_t temp;

	temp = can_read8(device->mem_base + SJA_INT_REG); 
	if (temp & TI) {
        printf("IRQ Transmit buffer in(%d) out(%d) count(%d)\n",
					device->tx_in, device->tx_out, device->tx_count);
		if (device->tx_count > 0) {
			send_message(device->mem_base, &(device->tx_buf[device->tx_out]));
			device->tx_out++;
			if (device->tx_out == BUFFERSIZE)
				device->tx_out = 0;
			device->tx_count--;
		}
	}

	if (temp & RI) {
		printf("IRQ Receive buffer in(%d) out(%d) count(%d)\n",
					device->rx_in, device->rx_out, device->rx_count);
		
		if(device->rx_count >= BUFFERSIZE) {
   			can_write8(0x04, device->mem_base + SJA_COMMAND_REG);// Release receive buffer.
			printf("ignored. \n");
            return;   	 // No buffer, ignore this one.
		}

		device->rx_count++;
		receive_message(device->mem_base, &(device->rx_buf[device->rx_in]));

		device->rx_in++;
		if (device->rx_in >= BUFFERSIZE)
			device->rx_in = 0;

	}

	if (temp & DOI) {
		printf("IRQ Overrun int\n");
		can_write8(CDO, device->mem_base + SJA_COMMAND_REG); // Clear data overrun.
	}

}

int main(){

    device = (can_dev *)malloc(sizeof(can_dev));
	memset(device, 0, sizeof(can_dev));
	device->mem_base = (addrptr)0x80005000;

    device_open(device);

    catch_interrupt(canIrq_handler,CANSYS_IRQ_NO);  //捕获中断
    enable_irq(CANSYS_IRQ_NO);


    mdelay(18000);
	printf("get data from buffer : \n\n");
    while(device->rx_count > 0){
        can_frame* canrcv= device_read(device);
        display_can(canrcv);
    }

    // while(1){
	// 	can_frame* canrcv= device_read(device);
	// 	if(canrcv != NULL)    display_can(canrcv);
    // }

}

