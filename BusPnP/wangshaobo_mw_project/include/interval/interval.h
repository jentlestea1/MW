#ifndef INTERVAL_H
#define INTERVAL_H
#include "compile_type.h"
#include "m_type.h"
#ifndef __RT_INCLUDE
#ifdef __SPARC_GCC_MMU
#include <time.h>
#include <fsu_pthread.h>
#elif __GCC_C99
#include "unistd.h"
#endif
#else
#include "unistd.h"
#endif

#define msec_t UINT

/*统一使用自定义的sleep_ms*/

static inline int sleep_ms(msec_t msec){
#ifdef __SPARC_GCC_MMU
    struct timespec tv;
    UINT sec=msec/1000;
    ULONG nsec=(msec%1000)*1000000;
    tv.tv_sec=sec;
    tv.tv_nsec=nsec;
    return nanosleep(&tv,NULL);
#elif __GCC_C99
    ULONG usec=msec*1000;
    return usleep(usec);
#endif
}

#endif
