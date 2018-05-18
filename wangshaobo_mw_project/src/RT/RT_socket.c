#include "compile_type.h"
#include<stdio.h>
#include<stdlib.h> 
#include<pthread.h>
#include<math.h>
#include<stdlib.h>  
#include<unistd.h>
#include<string.h>  
#include<errno.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>
#include<pthread.h>
#ifdef __RT_VCAN_TRANSMIT
#define __RT_INCLUDE
#include <net/if.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include "vcan_frame.h"
#endif
#include "file.h"
#include "relevant_struct_def.h"
#include "RT_socket.h"
#include "interval.h"
#include "handle_event.h"

#ifdef __RT_VCAN_TRANSMIT
/*同步锁用来在初始化好了端口后启动接收数据*/
pthread_mutex_t RT_recv_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  RT_recv_cond  = PTHREAD_COND_INITIALIZER;

static int s;
void init_vcan_handler(){
	struct ifreq ifr;
    struct sockaddr_can addr;
	const char *ifname = "vcan0";
	if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Error while opening socket");
		return;
	}

	strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);
	
	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Error in socket bind");
		return;
	}
    
}

int RT_send_frame(struct can_frame frame){
    int n;
	n = write(s, &frame, sizeof(struct can_frame));
    return n;
}

UINT RT_receive_package(unsigned char *buffer){   //返回接收到的全帧大小,buffer大小满足情况
    int n;
    UINT pack_size;
    UINT size;
    UINT recv_bytes=0;
    struct can_frame frame;
    n = read(s, &frame, sizeof(struct can_frame));
    //第一次接应该为大小帧，否则直接丢弃
    while(frame_type_detect(frame,NULL,&size,false)!=VCAN_SIZE_FRAME_FLAG){
        n = read(s, &frame, sizeof(struct can_frame));
    }
    pack_size=size;
    //printf("RT接收到大小帧size:%d\n",size);
    while(recv_bytes<pack_size){
        n = read(s, &frame, sizeof(struct can_frame));
        frame_type_detect(frame,buffer+recv_bytes,&size,true);
        recv_bytes+=size;
    }
    if(recv_bytes>pack_size)
        throw_event(0,NULL,RT_EVT_RECV_PACKAGE_ERR);
        //printf("我收到了过多的数据,实际收到数据:%d,应该收到数据%d\n",recv_bytes,pack_size);
    //else if(recv_bytes==pack_size)
    //    printf("RT收到正确的数据帧\n");
    return recv_bytes;
}

#endif


