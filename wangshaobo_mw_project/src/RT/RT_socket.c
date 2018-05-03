#include "file.h"
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
#include "relevant_struct_def.h"
#include "RT_socket.h"
#include<pthread.h>

void* create_RT_socket_server(void* RT_port){
        port_con* p_RT_port=(port_con*)RT_port;
        UINT port=p_RT_port->port;
        UINT child_port;
        int    socket_fd, connect_fd;  
        struct sockaddr_in     servaddr;  
        unsigned char    buffer[4096];  
        unsigned char    ret_buff[4096];
        UINT ret_size;
        int     n;  
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
        if(n!=0&&n!=-1){

            /*解包过程*/
            unsigned char send_buffer[4096]={0};
            UINT size;
            UINT is_valid;
            UINT pos=0;
            UINT port_pos=0;
            while(pos<n){
                size=buffer[pos]%0x80;
                is_valid=buffer[pos]/0x80;
                if(is_valid==0){
                    if(size==0)pos++;
                    else pos+=size;
                    port_pos++;
                    continue;
                }
                if(size==0){
                    pos++;
                    port_pos++;
                    continue;
                }
                pos++;
                memcpy(send_buffer,buffer+pos,size);
                pos+=size;
                send_buffer[size]='\0';
                if(port_pos<get_child_port_array_len()){
                    child_port=get_child_port(port_pos);
                    port_pos++;
                }
                else{
                    printf("port_pos大小出错\n");
                }
                //printf("\n----------port为%d的RT捕获到数据：%s发送给child_port:%d端口------------\n",port,send_buffer,child_port);
                double d;
                /*测试用*/
                if(child_port==8003){
                    double d1=send_buffer[0];
                    double d2=send_buffer[1];
                    double d3=send_buffer[2];
                    d=d1+pow(0.1,d3)*d2;
                }
                else {
                    d=send_buffer[0];
                }
                printf("位置：RT；类型：->接收；数据：%lf；大小：%d；端口：%d    ",d,size,child_port);
                add_string(RECEIVE,d,child_port);
                void* p_time=get_time_node();
                get_current_time(p_time);
                print_time(p_time);
                free_time_node(&p_time);
                memset(send_buffer,0,4096);
            }
            if(pos!=n){
                printf("ERR:传输内容有误\n");
            }
            
        }
        close(connect_fd);  
    }  
    close(socket_fd);  

}

void create_RT_socket_client(char* buffer,UINT port){
    int    sockfd, recv_len;
    struct sockaddr_in    servaddr;  
    unsigned char recv_buffer[4096];
    UINT size;
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){  
    printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);  
    exit(0);  
    }  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(port); 
    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){  
    printf("connect error: %s(errno: %d)\n",strerror(errno),errno);  
    exit(0);  
    }  
    if( send(sockfd, buffer, strlen(buffer), 0) < 0)  
    {  
    printf("send msg error: %s(errno: %d)\n", strerror(errno), errno);  
    exit(0);  
    }  
    recv_len = recv(sockfd, recv_buffer,4096, 0);
    recv_buffer[recv_len]='\0';
    if(recv_len!=0){
        /*测试用*/
        //write_write_buffer(port,recv_buffer,recv_len,&size);
        //if(size!=recv_len){
        //    printf("ERR:写入RT buffer过程丢失数据\n");
        //}
    }
    close(sockfd);  
    return;
}

void* create_RT_ret_socket_client(void* RT_port){//以原port+1发
    usleep(500000);
    port_con* p_RT_port=(port_con*)RT_port;
    UINT port=p_RT_port->port+1;
    int    sockfd, n,recv_len;  
    unsigned char ret_buff[4096]={0};
    UINT ret_size;
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
    ret_buff[0]=0x0;
    ret_buff[1]=0xff;
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
    init_port_array((UINT *)(ret_buff+4),*(UINT *)ret_buff);
    close(sockfd);
    while(1){
    usleep(30000);
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){  
    printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);  
    exit(0);  
    }  
    //memset(&servaddr, 0, sizeof(servaddr));  
    //servaddr.sin_family = AF_INET;  
    //servaddr.sin_port = htons(port); 
    memset(ret_buff,0,4096);
    pack_package(ret_buff,4096,&ret_size);
    if(ret_size==0)
        continue;
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

