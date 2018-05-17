#include "compile_type.h"
#include "RT_socket.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "RT_socket.h"
#include "file.h"
#define __RT_INCLUDE
#include "interval.h"
#include "handle_event.h"

int main(){
    init_event_repos_array();
    UINT event_repos_id;
    get_one_event_repos(&event_repos_id);
    /*创建事件库扫描线程,事件库一个就够了*/
    create_evt_repos_scan_unit();
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
            //out_put();
            judge_result();
            return 0;
        }
    }
    return 0;
}
