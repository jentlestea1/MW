#include "sync_collect.h"
#include "stdlib.h"
#include "stdio.h"
#include "handle_event.h"

FLAG get_sync_collect_flag(void *p,bool lock){
    if(p==NULL){
        throw_event(0,NULL,EVT_GET_SYNC_FLAG_ERR);
        return FLAG0;
    }
    FLAG flag;
    sync_collection *p_tmp=(sync_collection *)p;
    if(lock==true){
        pthread_mutex_lock(&(p_tmp->flag_mutex));
        flag=p_tmp->flag;
        pthread_mutex_unlock(&(p_tmp->flag_mutex));
    }
    else if(lock==false){
        flag=p_tmp->flag;
    }
    return flag;
}

void write_sync_collect_flag(void *p,FLAG flag,bool lock){
    if(p==NULL){
        throw_event(0,NULL,EVT_WRITE_SYNC_FLAG_ERR);
        return;
    }
    sync_collection *p_tmp=(sync_collection *)p;
    if(lock==true){
        pthread_mutex_lock(&(p_tmp->flag_mutex));
        p_tmp->flag=flag;
        pthread_mutex_unlock(&(p_tmp->flag_mutex));
    }
    else if(lock==false){
        p_tmp->flag=flag;
    }
}

void *get_sync_collect(SYNC_TYPE type,UINT d1,UINT d2,char *s1){    
    void *p=get_hash_value(type,d1,d2,s1);
    if(p==NULL){
       sync_collection *sync=(sync_collection *)malloc(sizeof(sync_collection));
//#ifdef __GCC_C99
       //pthread_mutex_t flag_mutex= PTHREAD_MUTEX_INITIALIZER;
       //pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;
       //pthread_cond_t cond= PTHREAD_COND_INITIALIZER;
       //sync->cond = cond;
       //sync->flag_mutex = flag_mutex;
       //sync->mutex = mutex;
//#elif __SPARC_GCC_MMU
       pthread_mutex_init(&(sync->flag_mutex),NULL);
       pthread_mutex_init(&(sync->mutex),NULL);
       pthread_cond_init(&(sync->cond),NULL);
//#endif
       sync->flag=FLAG1;
       p=sync;
       HASHKEY key= get_hash_key(type,d1,d2,s1);
       UINT pos = Hash(type,key);
       insert_hash_node(pos,key,p);
    } 
    return p;
}
void vi_signal(void *p){
    if(p==NULL){
        throw_event(0,NULL,EVT_VI_SIGNAL_ERR);
        //printf("传入的sync为空\n");
        return;
    }
    sync_collection *p_tmp=(sync_collection *)p;
    pthread_mutex_lock(&(p_tmp->mutex));
    pthread_cond_signal(&(p_tmp->cond));
    pthread_mutex_unlock(&(p_tmp->mutex));
    
}
void vi_wait(void *p){
    if(p==NULL){
        throw_event(0,NULL,EVT_VI_WAIT_ERR);
        //printf("传入的sync为空\n");
        return;
    }
    sync_collection *p_tmp=(sync_collection *)p;
    pthread_mutex_lock(&(p_tmp->mutex));
    pthread_cond_wait(&(p_tmp->cond),&(p_tmp->mutex));
    pthread_mutex_unlock(&(p_tmp->mutex));

}
