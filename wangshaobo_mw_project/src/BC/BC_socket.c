#include "compile_type.h"
#include "BC_socket.h"
#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
#ifdef __TCPIP_TRANSMIT
#include<errno.h>  
#include<sys/types.h>  
#include<sys/socket.h>  
#include<netinet/in.h>  
#elif __VCAN_TRANSMIT
#include "can_transmit.h"
#endif
#include<unistd.h>
#include "control_package.h"
#include "handle_event.h"
#include "config_1553.h"
#ifdef __GCC_C99
#include<pthread.h>
#elif __SPARC_GCC_MMU
#include<fsu_pthread.h>
#endif
#include "BC_control.h"
#include "sync_collect.h"
#include "interval.h"

static unsigned char read_buf_1553[READ_BUF_1553_MAX_SIZE][BUF_MAX_LEN]={0};
static unsigned int read_buf_1553_size[READ_BUF_1553_MAX_SIZE]={0};
static bool is_read_buf_1553_avail[READ_BUF_1553_MAX_SIZE][RT_MAX_NUM]={0};

//对每一个BC/RT，有且仅有一个收线程和一个发线程

/*
 *使用socket收发两端自由，没有遵循BC-RT模式
 */

void create_bus_socket_client(UINT config_id,UINT RT_config_id,UINT port){  

    void *p_sync=get_sync_collect(HASH_CONTROL_PACKAGE_SCAN_FLAG,config_id,RT_config_id,NULL);
#ifdef __TCPIP_TRANSMIT
    sleep_ms(1000);
    int    sockfd, n,rec_len;  
    struct sockaddr_in    servaddr;
    void* p_config_node_tmp=get_config_node(config_id);
    UINT traffic_repos_id=get_config_node_traffic_repos_id(p_config_node_tmp);
    while(1){
    //需要加同步锁模块，节省cpu资源
    //if(!get_buffer_is_avail(config_id,RT_config_id))continue;
    vi_wait(p_sync);
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){  
    printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);  
    exit(0);  
    }  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(port);  
    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){  
    printf("bus--connect error: %s(errno: %d)\n",strerror(errno),errno);  
    exit(0);  
    }
    //if(get_buffer_is_avail(config_id,RT_config_id)){
    //    set_buffer_unavail(config_id,RT_config_id);
    //        if(send(sockfd,read_buf_1553[config_id],read_buf_1553_size[config_id],0) == -1)  
    //            perror("send error");
    //        //printf("已经发送%d的数据\n",read_buf_1553_size[config_id]);
    //        read_buf_1553_size[config_id]=0;
    //        memset(read_buf_1553[config_id],0,BUF_MAX_LEN);
    //}
    if(send(sockfd,read_buf_1553[config_id],read_buf_1553_size[config_id],0) == -1)  
            perror("send error");
    read_buf_1553_size[config_id]=0;
    memset(read_buf_1553[config_id],0,BUF_MAX_LEN);

    close(sockfd);  
    }
    close(sockfd);  
    exit(0);  

#elif __VCAN_TRANSMIT

    while(1){
        vi_wait(p_sync);
        if(vcan_send_package(read_buf_1553[config_id],read_buf_1553_size[config_id])==-1){
                printf("send data error\n");
        }
        memset(read_buf_1553[config_id],0,read_buf_1553_size[config_id]);
        read_buf_1553_size[config_id]=0;
        
        //if(get_buffer_is_avail(config_id,RT_config_id)){
        //    set_buffer_unavail(config_id,RT_config_id);
        //    if(vcan_send_package(read_buf_1553[config_id],read_buf_1553_size[config_id])==-1){
        //        printf("send data error\n");
        //}
        //memset(read_buf_1553[config_id],0,read_buf_1553_size[config_id]);
        //read_buf_1553_size[config_id]=0;
        //}
    }

#endif

}