void* get_one_port_con(){
    port_con* p=(port_con*)malloc(sizeof(port_con));
    return (void*)p;
}

void* generate_data_1(void* argc){
    printf("1号数据源即将产生数据\n");
    usleep(5000000);
    unsigned char recv_buffer[5];
    double d=20.005;
    int d1=20;
    int d2=5;
    int d3=3;
    recv_buffer[0]=d1;
    recv_buffer[1]=d2;
    recv_buffer[2]=d3;
    recv_buffer[3]='\0';
    UINT size;
    UINT time;
    UINT t=TIMES;
    while(t--){
        time=m_random();
        usleep(2000*time);
        write_write_buffer(8001,recv_buffer,strlen(recv_buffer),&size);
        if(size!=3)printf("generate data err!\n");
        void* p_time=get_time_node();
        get_current_time(p_time);
        printf("位置：RT，类型：发送；数据：%f；大小：%d；端口：%d    时间戳：%d/%d/%d\n",d,size,8001,((timeStamp*)p_time)->hour,((timeStamp*)p_time)->minute,((timeStamp*)p_time)->second);
        add_string(SEND,d,8001);
        free_time_node(&p_time);
    }
    set_is_end();
}

void* generate_data_2(void* argc){
    printf("2号数据源即将产生数据\n");
    usleep(5000000);
    unsigned char recv_buffer[5];
    double d=30.01;
    int d1=30;
    int d2=1;
    int d3=2;
    recv_buffer[0]=d1;
    recv_buffer[1]=d2;
    recv_buffer[2]=d3;
    recv_buffer[3]='\0';
    UINT size;
    UINT time;
    UINT t=TIMES;
    while(t--){
        time=m_random();
        usleep(2000*time);
        write_write_buffer(8002,recv_buffer,strlen(recv_buffer),&size);
        if(size!=3)printf("generate data err!\n");
        void* p_time=get_time_node();
        get_current_time(p_time);
        printf("位置：RT，类型：发送；数据：%f；大小：%d；端口：%d    时间戳：%d/%d/%d\n",d,size,8002,((timeStamp*)p_time)->hour,((timeStamp*)p_time)->minute,((timeStamp*)p_time)->second);
        add_string(SEND,d,8002);
        free_time_node(&p_time);
    }
    set_is_end();
}

void* generate_data_4(void* argc){
    printf("4号数据源即将产生数据\n");
    usleep(5000000);
    unsigned char recv_buffer[5];
    recv_buffer[0]=4;
    recv_buffer[1]='\0';
    UINT size;
    UINT time;
    UINT t=TIMES;
    while(t--){
        time=m_random();
        usleep(2000*time);
        write_write_buffer(8004,recv_buffer,strlen(recv_buffer),&size);
        if(size!=1)printf("generate data err!\n");
        void* p_time=get_time_node();
        get_current_time(p_time);
        printf("位置：RT，类型：发送；数据：%d；大小：%d；端口：%d    时间戳：%d/%d/%d\n",recv_buffer[0],size,8004,((timeStamp*)p_time)->hour,((timeStamp*)p_time)->minute,((timeStamp*)p_time)->second);
        add_string(SEND,recv_buffer[0],8004);
        free_time_node(&p_time);
    }
    set_is_end();
}

void* generate_data_5(void* argc){
    printf("5号数据源即将产生数据\n");
    usleep(5000000);
    unsigned char recv_buffer[5];
    recv_buffer[0]=5;
    recv_buffer[1]='\0';
    UINT size;
    UINT time;
    UINT t=TIMES;
    while(t--){
        time=m_random();
        usleep(2000*time);
        write_write_buffer(8005,recv_buffer,strlen(recv_buffer),&size);
        if(size!=1)printf("generate data err!\n");
        void* p_time=get_time_node();
        get_current_time(p_time);
        printf("位置：RT，类型：发送；数据：%d；大小：%d；端口：%d    时间戳：%d/%d/%d\n",recv_buffer[0],size,8005,((timeStamp*)p_time)->hour,((timeStamp*)p_time)->minute,((timeStamp*)p_time)->second);
        add_string(SEND,recv_buffer[0],8005);
        free_time_node(&p_time);
    }
    set_is_end();
}

