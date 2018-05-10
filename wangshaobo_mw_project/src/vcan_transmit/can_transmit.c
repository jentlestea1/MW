/*
 *使用互斥同步锁来完成带阻塞类型的接口
 */
<<<<<<< HEAD

//vcan接口目前只支持在qemu上运行

=======
>>>>>>> 2a5957f... 做了较大改动,增加了条件编译,BC端和RT端都加入了vcan接口,但由于xml还不能读入以及测试数据文件无法打开的原因暂时还没有进行调试,目前使用__GCC_C99以及__TCPIP_TRANSMIT可以直接编译运行
#include "compile_type.h"
#ifdef __VCAN_TRANSMIT
#include "can_transmit.h"
#include "can_sys.h"
<<<<<<< HEAD
#include <fsu_pthread.h>
=======
#ifdef __SPARC_GCC_MMU
#include <fsu_pthread.h>
#endif
>>>>>>> 2a5957f... 做了较大改动,增加了条件编译,BC端和RT端都加入了vcan接口,但由于xml还不能读入以及测试数据文件无法打开的原因暂时还没有进行调试,目前使用__GCC_C99以及__TCPIP_TRANSMIT可以直接编译运行
#include "m_type.h"

//can_dev *device_recv;
//can_dev *device_send;

<<<<<<< HEAD
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
            return;   	 // No buffer, ignore this one.
		}
		receive_message(device_recv->mem_base, &(device_recv->rx_buf[device_recv->rx_in]));
        //printf("我触发了一次接收中断\n");
		device_recv->rx_in++;
		if (device_recv->rx_in >= BUFFERSIZE)
			device_recv->rx_in = 0;
	}

	if (temp & DOI) {
		printf("IRQ Overrun int\n");
		can_write8(CDO, device_recv->mem_base + SJA_COMMAND_REG); // Clear data overrun.
=======
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
		//printf("IRQ Receive buffer in(%d) out(%d) count(%d)\n",
		//			device->rx_in, device->rx_out, device->rx_count);
		
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
>>>>>>> 2a5957f... 做了较大改动,增加了条件编译,BC端和RT端都加入了vcan接口,但由于xml还不能读入以及测试数据文件无法打开的原因暂时还没有进行调试,目前使用__GCC_C99以及__TCPIP_TRANSMIT可以直接编译运行
	}

}

void init_device(){
    if(init_flag==1) return;
    else {
<<<<<<< HEAD
        device_send = (can_dev *)malloc(sizeof(can_dev));
        device_recv = (can_dev *)malloc(sizeof(can_dev));
	    memset(device_send, 0, sizeof(can_dev));
	    memset(device_recv, 0, sizeof(can_dev));
	    device_send->mem_base = (addrptr)0x80005000;
	    device_recv->mem_base = (addrptr)0x80005000;
        device_open(device_send);
        device_open(device_recv);
=======
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
>>>>>>> 2a5957f... 做了较大改动,增加了条件编译,BC端和RT端都加入了vcan接口,但由于xml还不能读入以及测试数据文件无法打开的原因暂时还没有进行调试,目前使用__GCC_C99以及__TCPIP_TRANSMIT可以直接编译运行
        catch_interrupt(canIrq_handler,CANSYS_IRQ_NO);  //捕获中断
        enable_irq(CANSYS_IRQ_NO);
        //
        init_flag=1;
    }
}

<<<<<<< HEAD
struct can_frame vcan_receive_frame(){
    can_frame *frame;
    while(device_recv->rx_in==device_recv->rx_out);
    frame = device_read(device_recv);
    //printf("size :%d 0x%x 0x%x",frame->can_dlc,*(UINT *)frame->data,*(UINT *)(frame->data+4));
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
    //printf("size :%d 0x%x 0x%x",frame.can_dlc,*(UINT *)frame.data,*(UINT *)(frame.data+4));
    //第一次接应该为大小帧，否则直接丢弃
    while(frame_type_detect(frame,NULL,&size,false)!=VCAN_SIZE_FRAME_FLAG){
        frame = vcan_receive_frame();
        //throw_event(0,NULL,EVT_RT_VCAN_RECV_SIZE_FRAME_ERR);
        printf("error,接收到非大小帧\n");
    }
    pack_size=size;
    printf("\n收到大小帧size:%d\n",size);
    while(recv_bytes<pack_size){
        frame = vcan_receive_frame();
        //printf("size :%d 0x%x 0x%x\n",frame.can_dlc,frame.data[0],frame.data[1]);
        frame_type_detect(frame,buf+recv_bytes,&size,true);
        recv_bytes+=size;
        if(recv_bytes>=r_size){
            printf("数据溢出\n");
            *recv_size=recv_bytes;
            return;
        }
    }
    if(recv_bytes>pack_size){
        printf("我收到了过多的数据,实际收到数据:%d,应该收到数据%d\n",recv_bytes,pack_size);
    }
    else if(recv_bytes==pack_size){
        printf("正确接受%dB大小数据\n\n",recv_bytes);
    }
    //int i=0;
    //for(i=0;i<recv_bytes;i++)
    //    printf("%x ",buf[i]);
    //printf("\n");
    *recv_size=recv_bytes;
}

