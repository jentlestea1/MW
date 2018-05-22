#ifndef VCAN_FRAME_H
#define VCAN_FRAME_H
#ifdef __VCAN_TRANSMIT
#include "m_type.h"
#define htonl(x) ( (( (x) & 0x000000ff)<<24)|(( (x) & 0x0000ff00)<<8)|\
    (( (x) & 0x00ff0000)>>8)|(( (x) & 0xff000000)>>24) )
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
