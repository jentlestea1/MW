#include "compile_type.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "RT_socket.h"
#include "pthread.h"
#include "m_type.h"
#define __RT_INCLUDE
#include "interval.h"
#include "file.h"
#include "relevant_struct_def.h"
#include "string.h"

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
    memset(&t,0,sizeof(timeStamp));
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
        printf("位置：RT，类型：发送；数据：%f；大小：%d；端口：%d    时间戳：%d:%d:%d\n",d,size,8001,((timeStamp*)&t)->hour,((timeStamp*)&t)->minute,((timeStamp*)&t)->second);
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
    memset(&t,0,sizeof(timeStamp));
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
        printf("位置：RT，类型：发送；数据：%f；大小：%d；端口：%d    时间戳：%d:%d:%d\n",d,size,8002,((timeStamp*)&t)->hour,((timeStamp*)&t)->minute,((timeStamp*)&t)->second);
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
    memset(&t,0,sizeof(timeStamp));
    while(cnt--){
        recv_buffer[0]=d;
        recv_buffer[1]='\0';
        time=m_random();
        sleep_ms(100*time);
        write_write_buffer(8004,recv_buffer,strlen(recv_buffer),&size);
        if(size!=1)printf("generate data err!\n");
        get_current_time(&t);
        printf("位置：RT，类型：发送；数据：%d；大小：%d；端口：%d    时间戳：%d:%d:%d\n",recv_buffer[0],size,8004,((timeStamp*)&t)->hour,((timeStamp*)&t)->minute,((timeStamp*)&t)->second);
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
    memset(&t,0,sizeof(timeStamp));
    while(cnt--){
        recv_buffer[0]=d;
        recv_buffer[1]='\0';
        time=m_random();
        sleep_ms(100*time);
        write_write_buffer(8005,recv_buffer,strlen(recv_buffer),&size);
        if(size!=1)printf("generate data err!\n");
        get_current_time(&t);
        printf("位置：RT，类型：发送；数据：%d；大小：%d；端口：%d    时间戳：%d:%d:%d\n",recv_buffer[0],size,8005,((timeStamp*)&t)->hour,((timeStamp*)&t)->minute,((timeStamp*)&t)->second);
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
    memset(&t,0,sizeof(timeStamp));
    while(cnt--){
        recv_buffer[0]=d;
        recv_buffer[1]='\0';
        time=m_random();
        sleep_ms(100*time);
        write_write_buffer(8006,recv_buffer,strlen(recv_buffer),&size);
        if(size!=1)printf("generate data err!\n");
        get_current_time(&t);
        printf("位置：RT，类型：发送；数据：%d；大小：%d；端口：%d    时间戳：%d:%d:%d\n",recv_buffer[0],size,8006,((timeStamp*)&t)->hour,((timeStamp*)&t)->minute,((timeStamp*)&t)->second);
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
    memset(&t,0,sizeof(timeStamp));
    while(cnt--){
        recv_buffer[0]=d;
        recv_buffer[1]='\0';
        time=m_random();
        sleep_ms(100*time);
        write_write_buffer(8007,recv_buffer,strlen(recv_buffer),&size);
        if(size!=1)printf("generate data err!\n");
        get_current_time(&t);
        printf("位置：RT，类型：发送；数据：%d；大小：%d；端口：%d    时间戳：%d:%d:%d\n",recv_buffer[0],size,8007,((timeStamp*)&t)->hour,((timeStamp*)&t)->minute,((timeStamp*)&t)->second);
        add_string(SEND,recv_buffer[0],8007);
        //d++;
    }
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

/*********************************************************
 *
 *generate_data_*函数模拟设备产生数据
 *
 *********************************************************/

int main(){
    initialize_RT();
    time_t t;
    srand((unsigned)time(&t));
    generate_data();
    while(1){
        if(is_end_t()==6){
            sleep_ms(5000);
            printf("\n数据传输结束，准备分析测试结果...\n\n");
            sleep_ms(1000);
            out_put();
            judge_result();
            return 0;
        }
    }
    return 0;
}
