/*
 * 定义几个接受字符串的缓存,假设RT下最多可以挂载31个设备
 */
#ifndef RT_CONTROL_H_
#define RT_CONTROL_H_
#include "compile_type.h"
#include "m_type.h"
//#define RT_physical_addr 9000//具体再改
#define MOUNT_DEV_MAX_NUM 31
#define CACHE_MAX_SIZE 0x400 //1k
#define READ_MAX_SIZE_RT 0xff
#define RT_DATA_BLOCK_VALID_PREFIX (unsigned char)0x80
#ifdef __RT_TCPIP_TRANSMIT
#define RT_PACKAGE_HEADER_SIZE_LEN 0X4
#endif

void init_port_array(UINT *RT_sub_addr_array,UINT size);
void clear_write_buffer(void);
void write_write_buffer(UINT child_port,unsigned char* buffer,UINT write_size,UINT* size);
void read_write_buffer(UINT pos,unsigned char* buffer,UINT read_size,UINT* size);
void pack_package(unsigned char* buffer,UINT buffer_len,UINT* buffer_size);
void RT_handle_package(UCHAR *buffer,UINT n);
int get_child_port_pos(UINT child_port);
UINT get_child_port(int pos);
UINT get_child_port_array_len(void);
#endif
