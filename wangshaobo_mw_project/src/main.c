#include "manage_transport_center.h"
#include "app.h"
#include<time.h>
#include "file.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "my_RT_socket.h"
int main(){
    init_vi_dev_visit_sys();
    app_read();
    time_t t;
    srand((unsigned)time(&t));
    generate_data();
    while(1){
        //print_traffic_light();
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
