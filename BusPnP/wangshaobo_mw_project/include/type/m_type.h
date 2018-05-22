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
#endif
