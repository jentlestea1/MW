#define __RT_INCLUDE
#include "compile_type.h"
#include "handle_event.h"
#include "unistd.h"
#include "relevant_struct_def.h"
#include<stdlib.h>
#include<pthread.h>
#include<stdio.h>
#include "route_map.h"
#include "interval.h"

static void* p_repos_array[REPOS_MAX_LEN];
static UINT is_repos_avail[REPOS_MAX_LEN]={0};

void init_event_repos_array(){
    printf("初始化事件库仓库...\n");
    int i=0;
    for(;i<REPOS_MAX_LEN;i++){
        if(p_repos_array[i]!=NULL){
            free(p_repos_array[i]);
        }
        void* p_repos_tmp=create_evt_repos();
        p_repos_array[i]=p_repos_tmp;
        is_repos_avail[i]=1;
    }
    printf("初始化事件库仓库结束...\n");
}

void get_one_event_repos(UINT* pos){
    int i=0;
    for(;i<REPOS_MAX_LEN;i++){
        if(is_repos_avail[i]==1){
            is_repos_avail[i]=0;
            *pos=i;
            printf("获取编号为%d的事件库...\n",i);
            return;
        }
    }
}

bool get_one_event(void* p_repos,void* p_evt_node){
    evt_repository* p_evt_repos_tmp=(evt_repository*)p_repos;
    void* p_evt_node_tmp=(evt*)p_evt_node;
    bool is_get_true=get_event_node(p_repos,p_evt_node_tmp);
    return is_get_true;
}

void handle_event(void* p_event){
    if(p_event==NULL)return;
    else{
        char* sel_RT_lid_tmp=((evt*)p_event)->sel_RT_lid;
        if(sel_RT_lid_tmp!=NULL){
            printf("RT_lid:%s   event_type:%d\n",sel_RT_lid_tmp,((evt*)p_event)->event_type);
        }
        else{
            printf("RT_lid:   event_type:%d\n",((evt*)p_event)->event_type);
        }
    }
}

void* get_evt_repos(UINT pos){
    return (void*)p_repos_array[pos];
}

void* evt_repos_scan_pthread_func(void* argc){
    UINT i=0;
    UINT pos=-1;
    for(;i<REPOS_MAX_LEN;i++){
        if(is_repos_avail[i]==0){//已经被注册
            pos=i;
            break;
        }
    }
    if(pos!=-1){
        while(true){
            void* p_repos=get_evt_repos(i);
            void* p_evt_node=(void*)((evt*)malloc(sizeof(evt)));
            bool is_true=get_one_event(p_repos,p_evt_node);
            if(is_true==true){
                handle_event(p_evt_node);
            }
            sleep_ms(1000);
            free(p_evt_node);
        }
    }
}

void create_evt_repos_scan_unit(void){
    pthread_t tid;
    pthread_create(&tid,NULL,evt_repos_scan_pthread_func,NULL);
    printf("成功创建事件库扫描线程...\n");
}

void throw_event(UINT repos_id,char* RT_lid,EVT_TYPE event_type){
    bool is_throw_succeed=false;
    void* p_repos_tmp=get_evt_repos(repos_id);
    if(p_repos_tmp==NULL)return;
    printf("repos_id:%d RT_lid:%s\n",repos_id,RT_lid);
    is_throw_succeed=append_event_node(p_repos_tmp,RT_lid,event_type);
    if(is_throw_succeed==false){
        printf("throw event error\n");
    }
}


