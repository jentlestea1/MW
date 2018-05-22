#include "sync_hash.h"
#include "m_type.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "handle_event.h"
#define MP2_CHAR_STR_MAX_LEN ATTR_LID_VALUE_MAX_LEN
#ifdef __SPARC_GCC_MMU
#include <fsu_pthread.h>
#elif __GCC_C99
#include <pthread.h>
#endif

struct mp1{
    UINT d1;
    UINT d2;
};
struct mp2{
    char s1[MP2_CHAR_STR_MAX_LEN];
};
struct hash_table table={{NULL}};
struct mp1 hash_key_map1[HASH_LIST_MAX_LEN]={{0,0}};
static UINT mp1_len=0;
struct mp2 hash_key_map2[HASH_LIST_MAX_LEN]={{0}};
static UINT mp2_len=0;
/*只会针对HASH_CONTROL_PACKAGE的输入取HASH_KEY*/
HASHKEY get_hash_key(HASH_TYPE hash_type,UINT d1,UINT d2,char *s1){
    static HASHKEY key=0;
    if(hash_type==HASH_CONTROL_PACKAGE_SCAN_FLAG){
        for(key=0;key<mp1_len;key++){
            if(hash_key_map1[key].d1==d1&&hash_key_map1[key].d2==d2)
                break;
        }
        if(key==mp1_len){
            hash_key_map1[key].d1=d1;
            hash_key_map1[key].d2=d2;
            mp1_len++;
        }
    }
    else if(hash_type==HASH_CONTROL_APP_READ_FLAG){
        if(strcmp(s1,"")==0||s1==NULL){
            throw_event(0,NULL,EVT_HASH_KEY_ERR);
        }
        for(key=0;key<mp2_len;key++){
            if(strcmp(s1,hash_key_map2[key].s1)==0)
                break;
        }
        if(key==mp2_len){
            strcpy(hash_key_map2[key].s1,s1);
            mp2_len++;
        }
    }
    return key;
}

UINT Hash(HASH_TYPE hash_type,HASHKEY key){
    //求出下标
    if(hash_type==HASH_CONTROL_TRAFFIC_SCAN_FLAG)
        return 1;
    else if(hash_type==HASH_CONTROL_UNDETERMINATE_FLAG)
        return 2;
    else if(hash_type==HASH_CONTROL_PACKAGE_SCAN_FLAG)
        return key%(HASH_LIST_MAX_LEN-50)+3; //(3~52)
    else if(hash_type==HASH_CONTROL_APP_READ_FLAG)
        return key%(HASH_LIST_MAX_LEN-30)+53; //(53~82)
    else 
        throw_event(0,NULL,EVT_HASH_TYPE_ERR);

}

void insert_hash_node(UINT pos,HASHKEY key,void *p){
    node *prev=NULL;
    if(table.node_head[pos]!=NULL){
        prev=table.node_head[pos];
        while(prev->next!=NULL){
            prev=prev->next;
        }
        node *a=(node *)malloc(sizeof(node));
        a->key=key;
        a->p_value=p;
        a->next=NULL;
        prev->next=a;
    }
    else{
        node *a=(node *)malloc(sizeof(node));
        a->key=key;
        a->p_value=p;
        a->next=NULL;
        table.node_head[pos]=a;
    }
}

void *get_hash_value(HASH_TYPE hash_type,UINT d1,UINT d2,char *s1){
    HASHKEY key=0;
    key=get_hash_key(hash_type,d1,d2,s1); 
    UINT pos=Hash(hash_type,key);
    node *prev=NULL;
    if(table.node_head[pos]!=NULL){
        prev=table.node_head[pos];
        while(prev!=NULL){
            if(prev->key==key){
                return prev->p_value;
            }
            prev=prev->next;
        }
    }
    return NULL;
}