void* create_RT_socket_server(void* RT_port){ 
#ifdef PTHREAD_RECYCLE
    pthread_detach(pthread_self());
#endif
    unsigned char    buffer[4096];  
    UINT size;
#ifdef __RT_TCPIP_TRANSMIT
    port_con* p_RT_port=(port_con*)RT_port;
    UINT port=p_RT_port->port;
    UINT child_port;
    int     n; 
    int    socket_fd, connect_fd;  
    struct sockaddr_in     servaddr;  
    if( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
    }  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(port);//
    if( bind(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){  
        printf("RT--bind socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
    }  
    if( listen(socket_fd, 10) == -1){  
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
    }  
    while(1){
        if( (connect_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1){  
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);  
            continue;  
        }  
        n = recv(connect_fd, buffer, 4096, 0); 
        buffer[n]='\0';
        RT_handle_package(buffer,n);
        close(connect_fd);  
    }  
    close(socket_fd);  
#elif __RT_VCAN_TRANSMIT
	UINT nbytes;
    pthread_mutex_lock(&RT_recv_mutex);
    pthread_cond_wait(&RT_recv_cond,&RT_recv_mutex);
    pthread_mutex_unlock(&RT_recv_mutex);
    while(true){
        //阻塞状态不需要sleep
        nbytes=RT_receive_package(buffer);
        RT_handle_package(buffer,nbytes);
    }
#endif

}

///*dev测试用*/
//void create_RT_socket_client(char* buffer,UINT port){
//    int    sockfd, recv_len;
//    struct sockaddr_in    servaddr;  
//    unsigned char recv_buffer[4096];
//    UINT size;
//    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){  
//    printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);  
//    exit(0);  
//    }  
//    memset(&servaddr, 0, sizeof(servaddr));  
//    servaddr.sin_family = AF_INET;  
//    servaddr.sin_port = htons(port); 
//    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){  
//    printf("connect error: %s(errno: %d)\n",strerror(errno),errno);  
//    exit(0);  
//    }  
//    if( send(sockfd, buffer, strlen(buffer), 0) < 0)  
//    {  
//    printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);  
//    exit(0);  
//    }  
//    recv_len = recv(sockfd, recv_buffer,4096, 0);
//    recv_buffer[recv_len]='\0';
//    if(recv_len!=0){
//        /*测试用*/
//        //write_write_buffer(port,recv_buffer,recv_len,&size);
//        //if(size!=recv_len){
//        //    printf("ERR:写入RT buffer过程丢失数据\n");
//        //}
//    }
//    close(sockfd);  
//    return;
//}

void* create_RT_ret_socket_client(void* RT_port){//以原port+1发
#ifdef PTHREAD_RECYCLE
    pthread_detach(pthread_self());
#endif
    sleep_ms(500);
    unsigned char ret_buff[4096]={0};
    UINT ret_size;
#ifdef __RT_TCPIP_TRANSMIT
    port_con* p_RT_port=(port_con*)RT_port;
    UINT port=p_RT_port->port+1;
    int    sockfd, n,recv_len;  
    struct sockaddr_in    servaddr;
    //第一次要初始化RT端口
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){  
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);  
        exit(0);  
    }  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(port); 
    memset(ret_buff,0,4096);
    ret_buff[0]=0x2;
    ret_buff[1]=0x0;
    ret_buff[2]=0xff;
    //请求获取端口列表
    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){  
        printf("RT--connect error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
    }
    if(send(sockfd,ret_buff,sizeof(ret_buff),0) == -1)  
        perror("send error");  
    memset(ret_buff,0,4096);
    recv_len = recv(sockfd, ret_buff,4096, 0);
    //初始化RT子地址表,该表遵循优先级从大到小,len指代所述表长度
    init_port_array((UINT *)(ret_buff+8),*(UINT *)(ret_buff+4));
    close(sockfd);
    while(1){
        sleep_ms(30);
        if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){  
            printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);  
            exit(0);  
        }  
        //memset(&servaddr, 0, sizeof(servaddr));  
        //servaddr.sin_family = AF_INET;  
        //servaddr.sin_port = htons(port); 
        memset(ret_buff,0,4096);
        pack_package(ret_buff,4096,&ret_size);
        if(ret_size==0){
            close(sockfd);
            continue;
        }
        if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){  
            printf("RT--connect error: %s(errno: %d)\n",strerror(errno),errno);  
            exit(0);  
        }
        if(send(sockfd,ret_buff, ret_size,0) == -1)  
            perror("send error");  
        close(sockfd);
    }  
    close(sockfd);  
    exit(0);
#elif __RT_VCAN_TRANSMIT
	struct can_frame frame;
	int nbytes;
    frame=serial_frame(VCAN_SIZE_FRAME_FLAG,NULL,0x2);
	nbytes = RT_send_frame(frame);
    sleep_ms(10);
    frame=serial_frame(VCAN_INIT_PORT_FRAME_FLAG,NULL,0);
	nbytes = RT_send_frame(frame);
    RT_receive_package(ret_buff);
    UINT port_len=*(UINT *)ret_buff;
    port_len=htonl(port_len);
    init_port_array((UINT *)(ret_buff+sizeof(UINT)),port_len);
    //初始化完成之后再创建RT_server
    pthread_mutex_lock(&RT_recv_mutex);
    pthread_cond_signal(&RT_recv_cond);
    pthread_mutex_unlock(&RT_recv_mutex);
    //正式发送数据
    while(true){
        sleep_ms(100);
        memset(ret_buff,0,4096);
        pack_package(ret_buff,4096,&ret_size);
        int i=0;
        if(ret_size==0)
            continue;
        frame=serial_frame(VCAN_SIZE_FRAME_FLAG,NULL,ret_size);
        RT_send_frame(frame);
        sleep_ms(10);
        UINT frame_size_tmp;
        //printf("ret_size:%d\n",ret_size);
        for(i=0;i<ret_size;){
	        frame_size_tmp = (ret_size-i)>8?8:(ret_size-i);
            //printf("frame_size_tmp:%d\n",frame_size_tmp);
            frame=serial_frame(VCAN_DATA_FRAME_FLAG,ret_buff+i,frame_size_tmp);
            i+=frame_size_tmp;
            RT_send_frame(frame);
            sleep_ms(10);
        }
    }
