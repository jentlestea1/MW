#ifndef SEMAPHORE_HASH_H
#define SEMAPHORE_HASH_H
#include "compile_type.h"
#include "m_type.h"
#define HASHKEY UINT
#define MAX_HASH_KEY 1000
#define HASH_LIST_MAX_LEN 100  //0号不用,1号和2号占用


/*用于获取控制数据转存的sync_collection的flag*/
/*待定flag*/
typedef enum{HASH_CONTROL_TRAFFIC_SCAN_FLAG=0x1,HASH_CONTROL_PACKAGE_SCAN_FLAG=0x2,\
HASH_CONTROL_UNDETERMINATE_FLAG=0x3,HASH_CONTROL_APP_READ_FLAG=0x4}HASH_TYPE;

typedef struct node{
    HASHKEY key;
    void *p_value;
    struct node *next;
}node;
typedef struct hash_table{
    node *node_head[HASH_LIST_MAX_LEN];
}hash_table;


HASHKEY get_hash_key(HASH_TYPE hash_type,UINT d1,UINT d2,char *s1);
UINT Hash(HASH_TYPE hash_type,HASHKEY key);
void insert_hash_node(UINT pos,HASHKEY key,void *p);
void *get_hash_value(HASH_TYPE hash_type,UINT d1,UINT d2,char *s1);
#endif

