#ifndef CAN_SYS_H__
#define CAN_SYS_H__
#include "compile_type.h"
#ifdef __VCAN_TRANSMIT
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
 * Controller Area Network Identifier structure
 *
 * bit 0-28	: CAN identifier (11/29 bit)
 * bit 29	: error frame flag (0 = data frame, 1 = error frame)
 * bit 30	: remote transmission request flag (1 = rtr frame)
 * bit 31	: frame format flag (0 = standard 11 bit, 1 = extended 29 bit)
 */
typedef uint32_t canid_t;
typedef uint8_t* addrptr;

typedef struct can_frame {
	canid_t can_id;  			/* 32 bit CAN_ID + EFF/RTR/ERR flags */
	uint8_t    can_dlc; 		/* data length code: 0 .. 8 */
	uint8_t    data[8] __attribute__((aligned(8)));
}can_frame;

#define BUFFERSIZE		6
#define CANSYS_IRQ_NO 			13

typedef struct can_dev
{
	can_frame			tx_buf[BUFFERSIZE];
	uint8_t				tx_count;
	uint8_t				tx_in;
	uint8_t				tx_out;

	can_frame			rx_buf[BUFFERSIZE];
	uint8_t				rx_count;
	uint8_t				rx_in;
	uint8_t				rx_out;

	addrptr mem_base;
}can_dev;


// Mode register, address 0
#define SJA_MODE_REG		0
#define RESET_BIT			(1 << 0)

// TX frame information, address 16, p40.
#define TX_FRAME_INFO_REG	16
// Standard Frame Format, SFF, bit7
#define SFF					(0 << 7)
// Extended Frame Format, EFF
#define EFF					(1 << 7)
// Remote Transmission Request, RTR
#define RTR					(1 << 6)
// Data Length Code bits, DLC
#define DLC(x)				(x)


// Status register, address 2
#define SJA_STATUS_REG		2
// Tranmit buffer status, 1-released 0-locked
#define TBS					(1 << 2)

// Command register, address 1, p13.
#define SJA_COMMAND_REG		1
// Clear Data Overrun
#define CDO					(1 << 3)

// Clock Divider register, address 31, Dp55
#define SJA_CLOCK_REG		31
#define PELI				(1 << 7)

#define SJA_INT_REG			3
#define SJA_INT_EN_REG		4
#define RI					(1 << 0)
#define RIE					(1 << 0)
#define TI					(1 << 1)
#define TIE					(1 << 1)
#define DOI					(1 << 3)
#define DOIE				(1 << 3)

// Basic mode, Control register
#define SJA_CONTROL_REG		0
// Basic mode, Acceptance mask
#define SJA_BASIC_AMR_REG	5

uint8_t can_read8(addrptr ptr);
void can_write8(uint8_t val, addrptr ptr);
void send_message(addrptr base, struct can_frame *can);
int receive_message(addrptr base, struct can_frame *can);
int device_open(can_dev *device);

int device_write(can_dev *device, can_frame frame);
can_frame* device_read(can_dev *device);

void mdelay(int d);
void display_can(struct can_frame *can);

/* IRQ */
#define IRQMP_BASE          0x80000200
#define IRQMP_P0_MASK_START IRQMP_BASE+0x40
#define IRQMP_ICLEAR          *(volatile unsigned int *)(IRQMP_BASE+0xc)
#define MASK_IRQ(cpu,irq)     (*(volatile unsigned int *)(IRQMP_P0_MASK_START+cpu*4))|=(1<<irq)
#define UN_MASK_IRQ(cpu,irq)  (*(volatile unsigned int *)(IRQMP_P0_MASK_START+cpu*4))&=(~(1<<irq))
#define enable_irq(irq)    MASK_IRQ(0,irq)
#define disable_irq(irq)   UN_MASK_IRQ(0,irq)
#define IRQ_CLEAR(irq)        IRQMP_ICLEAR|=(1<<irq)

extern void *catch_interrupt (void func(), int irq);

#endif
#endif