void* generate_data_6(void* argc){
    printf("6号数据源即将产生数据\n");
    usleep(5000000);
    unsigned char recv_buffer[5];
    recv_buffer[0]=6;
    recv_buffer[1]='\0';
    UINT size;
    UINT time;
    UINT t=TIMES;
    while(t--){
        time=m_random();
        usleep(2000*time);
        write_write_buffer(8006,recv_buffer,strlen(recv_buffer),&size);
        if(size!=1)printf("generate data err!\n");
        void* p_time=get_time_node();
        get_current_time(p_time);
        printf("位置：RT，类型：发送；数据：%d；大小：%d；端口：%d    时间戳：%d/%d/%d\n",recv_buffer[0],size,8006,((timeStamp*)p_time)->hour,((timeStamp*)p_time)->minute,((timeStamp*)p_time)->second);
        add_string(SEND,recv_buffer[0],8006);
        free_time_node(&p_time);
    }
    set_is_end();
}

void* generate_data_7(void* argc){
    printf("7号数据源即将产生数据\n");
    usleep(5000000);
    unsigned char recv_buffer[5];
    recv_buffer[0]=7;
    recv_buffer[1]='\0';
    UINT size;
    UINT time;
    UINT t=TIMES;
    while(t--){
        time=m_random();
        usleep(2000*time);
        write_write_buffer(8007,recv_buffer,strlen(recv_buffer),&size);
        if(size!=1)printf("generate data err!\n");
        void* p_time=get_time_node();
        get_current_time(p_time);
        printf("位置：RT，类型：发送；数据：%d；大小：%d；端口：%d    时间戳：%d/%d/%d\n",recv_buffer[0],size,8007,((timeStamp*)p_time)->hour,((timeStamp*)p_time)->minute,((timeStamp*)p_time)->second);
        add_string(SEND,recv_buffer[0],8007);
        free_time_node(&p_time);
    }
    set_is_end();
}

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
    //socket_config* p_socket_config_tmp=(socket_config*)p_socket_config;
    //UINT port_tmp=p_socket_config_tmp->port;
    pthread_t tid;
    //void* p_RT_con=get_one_port_con();
    //set_RT_port(p_RT_con,port_tmp);
    int err=pthread_create(&tid,NULL,create_RT_socket_server,p_RT_config);
    if(err!=0)printf("RT 收端创建线程失败...\n");
}

void* RT_ret_socket_pthread_func(void* p_RT_config){
    //socket_config* p_socket_config_tmp=(socket_config*)p_socket_config;
    //UINT port_tmp=p_socket_config_tmp->port;
    //if(port_tmp!=9000)return NULL;//9000测试用
    pthread_t tid;
    //void* p_RT_con=get_one_port_con();
    //set_RT_port(p_RT_con,port_tmp);
    int err=pthread_create(&tid,NULL,create_RT_ret_socket_client,p_RT_config);
    if(err!=0)printf("RT 发端创建线程失败...\n");
}

void create_RT_unit(void* p_RT_config){
    pthread_t tid1;
    pthread_t tid2;
    UINT err1,err2=0;
    err1=pthread_create(&tid1,NULL,RT_socket_pthread_func,p_RT_config);
    err2=pthread_create(&tid2,NULL,RT_ret_socket_pthread_func,p_RT_config);
    if(err1!=0||err2!=0)printf("创建RT模拟端口失败...\n");
    else printf("成功启动一个RT模拟端口,端口号:%d...\n",((port_con*)p_RT_config)->port);
}

void initialize_RT(void){

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
    buff[0]=0x0;
    buff[1]=0xff;
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
    UINT port_len=*(UINT *)buff;
    UINT *p=(UINT *)(buff+4);
    for(i=0;i<port_len;i++){
        void* p_RT_config=get_one_port_con();
        set_RT_port(p_RT_config,*p);
        create_RT_unit(p_RT_config);
    }
    close(sockfd);
}
