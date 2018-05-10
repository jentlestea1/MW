#include "compile_type.h"
#include "package.h"
#include "handle_data_package.h"
#include "control_data_stream.h"
#include "handle_event.h"
#include "control_traffic_light.h"
#include "route_map.h"
#include "string.h"
#include "stdio.h"

/*
 * 该函数负责将BC接到的数据解包然后调用数据流模块接口
 * 将数据写到对应转存区域 
 */
void unpack_package_to_1553(UINT traffic_repos_id,unsigned char* buffer,UINT buf_size,char* bus_type,char* bus_lid,char* RT_lid){
    //前4个字节为帧的大小
#ifdef __TCP_IP_TRANSMIT
    buffer+=PACKAGE_HEADER_SIZE_LEN;
#endif
    UINT cur_prio=0;
    UINT buffer_pos=0;
    UINT block_size=0;
    UINT size=0;
    UINT prev_priority=MAX_PRIORITY;
    UINT anchor=0;
    if(buf_size<=0)return;
    UINT light_pos=get_light_pos(traffic_repos_id,RT_lid);
    if(is_RT_section_writeable(traffic_repos_id,light_pos)==false){
        throw_event(0,RT_lid,EVT_1553_RETURN_DATA_ERR);
        return;//抛出异常
    }
    char* dev_lid=get_priority_deterio_dev_lid(bus_type,bus_lid,RT_lid,SEND_PRIORITY_FLAG,prev_priority,&cur_prio,&anchor);
    prev_priority=cur_prio;
    while(strcmp(dev_lid,"")!=0){
        UINT is_valid=*(buffer+buffer_pos)/DATA_BLOCK_VALID_PREFIX;
        if(is_valid==1){
            block_size=*(buffer+buffer_pos)%DATA_BLOCK_VALID_PREFIX;
            buffer_pos++;
            ctrl_dev_write_data(traffic_repos_id,dev_lid,buffer+buffer_pos,block_size,&size);
            if(size!=block_size){
                printf("write err!");
                return;
            }
            buffer_pos+=block_size;
        }
        else{
            buffer_pos++;
        }
        dev_lid=get_priority_deterio_dev_lid(bus_type,bus_lid,RT_lid,SEND_PRIORITY_FLAG,prev_priority,&cur_prio,&anchor);
        prev_priority=cur_prio;
    }
    if(buf_size!=buffer_pos+PACKAGE_HEADER_SIZE_LEN)printf("unpack to 1553有数据丢失\n");
}

/*
 *改函数将转存区域的数据打包给BC
 */
void pack_package_to_1553(UINT traffic_repos_id,UINT light_pos,char* bus_type,char* bus_lid,char* RT_lid,unsigned char* buffer_1553,UINT* buffer_size){
    UINT cur_prio=0;
    UINT block_size=0;
    UINT size=0;
    UINT buffer_pos=0;
    UINT prev_priority=MAX_PRIORITY;
    UINT anchor=0;
    bool is_send_valid=false;
    unsigned char read_buffer[READ_BUFFER_MAX_SIZE]={0};
    unsigned char buffer_tmp[READ_BUFFER_MAX_SIZE]={0};
    char* dev_lid=get_priority_deterio_dev_lid(bus_type,bus_lid,RT_lid,RECEIVE_PRIORITY_FLAG,prev_priority,&cur_prio,&anchor);
    prev_priority=cur_prio;
    if(strcmp(dev_lid,"")==0){
        *buffer_size=0;
        return;
    }
    while(strcmp(dev_lid,"")!=0){
        block_size=get_dev_trans_attr(bus_type,bus_lid,RT_lid,dev_lid,RECEIVE_BLOCK_FLAG);
        void* p_time_node=get_time_node();
        ctrl_dev_read_data(traffic_repos_id,dev_lid,read_buffer,block_size,&size,p_time_node);
        int j=0;
        if(size!=0&&block_size!=size){//抛出异常,应用层应该以一个block的大小发送指令/数据
            void* p_route=get_route_node();
            get_dev_route_map(dev_lid,&p_route);
            char* RT_lid=get_route_RT_lid(p_route);
            throw_event(0,RT_lid,EVT_APP_DATA_SIZE_ERR);
            free_route_node(&p_route);
        }
        if(size==0){
            *(buffer_tmp+buffer_pos)|=DATA_BLOCK_VALID_PREFIX;
            buffer_pos++;
        }
        else{
            is_send_valid=true;
            *(buffer_tmp+buffer_pos)=size;
            *(buffer_tmp+buffer_pos)|=DATA_BLOCK_VALID_PREFIX;
            buffer_pos++;
            memcpy(buffer_tmp+buffer_pos,read_buffer,size);
            buffer_pos=buffer_pos+size;
            memset(read_buffer,0,READ_BUFFER_MAX_SIZE);
        }
        dev_lid=get_priority_deterio_dev_lid(bus_type,bus_lid,RT_lid,RECEIVE_PRIORITY_FLAG,prev_priority,&cur_prio,&anchor);
        prev_priority=cur_prio;
        free_time_node(&p_time_node);
    }
    if(is_send_valid==true){
#ifdef __TCP_IP_TRANSMIT
        *(UINT *)buffer_1553=buffer_pos;
        buffer_pos+=PACKAGE_HEADER_SIZE_LEN;
        *buffer_size=buffer_pos;
        buffer_tmp[buffer_pos]='\0';
        strcpy(buffer_1553+PACKAGE_HEADER_SIZE_LEN,buffer_tmp);
#elif __VCAN_TRANSMIT
        *buffer_size=buffer_pos;
        buffer_tmp[buffer_pos]='\0';
        strcpy(buffer_1553,buffer_tmp);
#endif
        /*int i=0;
        for(i=0;i<buffer_pos;i++){
            printf("%d ",buffer_1553[i]);
        }
        printf("\n");
        */
    }
    else{
        *buffer_size=0;
    }
}
