#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include "compile_type.h"
#include "semaphore_hash.h"
#include "m_type.h"
#ifdef __SPARC_GCC_MMU
#include <fsu_pthread.h>
#elif __GCC_C99
#include <pthread.h>
#endif
#define FLAG UCHAR 
#define FLAG0 0  //FLAG0无意义
#define FLAG1 1   //FLAG1 2 3可自定义使用规则
#define FLAG2 2
#define FLAG3 3

typedef  HASH_TYPE SYNC_TYPE;

/*通过hash表获取存放pthread_con和pthread_mutex结构的指针,实体以链表存储*/
/**/

typedef struct sync_collection{
    UCHAR flag;                 //flag支持原子访问
    pthread_mutex_t flag_mutex;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
}sync_collection;
void *get_sync_collect(SYNC_TYPE type,UINT d1,UINT d2,char *s1);
FLAG get_sync_collect_flag(void *p,bool lock);
void write_sync_collect_flag(void *p,FLAG flag,bool lock);
void vi_signal(void *p);
void vi_wait(void *p);

#endif
