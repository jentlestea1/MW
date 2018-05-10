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

    can_frame cansnd;
	cansnd.can_id = 0x111;
	cansnd.can_dlc = 3;
	cansnd.data[0] = 'd';
	cansnd.data[1] = 'o';
	cansnd.data[2] = 't';

    int i;
    for(i = 0;i < 6;i++){
        device_write(device, cansnd);
        cansnd.can_id += 0x111;
        mdelay(2500);
    }

    // for(i = 0;i < 40;i++){
    //     device_write(device, cansnd);
    //     cansnd.can_id += 0x111;
    //     //mdelay(2500);
    // }

	// while(1){
	// 	device_write(device, cansnd);
	// 	while(1){
	// 		can_frame* canrcv = device_read(device);
    //         mdelay(2000);            
	// 		if(canrcv != NULL) {
    //             display_can(canrcv);
    //             break;                
    //         }
	// 	}
	// }
}

