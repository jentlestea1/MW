#ifndef RELEVANT_STRUCT_DEF_H_
#define RELEVANT_STRUCT_DEF_H_
#include "m_type.h"
#define CACHE_MAX_LEN 0x400
#define DATA_NODE_ARRY_MAX_LEN 
typedef struct timeStamp{
    //UINT year;
    //UINT month;
    //UINT day;
    UCHAR hour;
    UCHAR minute;
    UCHAR second;
}timeStamp;
typedef struct dataNode{
    timeStamp time;    //存的是指针
    unsigned char dataPiece;
}dataNode;
void plugin_data_node_array(void* data_node_array,unsigned char* buf,UINT buf_size,UINT* size);
void* get_data_node_array(void);
void free_data_node_array(void* p_data_node_array);
void get_array_data_string(void* data_node_array,unsigned char* buf,UINT read_size,UINT* size,void* time);
void insert_node_to_data_node_array(void* dest_array,UINT pos,void* src_data_node);
void get_current_time(timeStamp* time_stamp);
void clear_data_node_array(void* p_data_node_array,UINT array_size);
void delay(UINT m_s);
void print_time(timeStamp* time_stamp);
#endif
