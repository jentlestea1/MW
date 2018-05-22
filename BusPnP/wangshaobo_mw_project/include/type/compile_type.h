#ifndef COMPILE_TYPE_H
#define COMPILE_TYPE_H

#ifdef SOCKET_PROTOCOL

#define __GCC_C99 1
#define __TCPIP_TRANSMIT 2
#define __RT_TCPIP_TRANSMIT 3

#elif VCAN_PROTOCOL

#define __SPARC_GCC_MMU 1
#define __VCAN_TRANSMIT 2
#define __RT_VCAN_TRANSMIT 3

#endif

#endif
