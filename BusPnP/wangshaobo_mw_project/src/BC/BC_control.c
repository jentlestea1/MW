#include "BC_control.h"
#include "relevant_struct_def.h"
#include "handle_data_package.h"
#include "config_1553.h"
#include "route_map.h"
#include "stdio.h"
#include "string.h"
#define BC_DEVICE_NUM 1

UINT get_RT_sub_addr_array(UINT port,UINT *buf){
    
    /*
     * 根据RT_physical_addr找到RT_lid
     *依次按优先级找到其下的dev_lid,
     *再把每个dev相应的subaddr放到
     *child_port_array中
     */

    printf("正在为地址为%d的RT分配子地址...\n",port);
    UINT len=0;
    UINT config_1553_id=get_device_num_1553_bus_config_id(BC_DEVICE_NUM);
    if(config_1553_id==-1)return 0;
    void* p_confgi_node=get_config_node(config_1553_id);
    UINT pos=get_config_light_pos(config_1553_id,port);
    char* RT_lid=get_config_node_RT_lid(p_confgi_node,pos);
    route r;
    get_RT_route_map(RT_lid,&r);
    UINT cur_prio=0;
    UINT prev_priority=MAX_PRIORITY; 
    UINT anchor=0;
    UINT child_port;
    char* dev_lid=get_priority_deterio_dev_lid(get_route_bus_type(r),get_route_bus_lid(r),get_route_RT_lid(r),SEND_PRIORITY_FLAG,prev_priority,&cur_prio,&anchor);
    prev_priority=cur_prio;
    while(strcmp(dev_lid,"")!=0){
        child_port=get_RT_physical_sub_addr(get_route_bus_type(r),get_route_bus_lid(r),get_route_RT_lid(r),dev_lid);
        buf[len++]=child_port;
        dev_lid=get_priority_deterio_dev_lid(get_route_bus_type(r),get_route_bus_lid(r),get_route_RT_lid(r),SEND_PRIORITY_FLAG,prev_priority,&cur_prio,&anchor);
        prev_priority=cur_prio;
    }
    int i=0;
    for(;i<len;i++){
        printf("port:%d ",buf[i]);
    }
    return len;
}
