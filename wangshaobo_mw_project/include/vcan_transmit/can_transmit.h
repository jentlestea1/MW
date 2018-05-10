#ifndef CAN_TRANSMIT_H
#define CAN_TRANSMIT_H
void vcan_receive_data(unsigned char *buf,unsigned int r_size,unsigned int *size);
int vcan_send_data(unsigned char *buf,unsigned int size);
#endif