int vcan_send_package(unsigned char *buf,unsigned int size){
    init_device();
    //printf("in vcan_send_data\n");
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
        //printf("last_cnt:%d\n",last_cnt);
        if(last_cnt==0&&i>=size){
            printf("发送丢失\n");
            return -1;
        }
=======
void vcan_receive_data(unsigned char *buf,unsigned int r_size,unsigned int *size){
    printf("in vcan_receive_data\n");
    init_device();
    *size=0;
    can_frame *frame;
    int recv_bytes=0;
    int recv_bytes_sum=0;
    int pack_size=-1;
    pthread_mutex_lock(&condition_mutex);
    pthread_cond_wait(&condition_cond,&condition_mutex);
    pthread_mutex_lock(&condition_mutex);
    while(true){   //应该接受一整条信息
        frame= device_read(device);
        recv_bytes=frame->can_dlc;
        recv_bytes_sum+=recv_bytes;
        int i=0;
        for(i=0;i<recv_bytes;i++){
            buf[recv_bytes_sum+i]=frame->data[i];
            printf("frame.data[%d]:%d\n",i,frame->data[i]);
        }
        if(pack_size==-1&&recv_bytes_sum>=4){
            pack_size=*(UINT *)buf;
        }
        if(pack_size==(recv_bytes_sum-4)){
            break;
        }
        else if(pack_size<(recv_bytes_sum-4)){
            printf("错误,接收到了%dB数据，数据总量应该为%dB\n",recv_bytes_sum-4,pack_size);
            break;
        }
    }

    *size=recv_bytes_sum;
}

int vcan_send_data(unsigned char *buf,unsigned int size){
    init_device();
    //printf("in vcan_send_data\n");
    can_frame cansnd;
	cansnd.can_id = 0x1;
    int i=0;
    for(i=0;i<size;){
	    cansnd.can_dlc = (size-i)>8?8:(size-i);
        int j=0;
        for(j=0;j<cansnd.can_dlc;j++){
            cansnd.data[j]=buf[i+j];
            //printf("%d %d 0x%x\n",j,i+j,buf[i+j]);
        }
        i+=cansnd.can_dlc;
        int last_cnt=device_write(device,cansnd);
        //printf("last_cnt:%d\n",last_cnt);
        if(last_cnt==0&&i>=size)return -1;
        cansnd.can_id=(cansnd.can_id+1)%1000;
>>>>>>> 2a5957f... 做了较大改动,增加了条件编译,BC端和RT端都加入了vcan接口,但由于xml还不能读入以及测试数据文件无法打开的原因暂时还没有进行调试,目前使用__GCC_C99以及__TCPIP_TRANSMIT可以直接编译运行
        //mdelay(500);
    }
    return 1;
}
<<<<<<< HEAD

void run_send(){
    unsigned char send_buff[]="wodejiazaijiangxishengjingdezhenshifuliangxianxihuxiang";//{'w','a','n','g','s','h','a','o','b','o','w','a','n','g','k','e','w','e','i'};
    printf("in send\n");
    int i=vcan_send_package(send_buff,55);
=======
void run_send(){
    unsigned char send_buff[]="wodejiazaijiangxishengjingdezhenshifuliangxianxihuxiang";//{'w','a','n','g','s','h','a','o','b','o','w','a','n','g','k','e','w','e','i'};
    printf("in send\n");
    int i=vcan_send_data(send_buff,55);
>>>>>>> 2a5957f... 做了较大改动,增加了条件编译,BC端和RT端都加入了vcan接口,但由于xml还不能读入以及测试数据文件无法打开的原因暂时还没有进行调试,目前使用__GCC_C99以及__TCPIP_TRANSMIT可以直接编译运行
    if(i==-1)printf("发送数据失败\n");
}
void run_receive(){   
    unsigned char recv_buff[1000];
    int size=0;
    int size_sum=0;
    int count=0;
    while(size_sum!=55&&count!=10){
<<<<<<< HEAD
        vcan_receive_package(recv_buff+size_sum,100,&size);
=======
        vcan_receive_data(recv_buff+size_sum,100,&size);
>>>>>>> 2a5957f... 做了较大改动,增加了条件编译,BC端和RT端都加入了vcan接口,但由于xml还不能读入以及测试数据文件无法打开的原因暂时还没有进行调试,目前使用__GCC_C99以及__TCPIP_TRANSMIT可以直接编译运行
        size_sum+=size;
        printf("buf:%s\nsize:%d\n",recv_buff,size);
        count++;
        //mdelay(2000);
    }
}
<<<<<<< HEAD

int test_send(){
    mdelay(1000);
    printf("start\n");
=======
/*
int main(){
    mdelay(1000);
    printf("start\n");
    pthread_init();
>>>>>>> 2a5957f... 做了较大改动,增加了条件编译,BC端和RT端都加入了vcan接口,但由于xml还不能读入以及测试数据文件无法打开的原因暂时还没有进行调试,目前使用__GCC_C99以及__TCPIP_TRANSMIT可以直接编译运行
    init_device();
    pthread_t tid2;
    pthread_create(&tid2,NULL,(pthread_func_t)run_receive,NULL);
    pthread_t tid1;
    pthread_create(&tid1,NULL,(pthread_func_t)run_send,NULL);
    mdelay(15000);
}
<<<<<<< HEAD
=======
*/

>>>>>>> 2a5957f... 做了较大改动,增加了条件编译,BC端和RT端都加入了vcan接口,但由于xml还不能读入以及测试数据文件无法打开的原因暂时还没有进行调试,目前使用__GCC_C99以及__TCPIP_TRANSMIT可以直接编译运行
#endif