static unsigned char    recv_buffer[4096];  
static bool send_port_array_flag =false;       
void create_bus_socket_server(UINT config_id,UINT port)  //原port+1用来接受传回的数据
{  
        int recv_len;  
        void* p_config_node_tmp=get_config_node(config_id);
        UINT traffic_repos_id=get_config_node_traffic_repos_id(p_config_node_tmp);
#ifdef __TCPIP_TRANSMIT

        int    socket_fd, connect_fd;  
        struct sockaddr_in     servaddr;  
        if( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
        }  
        memset(&servaddr, 0, sizeof(servaddr));  
        servaddr.sin_family = AF_INET;  
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//IP地址设置成INADDR_ANY,让系统自动获取本机的IP地址。  
        servaddr.sin_port = htons(port+1);//
        if( bind(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){  
        printf("bus--bind socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
        }  
        if( listen(socket_fd, 10) == -1){  
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
        }
        printf("等待与端口号为%d的RT建立连接\n",port);
        while(1){  
        //阻塞直到有客户端连接，不然多浪费CPU资源。  
            if( (connect_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1){  
                printf("accept socket error: %s(errno: %d)",strerror(errno),errno);  
                continue;  
            }  
        //printf("与端口号为 %d的RT建立连接\n",port);
        memset(recv_buffer,0,4096);
        recv_len = recv(connect_fd, recv_buffer,MAXLINE, 0);  
        recv_buffer[recv_len] = '\0';
        //printf("%d %d %d\n",recv_len,recv_buffer[0],recv_buffer[1]);
        //printf("recv: %d\n",recv_len);
        if(recv_len!=0){
            //printf("----%d %d\n",recv_buffer[0],recv_buffer[1]);
            if(send_port_array_flag==false&&recv_buffer[1]==0x0&&recv_buffer[2]==0xff){
                //发送端口列表给RT
                memset(recv_buffer,0,4096);
                UINT port_len=get_RT_sub_addr_array(port,(UINT *)(recv_buffer+8));
                *(UINT *)(recv_buffer+4)=port_len;
                *(UINT *)recv_buffer=(port_len+1)*sizeof(int);
                //printf("%d %d %d",port_len,*(UINT*)(recv_buffer+4),*(UINT*)(recv_buffer+8));
                if(send(connect_fd,recv_buffer,4096,0) == -1)  
                    perror("发送RT端口子地址列表给RT失败\n");
                else{
                    printf("成功发送RT端口子地址列表给端口号为%d的RT\n",port);
                    send_port_array_flag=true;
                }
            }
            else{
                //printf("recv: %d\n",recv_len);
                ctrl_unpack_package_to_1553(traffic_repos_id,port,recv_buffer,recv_len);
            }
        }  
        close(connect_fd);  
    }  
        close(socket_fd);  

#elif __VCAN_TRANSMIT

    while(1){
        vcan_receive_package(recv_buffer,4096,&recv_len);  
        recv_buffer[recv_len] = '\0';
        if(recv_len!=0){
            if(send_port_array_flag==false&&recv_buffer[0]==0x0&&recv_buffer[1]==0xff){
                memset(recv_buffer,0,4096);
                UINT port_len=get_RT_sub_addr_array(port,(UINT *)(recv_buffer+4));
                *(UINT *)recv_buffer=port_len;
                if(vcan_send_package(recv_buffer,(port_len+1)*sizeof(int)) == -1)    
                    printf("发送RT端口子地址列表给RT失败\n");
                else{
                    printf("成功发送RT端口子地址列表给端口号为%d的RT\n",port);
                    send_port_array_flag=true;
                }
        }
        else{
            ctrl_unpack_package_to_1553(traffic_repos_id,port,recv_buffer,recv_len);
            memset(recv_buffer,0,recv_len);
            }
        }  
    }

#endif

}

void* scan_1553_RT_section_pthread_func(void* p_scan_config){
#ifdef PTHREAD_RECYCLE
    pthread_detach(pthread_self());
#endif
    //实现一个扫描算法
    scan_config* p_scan_config_tmp=(scan_config*)p_scan_config;
    UINT config_id=p_scan_config_tmp->config_id;
    int light_pos_tmp=-1;
    unsigned char* buffer=read_buf_1553[config_id];
    void* p_config_node_tmp=get_config_node(config_id);
    UINT repos_pos_tmp=get_config_node_traffic_repos_id(p_config_node_tmp);
    while(true){
        ctrl_pack_package_to_1553(repos_pos_tmp,buffer,\
                    &read_buf_1553_size[config_id],&light_pos_tmp);
        if(light_pos_tmp!=-1){
            void *p_sync=get_sync_collect(HASH_CONTROL_PACKAGE_SCAN_FLAG,\
                    config_id,light_pos_tmp,NULL);
            if(read_buf_1553_size[config_id]!=0){
                //light_pos 即为 RT_config_id
                //set_buffer_avail(config_id,light_pos_tmp);//死等
                vi_signal(p_sync);
            }
        }
    sleep_ms(30);
    }
}

void* bus_socket_pthread_func(void* p_socket_config){
#ifdef PTHREAD_RECYCLE
    pthread_detach(pthread_self());
#endif
   socket_config* p_socket_config_tmp=(socket_config*)p_socket_config;
   UINT config_id_tmp=p_socket_config_tmp->config_id;
   UINT RT_config_id_tmp=p_socket_config_tmp->RT_config_id;
   UINT port_tmp=p_socket_config_tmp->port;
   create_bus_socket_client(config_id_tmp,RT_config_id_tmp,port_tmp);
}

void* bus_ret_socket_pthread_func(void* p_socket_config){
#ifdef PTHREAD_RECYCLE
    pthread_detach(pthread_self());
#endif
   socket_config* p_socket_config_tmp=(socket_config*)p_socket_config;
   UINT config_id_tmp=p_socket_config_tmp->config_id;
   UINT port_tmp=p_socket_config_tmp->port;
   create_bus_socket_server(config_id_tmp,port_tmp);
}

void create_scan_1553_RT_section_unit(void* p_scan_config){
    pthread_t tid;
#ifdef __GCC_C99
    int err=pthread_create(&tid,NULL,scan_1553_RT_section_pthread_func,p_scan_config);
#elif __SPARC_GCC_MMU
    int err=pthread_create(&tid,NULL,(pthread_func_t)scan_1553_RT_section_pthread_func,p_scan_config);
#endif
    
    if(err!=0) printf("创建RT section描线程失败...\n");
    else printf("成功创建RT section扫描线程，该扫描线程每20ms打包一次数据...\n");
}



void create_1553_bus_unit(void* p_socket_config){
    pthread_t tid1;
    pthread_t tid2;
    UINT err1,err2;
    //printf("in create_1553_bus_unit\n");
#ifdef __GCC_C99
    err1=pthread_create(&tid1,NULL,bus_ret_socket_pthread_func,p_socket_config);
    err2=pthread_create(&tid2,NULL,bus_socket_pthread_func,p_socket_config);
#elif __SPARC_GCC_MMU
    err1=pthread_create(&tid1,NULL,(pthread_func_t)bus_ret_socket_pthread_func,p_socket_config);
    err2=pthread_create(&tid2,NULL,(pthread_func_t)bus_socket_pthread_func,p_socket_config);
#endif
    if(err1!=0||err2!=0)printf("启动1553模拟端口失败...\n");
    else printf("成功启动一个1553模拟端口...\n");
}

bool get_buffer_is_avail(UINT config_id,UINT RT_config_id){
    return is_read_buf_1553_avail[config_id][RT_config_id];
}

bool set_buffer_unavail(UINT config_id,UINT RT_config_id){
    is_read_buf_1553_avail[config_id][RT_config_id]=false;
}

bool set_buffer_avail(UINT config_id,UINT RT_config_id){
    is_read_buf_1553_avail[config_id][RT_config_id]=true;
}

UINT get_RT_addr_array(UINT * buf){
    int i=0;
    int count=0;
    UINT len=get_config_len();
    for(i=0;i<len;i++){
       void* p_config_node_tmp=get_config_node(i);
       UINT RT_num=get_config_node_len(p_config_node_tmp);
       int j=0;
       /*1553模拟器所需的部分*/
       for(j=0;j<RT_num;j++){
            UINT port_tmp=get_config_node_port(p_config_node_tmp,j);
            buf[count++]=port_tmp;
            //printf("%d ",port_tmp);
       }
    }
    //printf("\ncount:%d\n",count);
    return count;
}


void initialize_communicate(){
#ifdef __TCPIP_TRANSMIT
    //printf("in initialize_communicate\n");
    int    socket_fd, connect_fd;  
    struct sockaddr_in  servaddr;  
    unsigned char buffer[4096];  
    int recv_len;  
    if( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
    }  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//IP地址设置成INADDR_ANY,让系统自动获取本机的IP地址。  
    servaddr.sin_port = htons(7000);//
    if( bind(socket_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1){  
        printf("bus--bind socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
    }  
     if( listen(socket_fd, 10) == -1){  
        printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);  
        exit(0);  
    }  
    if( (connect_fd = accept(socket_fd, (struct sockaddr*)NULL, NULL)) == -1){  
        printf("accept socket error: %s(errno: %d)",strerror(errno),errno);  
    }
    printf("与RT端成功建立连接\n");
    recv_len = recv(connect_fd, buffer,MAXLINE, 0);  
    buffer[recv_len] = '\0';
    if(recv_len!=0){
        if(buffer[1]==0x0&&buffer[2]==0xff){
            //发送端口列表给RT
            memset(buffer,0,4096);
            UINT port_len=get_RT_addr_array((UINT *)(buffer+8));
            *(UINT *)(buffer+4)=port_len;
            *(UINT *)buffer=(port_len+1)*sizeof(int);
            //printf("%d %d",*(UINT *)(buffer),*(UINT *)(buffer+4));
            if(send(connect_fd,buffer,4096,0) == -1)  
                perror("发送RT端口列表给RT失败\n");
        }
        else{
            printf("初始化RT线程失败\n");
        }
        close(socket_fd);  
    }
    else {
        close(socket_fd);  
    }
#endif
}

void initialize_BC(){
    int i=0;
    UINT len=get_config_len();
    //printf("len:%d\n",len);
    for(i=0;i<len;i++){
       scan_config* p_scan_config_tmp=(scan_config*)malloc(sizeof(scan_config));
       p_scan_config_tmp->config_id=i;
       create_scan_1553_RT_section_unit(p_scan_config_tmp);
       void* p_config_node_tmp=get_config_node(i);
       UINT RT_num=get_config_node_len(p_config_node_tmp);
       UINT j=0;
       //printf("RT num:%d\n",RT_num);
       /*1553模拟器所需的部分*/
       for(;j<RT_num;j++){
           UINT port_tmp=get_config_node_port(p_config_node_tmp,j);
           socket_config* p_socket_config_tmp=(socket_config*)malloc(sizeof(socket_config));
           p_socket_config_tmp->config_id=get_config_node_traffic_repos_id(p_config_node_tmp);
           p_socket_config_tmp->RT_config_id=get_config_node_light_pos(p_config_node_tmp,j);
           p_socket_config_tmp->port=port_tmp;
           create_1553_bus_unit(p_socket_config_tmp);
       }
    }
    printf("等待与RT端建立连接\n");
#ifdef __TCPIP_TRANSMIT
    initialize_communicate();
#elif __VCAN_TRANSMIT

#endif
}

