#include "handle_event_func.h"
#include "route_map.h"
#include "event_type.h"
#include "event.h"
#include<stdio.h>

void handle_1553_func(void* p_event){
    char* sel_RT_lid_tmp=((evt*)p_event)->sel_RT_lid;
    route r;
    get_RT_route_map(sel_RT_lid_tmp,&r);
    printf("route:%s %s %s   event_type:%d",get_route_bus_type(r),get_route_bus_lid(r),get_route_RT_lid(r),((evt*)p_event)->event_type);
    if(((evt*)p_event)->event_type==EVT_1553_RECV_COMMAND){
        printf("  RECV_COMMAND_1553\n");
    }
    else if(((evt*)p_event)->event_type==EVT_1553_RECV_COMMAND_ERR){
        printf("  RECV_COMMAND_ERR_1553\n");        
    }
}

void handle_1553_ret_func(void* p_event){
    char* sel_RT_lid_tmp=((evt*)p_event)->sel_RT_lid;
    route r;
    get_RT_route_map(sel_RT_lid_tmp,&r);
    printf("route:%s %s %s   event_type:%d",get_route_bus_type(r),get_route_bus_lid(r),get_route_RT_lid(r),((evt*)p_event)->event_type);
    if(((evt*)p_event)->event_type==EVT_1553_RETURN_DATA){
        printf("  RETURN_DATA_1553\n");
    }
    else if(((evt*)p_event)->event_type==EVT_1553_RETURN_DATA_ERR){
        printf("  RETURN_DATA_ERR_1553\n");        
    }

}

void handle_RT_func(void* p_event){
    char* sel_RT_lid_tmp=((evt*)p_event)->sel_RT_lid;
    route r;
    get_RT_route_map(sel_RT_lid_tmp,&r);
    printf("route:%s %s %s   event_type:%d",get_route_bus_type(r),get_route_bus_lid(r),get_route_RT_lid(r),((evt*)p_event)->event_type);
    if(((evt*)p_event)->event_type==EVT_RT_RECV_DATA){
        printf("  RECV_DATA_RT\n");
    }
    else if(((evt*)p_event)->event_type==EVT_RT_RECV_DATA_ERR){
        printf("  RECV_DATA_ERR_RT\n");        
    }
}