#endif
}

void set_RT_port(void* p_port_con,UINT port){
    port_con* p_port_con_tmp=(port_con*)p_port_con;
    p_port_con_tmp->port=port;
}

/*void create_RT_unit(UINT port,UINT child_port){
    init_port_array(port);
    set_RT_port(port,child_port);
    pthread_t tid1;
    pthread_create(&tid1,NULL,create_RT_socket_server,(void*)&RT_port);
    char a;
    scanf("y or n:%c",&a);
    if(a=='n')exit(0);
    pthread_t tid2;
    pthread_create(&tid2,NULL,create_RT_ret_socket_client,(void*)&RT_port);
}
*/
/*
void* get_one_port_con(){
    port_con* p=(port_con*)malloc(sizeof(port_con));
    return (void*)p;
}
*/


/*********************************************************
 *
 *generate_data_*函数模拟设备产生数据
 *
 *********************************************************/
void* generate_data_1(void* argc){
#ifdef PTHREAD_RECYCLE
    pthread_detach(pthread_self());
#endif
    printf("1号数据源即将产生数据\n");
    sleep_ms(5000);
    int turns=2;
    while(turns--){
    sleep_ms(1000);
    unsigned char recv_buffer[5];
    static double d=20.005;
    static int d1=20;
    int d2=5;
    int d3=3;
    UINT size;
    UINT time;
    UINT cnt=TIMES;
    timeStamp t;
    while(cnt--){
        recv_buffer[0]=d1;
        recv_buffer[1]=d2;
        recv_buffer[2]=d3;
        recv_buffer[3]='\0';
        time=m_random();
        sleep_ms(100*time);
        write_write_buffer(8001,recv_buffer,strlen(recv_buffer),&size);
        if(size!=3)printf("generate data err!\n");
        get_current_time(&t);
        printf("位置：RT，类型：发送；数据：%f；大小：%d；端口：%d    时间戳：%d/%d/%d\n",d,size,8001,((timeStamp*)&t)->hour,((timeStamp*)&t)->minute,((timeStamp*)&t)->second);
        add_string(SEND,d,8001);
        //d=20.005+(time%10);
        //d1=20+(time%10);
    }
    }
    set_is_end();
}

void* generate_data_2(void* argc){
#ifdef PTHREAD_RECYCLE
    pthread_detach(pthread_self());
#endif
    printf("2号数据源即将产生数据\n");
    sleep_ms(5000);
    int turns=2;
    while(turns--){
    sleep_ms(1000);
    unsigned char recv_buffer[5];
    static double d=30.01;
    static int d1=30;
    int d2=1;
    int d3=2;
    UINT size;
    UINT time;
    UINT cnt=TIMES;
    timeStamp t;
    while(cnt--){
        recv_buffer[0]=d1;
        recv_buffer[1]=d2;
        recv_buffer[2]=d3;
        recv_buffer[3]='\0';
        time=m_random();
        sleep_ms(100*time);
        write_write_buffer(8002,recv_buffer,strlen(recv_buffer),&size);
        if(size!=3)printf("generate data err!\n");
        get_current_time(&t);
        printf("位置：RT，类型：发送；数据：%f；大小：%d；端口：%d    时间戳：%d/%d/%d\n",d,size,8002,((timeStamp*)&t)->hour,((timeStamp*)&t)->minute,((timeStamp*)&t)->second);
        add_string(SEND,d,8002);
        //d=30.01+(time%10);
        //d1=30+(time%10);
    }
    }
    set_is_end();
}

