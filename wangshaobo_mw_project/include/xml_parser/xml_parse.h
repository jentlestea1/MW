/*
 * xml_parse.h,声明配置文件解析存储结构以及各种操作函数。
 */
#ifndef MXML_H_
#define MXML_H_ 
#include "m_type.h"
#include "mxml.h"
typedef struct RTTransaction{
    UINT len;
    char dev_lid[DEV_LID_MAX_LEN][ATTR_LID_VALUE_MAX_LEN];
    char dev_map_subAddr[DEV_LID_MAX_LEN][RT_SUBADDR_VALUE_MAX_LEN];
    union info{
        char send_priority[DEV_LID_MAX_LEN][SEND_PRIORITY_VALUE_MAX_LEN];
        char receive_priority[DEV_LID_MAX_LEN][RECEIVE_PRIORITY_VALUE_MAX_LEN];
        char send_block_size[DEV_LID_MAX_LEN][SEND_BLOCK_VALUE_MAX_LEN];
        char receive_block_size[DEV_LID_MAX_LEN][RECEIVE_BLOCK_VALUE_MAX_LEN];
    }info[TRAN_DATA_ITEM_MAX_LEN];
}RTTransaction;
typedef struct attr{
    char attr_name[ATTR_MAX_LEN][ATTR_VALUE_MAX_LEN];
    char attr_value[ATTR_MAX_LEN][ATTR_VALUE_MAX_LEN];
}attribute;
typedef struct dev_description{
    char lid[ATTR_LID_VALUE_MAX_LEN];
    char type[ATTR_TYPE_VALUE_MAX_LEN];
    char interface[ATTR_INTERFACE_VALUE_MAX_LEN];
    UINT attr_len;
    attribute attrs;
}dev_descrip;
typedef union io_attributes{
    attribute attrs;
    RTTransaction RTTrans;
}io_attributes;
typedef struct io_description{
    char lid[ATTR_LID_VALUE_MAX_LEN];
    char type[ATTR_TYPE_VALUE_MAX_LEN];
    UINT io_attr_len;
    io_attributes io_attrs;
}io_descrip;
typedef struct IONode{
	UINT IO_id;
	io_descrip descrip;
	struct IONode* next;
}IONode;
typedef struct DeviceNode{
	UINT device_id;
	dev_descrip descrip;
	struct IONode* next;
}DeviceNode;
void parseXml(void);
char* getInterface(const char* dev_content,UINT dev_content_len);
mxml_node_t* findDependedNode(const char* content,UINT content_len,mxml_node_t* root,bool isConfig);
void printList();
void* get_devices_descrip_item(void);
UINT get_devices_descrip_item_num(void);
char* get_device_lid(void* descrip);
char* get_device_type(void* descrip);
char* get_device_interface(void* descrip);
///
void* get_devices_list_item(void);
void* get_device_list_item(UINT pos);
UINT get_device_list_item_num(void);
UINT get_device_attr_len(void* dev_item);
char* get_device_attrs_name(void* dev_item);
char* get_device_attrs_value(void* dev_item);
char* get_device_data_size(void* dev_item);
char* get_device_item_lid(void* dev_item);
char* get_device_item_type(void* dev_item);
void* get_device_io_item(void* dev_item);
void* get_io_lid(void* io_item);
char* get_io_type(void* io_item);
UINT get_io_attr_len(void* io_item);//
char* get_io_attrs_name(void* io_tem);
char* get_io_attrs_value(void* io_item);
UINT get_RT_trans_device_num(void* io_item);//
char* get_RT_trans_devices_lid(void* io_item);
char* get_io_attrs_name(void* io_item);
char* get_io_attrs_value(void* io_item);
char* get_RT_trans_device_send_priority(char* dev_lid,void* io_item);
char* get_RT_trans_device_send_block_size(char* dev_lid,void* io_item);
char* get_RT_trans_device_receive_priority(char* dev_lid,void* io_item);
char* get_RT_trans_device_receive_block_size(char* dev_lid,void* io_item);
void* get_io_next_item(void* io_item);
char* get_RT_trans_device_map_subAddr(char*dev_lid,void* io_item);

//提供接口free申请的中间节点，因为后面不需要再使用
void free_device_list();
#endif

