/*
 *使用互斥同步锁来完成带阻塞类型的接口
 */

#include "can_transmit.h"
#include "can_sys.h"
#include <fsu_pthread.h>

//can_dev *device_recv;
//can_dev *device_send;

can_dev *device;
volatile int init_flag=0;

//rx_out_mutex用来界定现在是否需要释放资源，否则每次执行中断函数都会释放资源
//pthread_mutex_t rx_out_mutex     = PTHREAD_MUTEX_INITIALIZER(count_mutex);
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER(condition_mutex);
pthread_cond_t  condition_cond  = PTHREAD_COND_INITIALIZER(condition_cond);

void canIrq_handler(){
	//uint8_t temp_recv;
	//uint8_t temp_send;
	uint8_t temp;

	//temp_recv = can_read8(device_recv->mem_base + SJA_INT_REG); 
	//temp_send = can_read8(device_send->mem_base + SJA_INT_REG); 
	temp = can_read8(device->mem_base + SJA_INT_REG); 
	
    //发送完触发一个中断
    
    
    //if (temp_send & TI) {
    if (temp & TI) {
        printf("IRQ Transmit buffer in(%d) out(%d) count(%d)\n",
					device->tx_in, device->tx_out, device->tx_count);
		//if (device_send->tx_count > 0) {
        //tx_in为可插入的位置
		if ( device->tx_out !=device->tx_in ) {
			//send_message(device->mem_base, &(device->tx_buf[device->tx_out]));
			device->tx_out++;
			if (device->tx_out == BUFFERSIZE)
				device->tx_out = 0;
			//可能被同时访问
            //device_send->tx_count--;
		}
	}
    

	if (temp & RI) {
		printf("IRQ Receive buffer in(%d) out(%d) count(%d)\n",
					device->rx_in, device->rx_out, device->rx_count);
		
		//if(device_recv->rx_count >= BUFFERSIZE) {
		if((device->rx_in+1)%BUFFERSIZE == device->rx_out) {
   			can_write8(0x04, device->mem_base + SJA_COMMAND_REG);// Release receive buffer.
			printf("ignored. \n");
            return;   	 // No buffer, ignore this one.
		}
        //注意这里rx_count可能会被同时访问
		//device_recv->rx_count++;
		receive_message(device->mem_base, &(device->rx_buf[device->rx_in]));
        //加入信号量
        pthread_mutex_lock(&condition_mutex);
        pthread_cond_signal(&condition_cond);
        pthread_mutex_unlock(&condition_mutex);

		device->rx_in++;
		if (device->rx_in >= BUFFERSIZE)
			device->rx_in = 0;

	}

	//if (temp_send & DOI||temp_recv & DOI) {
	if (temp & DOI) {
		printf("IRQ Overrun int\n");
        //一般不会出现缓冲区溢出的现象
		//can_write8(CDO, device_send->mem_base + SJA_COMMAND_REG); // Clear data overrun.
		//can_write8(CDO, device_recv->mem_base + SJA_COMMAND_REG); // Clear data overrun.
		can_write8(CDO, device->mem_base + SJA_COMMAND_REG); // Clear data overrun.
	}

}

void init_device(){
    if(init_flag==1) return;
    else {
        /*
        device_recv = (can_dev *)malloc(sizeof(can_dev));
        device_send = (can_dev *)malloc(sizeof(can_dev));
	    memset(device_send, 0, sizeof(can_dev));
	    memset(device_recv, 0, sizeof(can_dev));
	    device_recv->mem_base = (addrptr)0x80005000;
	    device_send->mem_base = (addrptr)0x80005000;
        device_open(device_recv);
        device_open(device_send);
        catch_interrupt(canIrq_handler,CANSYS_IRQ_NO);  //捕获中断
        enable_irq(CANSYS_IRQ_NO);
        //
        init_flag=1;
        */
        device = (can_dev *)malloc(sizeof(can_dev));
	    memset(device, 0, sizeof(can_dev));
	    device->mem_base = (addrptr)0x80005000;
        device_open(device);
        catch_interrupt(canIrq_handler,CANSYS_IRQ_NO);  //捕获中断
        enable_irq(CANSYS_IRQ_NO);
        //
        init_flag=1;
    }
}

void vcan_receive_data(unsigned char *buf,unsigned int r_size,unsigned int *size){
    //printf("in1\n");
    //init_device();
    //printf("in2\n");
    *size=0;
    int size_tmp=0;
    can_frame *frame;
    int i=0;
    //mdelay(4500);
    pthread_mutex_lock(&condition_mutex);
    printf("我被阻塞\n");
    pthread_cond_wait(&condition_cond,&condition_mutex);
    pthread_mutex_lock(&condition_mutex);
    printf("我被激活\n");
    while(device->rx_out != device->rx_in){
        frame= device_read(device);
        for(i=0;i<frame->can_dlc;i++){
            buf[size_tmp++]=frame->data[i];
        }
        if(r_size-size_tmp<8)break;
    }

    *size=size_tmp;
}

int vcan_send_data(unsigned char *buf,unsigned int size){
    //init_device();
    printf("in vcan_send_data\n");
    can_frame cansnd;
	cansnd.can_id = 0x1;
    int i=0;
    for(i=0;i<size;){
	    cansnd.can_dlc = (size-i)>8?8:(size-i);
        int j=0;
        for(j=0;j<cansnd.can_dlc;j++){
            cansnd.data[j]=buf[i+j];
            printf("%d %d 0x%x\n",j,i+j,buf[i+j]);
        }
        i+=cansnd.can_dlc;
        int last_cnt=device_write(device,cansnd);
        //printf("last_cnt:%d\n",last_cnt);
        if(last_cnt==0&&i>=size)return -1;
        cansnd.can_id=(cansnd.can_id+1)%1000;
        //mdelay(500);
    }
    return 1;
}
void run_send(){
    unsigned char send_buff[]="wodejiazaijiangxishengjingdezhenshifuliangxianxihuxiang";//{'w','a','n','g','s','h','a','o','b','o','w','a','n','g','k','e','w','e','i'};
    printf("in send\n");
    int i=vcan_send_data(send_buff,55);
    if(i==-1)printf("发送数据失败\n");
}
void run_receive(){   
    unsigned char recv_buff[1000];
    int size=0;
    int size_sum=0;
    int count=0;
    while(size_sum!=55&&count!=10){
        vcan_receive_data(recv_buff+size_sum,100,&size);
        size_sum+=size;
        printf("buf:%s\nsize:%d\n",recv_buff,size);
        count++;
        //mdelay(2000);
    }
}

int main(){
    mdelay(1000);
    printf("start\n");
    pthread_init();
    init_device();
    pthread_t tid2;
    pthread_create(&tid2,NULL,(pthread_func_t)run_receive,NULL);
    pthread_t tid1;
    pthread_create(&tid1,NULL,(pthread_func_t)run_send,NULL);
    mdelay(15000);
}



