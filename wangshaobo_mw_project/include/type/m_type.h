#ifndef M_TYPE_H_
#define M_TYPE_H_
#include "compile_type.h"
#define bool int
#define true 1
#define false 0
#ifndef NULL
#define NULL 0
#endif
#define USHORT unsigned short
#define UINT unsigned int
#define ULONG unsigned long
#define UCHAR unsigned char
#define ATTR_MAX_LEN 20
#define ATTR_VALUE_MAX_LEN 15
#define ATTR_LID_VALUE_MAX_LEN 15
#define ATTR_TYPE_VALUE_MAX_LEN 15
#define ATTR_INTERFACE_VALUE_MAX_LEN 15
#define RT_SUBADDR_VALUE_MAX_LEN 20
#define DEVICE_LIST_MAX_LEN 200
#define DEV_LID_MAX_LEN 32
#define SEND_PRIORITY_VALUE_MAX_LEN 10
#define SEND_BLOCK_VALUE_MAX_LEN 10
#define RECEIVE_PRIORITY_VALUE_MAX_LEN 10
#define RECEIVE_BLOCK_VALUE_MAX_LEN 10
#define TRAN_DATA_ITEM_MAX_LEN 5
#define INTERFACE_MAX_LEN 20
#define SEND_PRIORITY_POS 0
#define RECEIVE_PRIORITY_POS 1
#define SEND_BLOCK_POS 2
#define RECEIVE_BLOCK_POS 3
#ifdef __VCAN_TRANSMIT
#define htonl(x) (((x)<<24)&0xff000000)|(((x)<<8)&0x00ff0000)|\
    (((x)>>8)&0x0000ff00)|(((x)>>24)&0x000000ff)
#ifndef __RT_INCLUDE
#include "can_sys.h"
#endif
#define PACKAGE_HEADER (UINT)0xff0000ff
/*返回-1表示为数据帧，返回值>=0表示传输帧大小的控制帧*/
#define VCAN_DATA_FRAME_FLAG -1
#define VCAN_INIT_PORT_FRAME_FLAG -2
#define VCAN_SIZE_FRAME_FLAG 1
#define VCAN_INVALID_FRAME_FLAG -3

int frame_type_detect(struct can_frame frame,UCHAR* w_buf,UINT *size,int size_frame_mask); //默认一帧为8\
        位,size为有效位,w_buf为如果是 数据帧则填入w_buf,type_mask可以屏蔽SIZE类型,
struct can_frame serial_frame(int serial_type,UCHAR* r_buf,UINT size); //serial_type标示三种类型\
         size在DATA时为数据大小不超过8字节，在SIZE时需要传输字节大小,在INIT时只需要传入类型
void clear_frame_data(UCHAR* p);
#endif
#endif
