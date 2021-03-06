/*
 *使用互斥同步锁来完成带阻塞类型的接口
 */

//vcan接口目前只支持在qemu上运行

#include "compile_type.h"
#ifdef __VCAN_TRANSMIT
#include "can_transmit.h"
#include "can_sys.h"
#include <fsu_pthread.h>
#include "m_type.h"
#include "interval.h"
#include "handle_event.h"
#include "vcan_frame.h"

//can_dev *device_recv;
//can_dev *device_send;

//can_dev *device;//
can_dev *device_send;
can_dev *device_recv;
volatile int init_flag=0;


void canIrq_handler(){
	uint8_t temp;
    //发中断不做操作
	temp = can_read8(device_recv->mem_base + SJA_INT_REG); 
    //发送完触发一个中断
    
    /*
    if (temp & TI) {
        //printf("IRQ Transmit buffer in(%d) out(%d) count(%d)\n",
					device->tx_in, device->tx_out, device->tx_count);
		if ( device->tx_out !=device->tx_in ) {
			device->tx_out++;
			if (device->tx_out == BUFFERSIZE)
				device->tx_out = 0;
		}
	}*/
    

	if (temp & RI) {
		if((device_recv->rx_in+1)%BUFFERSIZE == device_recv->rx_out) {
   			can_write8(0x04, device_recv->mem_base + SJA_COMMAND_REG);// Release receive buffer.
			printf("ignored. \n");
            //pthread_mutex_lock(&condition_mutex);
            //pthread_cond_signal(&condition_cond);
            //pthread_mutex_unlock(&condition_mutex);


            return;   	 // No buffer, ignore this one.
		}
		receive_message(device_recv->mem_base, &(device_recv->rx_buf[device_recv->rx_in]));
		device_recv->rx_in++;
		if (device_recv->rx_in >= BUFFERSIZE)
			device_recv->rx_in = 0;
	}

	if (temp & DOI) {
        throw_event(0,NULL,EVT_VCAN_IRQ_OVERRUN);
		can_write8(CDO, device_recv->mem_base + SJA_COMMAND_REG); // Clear data overrun.
		
	}

}

void init_device(){
    if(init_flag==1) return;
    else {
        device_send = (can_dev *)malloc(sizeof(can_dev));
        device_recv = (can_dev *)malloc(sizeof(can_dev));
	    memset(device_send, 0, sizeof(can_dev));
	    memset(device_recv, 0, sizeof(can_dev));
	    device_send->mem_base = (addrptr)0x80005000;
	    device_recv->mem_base = (addrptr)0x80005000;
        device_open(device_send);
        device_open(device_recv);
        catch_interrupt(canIrq_handler,CANSYS_IRQ_NO);  //捕获中断
        enable_irq(CANSYS_IRQ_NO);
        init_flag=1;
    }
}

struct can_frame vcan_receive_frame(){
    can_frame *frame;

    while(device_recv->rx_in==device_recv->rx_out);

    frame = device_read(device_recv);
    return *frame;
}


void vcan_receive_package(unsigned char *buf,unsigned int r_size,unsigned int *recv_size){
    init_device();
    int n;
    UINT pack_size;
    UINT size;
    UINT recv_bytes=0;
    struct can_frame frame;
    frame = vcan_receive_frame();
    while(frame_type_detect(frame,NULL,&size,false)!=VCAN_SIZE_FRAME_FLAG){
        frame = vcan_receive_frame();
        throw_event(0,NULL,EVT_VCAN_RECV_SIZE_FRAME_ERR);
    }
    pack_size=size;
    while(recv_bytes<pack_size){
        frame = vcan_receive_frame();
        frame_type_detect(frame,buf+recv_bytes,&size,true);
        recv_bytes+=size;
        if(recv_bytes>=r_size){
            throw_event(0,NULL,EVT_VCAN_RECV_BUF_LIMIT_ERR);
            *recv_size=recv_bytes;
            return;
        }
    }
    if(recv_bytes>pack_size){
        throw_event(0,NULL,EVT_VCAN_RECV_PACKAGE_ERR);
    }
    *recv_size=recv_bytes;
}

int vcan_send_package(unsigned char *buf,unsigned int size){
    init_device();
    struct can_frame frame;
	frame=serial_frame(VCAN_SIZE_FRAME_FLAG,NULL,size);
    device_write(device_send,frame);
    //mdelay(500);

   int i=0;

    for(i=0;i<size;){
	    UINT frame_size_tmp = (size-i)>8?8:(size-i);
        frame=serial_frame(VCAN_DATA_FRAME_FLAG,buf+i,frame_size_tmp);
        i+=frame_size_tmp;
        int last_cnt=device_write(device_send,frame);
        if(last_cnt==0&&i>=size){
            throw_event(0,NULL,EVT_VCAN_SEND_PACKAGE_ERR);
            return -1;
        }


        //mdelay(500);
    }
    return 1;
}

void run_send(){
    unsigned char send_buff[]="wodejiazaijiangxishengjingdezhenshifuliangxianxihuxiang";//{'w','a','n','g','s','h','a','o','b','o','w','a','n','g','k','e','w','e','i'};
    printf("in send\n");
    int i=vcan_send_package(send_buff,55);

    if(i==-1)printf("发送数据失败\n");
}
void run_receive(){   
    unsigned char recv_buff[1000];
    int size=0;
    int size_sum=0;
    int count=0;
    while(size_sum!=55&&count!=10){
        vcan_receive_package(recv_buff+size_sum,100,&size);

        size_sum+=size;
        printf("buf:%s\nsize:%d\n",recv_buff,size);
        count++;
        //mdelay(2000);
    }
}

int test_send(){
    mdelay(1000);
    printf("start\n");
    init_device();
    pthread_t tid2;
    pthread_create(&tid2,NULL,(pthread_func_t)run_receive,NULL);
    pthread_t tid1;
    pthread_create(&tid1,NULL,(pthread_func_t)run_send,NULL);
    mdelay(15000);
}
#endif