void* generate_data_4(void* argc){
#ifdef PTHREAD_RECYCLE
    pthread_detach(pthread_self());
#endif
    printf("4号数据源即将产生数据\n");
    sleep_ms(5000);
    int turns=2;
    while(turns--){
    sleep_ms(1000);
    unsigned char recv_buffer[5];
    static int d=4;
    UINT size;
    UINT time;
    UINT cnt=TIMES;
    timeStamp t;
    while(cnt--){
        recv_buffer[0]=d;
        recv_buffer[1]='\0';
        time=m_random();
        sleep_ms(100*time);
        write_write_buffer(8004,recv_buffer,strlen(recv_buffer),&size);
        if(size!=1)printf("generate data err!\n");
        get_current_time(&t);
        printf("位置：RT，类型：发送；数据：%d；大小：%d；端口：%d    时间戳：%d/%d/%d\n",recv_buffer[0],size,8004,((timeStamp*)&t)->hour,((timeStamp*)&t)->minute,((timeStamp*)&t)->second);
        add_string(SEND,recv_buffer[0],8004);
        //d++;
    }
    }
    set_is_end();
}

void* generate_data_5(void* argc){
#ifdef PTHREAD_RECYCLE
    pthread_detach(pthread_self());
#endif
    printf("5号数据源即将产生数据\n");
    sleep_ms(5000);
    int turns=2;
    while(turns--){
    sleep_ms(1000);
    unsigned char recv_buffer[5];
    static int d=5;
    UINT size;
    UINT time;
    UINT cnt=TIMES;
    timeStamp t;
    while(cnt--){
        recv_buffer[0]=d;
        recv_buffer[1]='\0';
        time=m_random();
        sleep_ms(100*time);
        write_write_buffer(8005,recv_buffer,strlen(recv_buffer),&size);
        if(size!=1)printf("generate data err!\n");
        get_current_time(&t);
        printf("位置：RT，类型：发送；数据：%d；大小：%d；端口：%d    时间戳：%d/%d/%d\n",recv_buffer[0],size,8005,((timeStamp*)&t)->hour,((timeStamp*)&t)->minute,((timeStamp*)&t)->second);
        add_string(SEND,recv_buffer[0],8005);
        //d++;
    }
    }
    set_is_end();
}

void* generate_data_6(void* argc){
#ifdef PTHREAD_RECYCLE
    pthread_detach(pthread_self());
#endif
    printf("6号数据源即将产生数据\n");
    sleep_ms(5000);
    int turns=2;
    while(turns--){
    sleep_ms(1000);
    unsigned char recv_buffer[5];
    static int d=6;
    UINT size;
    UINT time;
    UINT cnt=TIMES;
    timeStamp t;
    while(cnt--){
        recv_buffer[0]=d;
        recv_buffer[1]='\0';
        time=m_random();
        sleep_ms(100*time);
        write_write_buffer(8006,recv_buffer,strlen(recv_buffer),&size);
        if(size!=1)printf("generate data err!\n");
        get_current_time(&t);
        printf("位置：RT，类型：发送；数据：%d；大小：%d；端口：%d    时间戳：%d/%d/%d\n",recv_buffer[0],size,8006,((timeStamp*)&t)->hour,((timeStamp*)&t)->minute,((timeStamp*)&t)->second);
        add_string(SEND,recv_buffer[0],8006);
        //d++;
    }
    }
    set_is_end();
}

