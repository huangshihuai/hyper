#pragma once

#include <sys/socket.h>

namespace hyper {
namespace base {
    
enum ESocketType {
    TCP = SOCK_STREAM,
    UDP = SOCK_DGRAM,
};
}
}