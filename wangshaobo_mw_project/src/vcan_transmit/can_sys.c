#include "can_sys.h"

void mdelay(int d){	   //延时函数
     int i,j;
     for(i =0;i <d;i++)
		for(j=0;j<1*1000*100;j++)
			;
}

void display_can(struct can_frame *can){
	uint8_t i;
	printf("%02x",can->can_id);
	printf("  [%02x]:",can->can_dlc);
	for(i = 0;i < can->can_dlc; i++){
		printf(" %02x",can->data[i]);
	}
	printf("\n");
}

uint8_t can_read8(addrptr ptr){
	return *(volatile addrptr)ptr;
}

void can_write8(uint8_t val, addrptr ptr){
	*(volatile addrptr)ptr = val;
}

void send_message(addrptr base, can_frame *can){
	uint8_t temp, index, i;

	index = 10;
	temp = (can->can_id >> 3) & 0xff;
	can_write8(temp, base + index);
	index++;

	temp = (can->can_id << 5) & 0xe0;
	if (can->can_id & (1 << 30)) // RTR
		temp |= (1 << 4);
	temp |= can->can_dlc & 0x0f;
	can_write8(temp, base + index);
	index++;

	for(i = 0; i < can->can_dlc; i++, index++)
		can_write8(can->data[i], base + index);

   	can_write8(0x01, base + SJA_COMMAND_REG);   // Send transmission request.
}

int receive_message(addrptr base, can_frame *can){
	uint8_t temp, index, i;
	index = TX_FRAME_INFO_REG;

	memset(can, 0, sizeof(struct can_frame));
	index = 20;
	temp = can_read8(base + index++);
	can->can_id = (temp << 3) & (0xff << 3);
	temp = can_read8(base + index++);
	can->can_id |= (temp >> 5) & 0x07;
	if(temp & 0x10)
		can->can_id |= (1 << 30);

	can->can_dlc = temp & 0x0f;
	for(i = 0; i < can->can_dlc; i++) {
		can->data[i] = can_read8(base + index++);
	}
   	can_write8(0x04, base + SJA_COMMAND_REG);// Release receive buffer.
	if(can->can_id != 0 | can->can_dlc > 0){		//判断是否收到数据帧
		//display_can(can);
		return 1;
	}
	return 0;
}

int device_open(can_dev *device){
	
	uint8_t			temp, count;
	// Try to go to reset mode.
	temp = can_read8(device->mem_base + SJA_MODE_REG); //
	//printf("count:0,  SJA_MODE_REG temp:0x%x\n",temp);
	count = 0;
	while (((temp & RESET_BIT) != RESET_BIT) && (count < 3)) {
		temp |= RESET_BIT;
		//printf("reset temp:0x%x\n",temp);
		can_write8(temp, device->mem_base + SJA_MODE_REG);
		mdelay(10);
		count++;
		temp = can_read8(device->mem_base + SJA_MODE_REG);
		//printf("count:%d, SJA_MODE_REG temp:0x%x\n", count, temp);
	}
	if ((temp & RESET_BIT) != RESET_BIT)
		return -1;

	/* Do some initialising thing */

	// BasicCAN Mode
	temp = can_read8(device->mem_base + SJA_CLOCK_REG);
	//printf("SJA_CLOCK_REG temp: 0x%x\n", temp);
	can_write8(temp & (~PELI), device->mem_base + SJA_CLOCK_REG);

	// Filter set
	can_write8(0xff, device->mem_base + SJA_BASIC_AMR_REG); // All data

	// Enable transmit and receive interrupt
	temp = can_read8(device->mem_base + SJA_CONTROL_REG);
	//printf("SJA_CONTROL_REG temp:0x%x\n",temp);
	can_write8(temp | (3 << 1), device->mem_base + SJA_CONTROL_REG);

	// Try to go to operation mode.
	temp = can_read8(device->mem_base + SJA_MODE_REG); //
	//printf("count:0,  SJA_MODE_REG temp:0x%x\n",temp);
	count = 0;
	while (((temp & RESET_BIT) == RESET_BIT) && (count < 3)) {
		temp &= ~RESET_BIT;
		can_write8(temp, device->mem_base + SJA_MODE_REG);
		mdelay(10);
		count++;
		temp = can_read8(device->mem_base + SJA_MODE_REG);
		//printf("count:%d, SJA_MODE_REG temp:0x%x\n", count, temp);
	}

	if ((temp & RESET_BIT) == RESET_BIT)
		return -1;

	memset(device->tx_buf, 0, BUFFERSIZE * sizeof(can_frame));
	device->tx_count = 0;
	device->tx_in = 0;
	device->tx_out = 0;
	memset(device->rx_buf, 0, BUFFERSIZE * sizeof(can_frame));
	device->rx_count = 0;
	device->rx_in = 0;
	device->rx_out = 0;
	printf("vcan设备已连接\n");
	return 0;
}

/* 返回buffer还可以容纳数据的个数 */
int device_write(can_dev *device, can_frame frame){
	
	unsigned char temp;
	
	//if (device->tx_count == BUFFERSIZE)
	if ((device->tx_in+1)%BUFFERSIZE ==device->tx_out)
		return -1;  // There is no tx buffer to store current message.

	device->tx_buf[device->tx_in] = frame;

	temp = can_read8(device->mem_base + SJA_STATUS_REG); //
	//printf("status register...... 0x%x\n", temp);
	if ((temp & TBS) != TBS) {  // Put the message to buffer.
		//device->tx_count++;
		device->tx_in++;
		if (device->tx_in == BUFFERSIZE)
			device->tx_in = 0;
		//return BUFFERSIZE - device->tx_count;
		return BUFFERSIZE - ((device->tx_in-device->tx_out+BUFFERSIZE)%BUFFERSIZE);
	}
	send_message(device->mem_base, &(device->tx_buf[device->tx_in]));

	return BUFFERSIZE - ((device->tx_in-device->tx_out+BUFFERSIZE)%BUFFERSIZE);
	//return BUFFERSIZE - device->tx_count;
}

can_frame* device_read(can_dev *device){
	
	//if (device->rx_count == 0)
	if (device->rx_in == device->rx_out )
		return NULL;	  // There is no CAN message now.

	can_frame* frame = &(device->rx_buf[device->rx_out]);
	
	device->rx_out++;
	if (device->rx_out == BUFFERSIZE)
		device->rx_out = 0;
    
    //这里的rx_count可能被同时访问
	//device->rx_count--;
		
	return frame;
}

