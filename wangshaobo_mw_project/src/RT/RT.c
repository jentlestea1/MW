#include "RT_socket.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "RT_socket.h"
#include "file.h"
int main(){
    initialize_RT();
    time_t t;
    srand((unsigned)time(&t));
    generate_data();
    while(1){
        usleep(1000000);
        if(is_end_t()==6){
            usleep(2000000);
            printf("\n数据传输结束，准备分析测试结果...\n\n");
            usleep(1000000);
            out_put();
            out_put();
            judge_result();
            return 0;
        }
    }
    
    return 0;
}