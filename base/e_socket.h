#pragma once

#include <sys/socket.h>

namespace hyper {
namespace base {

#define SOCKET_CLOSE -1
    
enum ESocketType {
    TCP = SOCK_STREAM,
    UDP = SOCK_DGRAM,
};

enum ESocketDomain {
    IPV4 = AF_INET,
    IPV6 = AF_INET6,
};

}
}