void* generate_data_7(void* argc){
#ifdef PTHREAD_RECYCLE
    pthread_detach(pthread_self());
#endif
    printf("7号数据源即将产生数据\n");
    sleep_ms(5000);
    int turns=2;
    while(turns--){
    sleep_ms(1000);
    unsigned char recv_buffer[5];
    static int d=7;
    UINT size;
    UINT time;
    UINT cnt=TIMES;
    timeStamp t;
    while(cnt--){
        recv_buffer[0]=d;
        recv_buffer[1]='\0';
        time=m_random();
        sleep_ms(100*time);
        write_write_buffer(8007,recv_buffer,strlen(recv_buffer),&size);
        if(size!=1)printf("generate data err!\n");
        get_current_time(&t);
        printf("位置：RT，类型：发送；数据：%d；大小：%d；端口：%d    时间戳：%d/%d/%d\n",recv_buffer[0],size,8007,((timeStamp*)&t)->hour,((timeStamp*)&t)->minute,((timeStamp*)&t)->second);
        add_string(SEND,recv_buffer[0],8007);
        //d++;
    }
    }
    set_is_end();
}
/*********************************************************
 *
 *generate_data_*函数模拟设备产生数据
 *
 *********************************************************/

void generate_data(void){
    pthread_t tid;
    pthread_create(&tid,NULL,generate_data_1,NULL);
    pthread_create(&tid,NULL,generate_data_2,NULL);
    pthread_create(&tid,NULL,generate_data_4,NULL);
    pthread_create(&tid,NULL,generate_data_5,NULL);
    pthread_create(&tid,NULL,generate_data_6,NULL);
    pthread_create(&tid,NULL,generate_data_7,NULL);
}

//下面两个函数创建RT的socket
void* RT_socket_pthread_func(void* p_RT_config){
#ifdef PTHREAD_RECYCLE
    pthread_detach(pthread_self());
#endif
    pthread_t tid;
    int err;
    err=pthread_create(&tid,NULL,create_RT_socket_server,p_RT_config);
    if(err!=0)
        throw_event(0,NULL,EVT_CREATE_THREAD_ERR);
}

void* RT_ret_socket_pthread_func(void* p_RT_config){
#ifdef PTHREAD_RECYCLE
    pthread_detach(pthread_self());
#endif
    pthread_t tid;
    int err;
    err=pthread_create(&tid,NULL,create_RT_ret_socket_client,p_RT_config);
    if(err!=0)
        throw_event(0,NULL,EVT_CREATE_THREAD_ERR);
        //printf("RT 发端创建线程失败...\n");
}

void create_RT_unit(void* p_RT_config){
    pthread_t tid1;
    pthread_t tid2;
    UINT err1,err2=0;
    err1=pthread_create(&tid1,NULL,RT_socket_pthread_func,p_RT_config);
    err2=pthread_create(&tid2,NULL,RT_ret_socket_pthread_func,p_RT_config);
    if(err1!=0||err2!=0)
        throw_event(0,NULL,EVT_CREATE_THREAD_ERR);
    else printf("成功启动一个RT模拟端口,端口号:%d...\n",((port_con*)p_RT_config)->port);
}

void initialize_RT(void){
#ifdef __RT_TCPIP_TRANSMIT
    //初始化端口号为7000的socket线程作为创建其他线程的基线程
    int    sockfd,recv_len;  
    unsigned char buff[4096]={0};
    struct sockaddr_in servaddr;
    //第一次要初始化RT端口
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){  
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);  
        exit(0);  
    }  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(7000); 
    memset(buff,0,4096);
    buff[0]=0x2;
    buff[1]=0x0;
    buff[2]=0xff;
    //请求获取端口列表
    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){  
        printf("RT--connect error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
    }
    if(send(sockfd,buff, sizeof(buff),0) == -1)  
        perror("send error");  
    memset(buff,0,4096);
    recv_len = recv(sockfd,buff,4096, 0);
    int i=0;
    UINT port_len=*(UINT *)(buff+4);
    UINT *p=(UINT *)(buff+8);
    for(i=0;i<port_len;i++){
        port_con RT_config;
        set_RT_port(&RT_config,*p);
        create_RT_unit(&RT_config);
    }
    close(sockfd);
#elif __RT_VCAN_TRANSMIT
    //vcan0与端口无关
    init_vcan_handler();
    port_con RT_config;
    set_RT_port(&RT_config,0);
    create_RT_unit(&RT_config);
#endif
}

