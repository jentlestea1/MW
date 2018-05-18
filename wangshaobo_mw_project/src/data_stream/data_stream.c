#include "data_stream.h"
#include "route_map.h"
#include "address_map.h"
#include "handle_event.h"


void config_address_map_index_list(void){
    create_index_list();
}


void app_write_data_func(char* dev_lid,unsigned char* buffer,UINT write_size,UINT* size){
    if(write_size>WRITE_MAX_SIZE){
        route r;
        get_dev_route_map(dev_lid,&r);
        char* RT_lid=get_route_RT_lid(r);
        throw_event(0,RT_lid,EVT_APP_WRITE_BLOCK_OVERFLOW);//报错
        return;
    }
    UINT write_size_tmp=write_size>WRITE_MAX_SIZE?WRITE_MAX_SIZE:write_size;//抛出事件
    route r;
    get_dev_route_map(dev_lid,&r);
    void* data_node_array_tmp=get_data_node_array();
    UINT size_tmp;
    plugin_data_node_array(data_node_array_tmp,buffer,write_size,&size_tmp);
    app_write_data(get_route_bus_type(r),get_route_bus_lid(r),get_route_RT_lid(r),dev_lid,data_node_array_tmp,size_tmp,size);
    free_data_node_array(data_node_array_tmp);
}


void app_read_data_func(char* dev_lid,unsigned char* buffer,UINT read_size,UINT* size,void* time){
    UINT read_size_tmp=read_size>READ_MAX_SIZE?READ_MAX_SIZE:read_size;
    route r;
    get_dev_route_map(dev_lid,&r);
    void* data_node_array_tmp=get_data_node_array();
    app_read_data(get_route_bus_type(r),get_route_bus_lid(r),get_route_RT_lid(r),dev_lid,data_node_array_tmp,read_size_tmp,size);
    get_array_data_string(data_node_array_tmp,buffer,*size,size,time);
    free_data_node_array(data_node_array_tmp);
}


void dev_write_data_func(char* dev_lid,unsigned char* buffer,UINT write_size,UINT* size){
    if(write_size>WRITE_MAX_SIZE){
        route r;
        get_dev_route_map(dev_lid,&r);
        char* RT_lid=get_route_RT_lid(r);
        throw_event(0,RT_lid,EVT_1553_RETURN_DATA_ERR);//报错
    }
    UINT write_size_tmp=write_size>WRITE_MAX_SIZE?WRITE_MAX_SIZE:write_size;//抛出事件
    route r;
    get_dev_route_map(dev_lid,&r);
    void* data_node_array_tmp=get_data_node_array();
    UINT size_tmp;
    plugin_data_node_array(data_node_array_tmp,buffer,write_size,&size_tmp);
    dev_write_data(get_route_bus_type(r),get_route_bus_lid(r),get_route_RT_lid(r),dev_lid,data_node_array_tmp,size_tmp,size);
    free_data_node_array(data_node_array_tmp);
}


void dev_read_data_func(char* dev_lid,unsigned char* buffer,UINT read_size,UINT* size,void* time){
    UINT read_size_tmp=read_size>READ_MAX_SIZE?READ_MAX_SIZE:read_size;
    route r;
    get_dev_route_map(dev_lid,&r);
    void* data_node_array_tmp=get_data_node_array();
    dev_read_data(get_route_bus_type(r),get_route_bus_lid(r),get_route_RT_lid(r),dev_lid,data_node_array_tmp,read_size_tmp,size);
    get_array_data_string(data_node_array_tmp,buffer,*size,size,time);
    free_data_node_array(data_node_array_tmp);
}


