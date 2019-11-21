#pragma once

#ifdef __linux
#include <sys/types.h>
#include <sys/socket.h>
#include <cstddef>
#endif // linux

namespace hyper {
namespace base {

#ifdef __linux // must Linux Platform
    typedef	u_int64_t	        uint64;
    typedef	u_int32_t	        uint32;
    typedef	u_int16_t       	uint16;
    typedef	u_int8_t	        uint8;

    typedef	int64_t		        int64;
    typedef	int32_t		        int32;
    typedef	int16_t		        int16;
    typedef	int8_t		        int8;

    typedef	int	                SOCKET;
    typedef int                 poll_t;
#else
    typedef unsigned long long  uint64;
    typedef unsigned int        uint32;
    typedef unsigned short int  uint16;
    typedef unsigned char       uint8;

    typedef long long           int64;
    typedef int                 int32;
    typedef short int           int16;
    typedef char                int8;
    
    typedef unsigned long       ulong;
    typedef	int	                SOCKET;
    typedef int                 EPOLL;
#endif
}
}