#ifndef HYPER_BASE_E_SOCKET_MODEL_H
#define HYPER_BASE_E_SOCKET_MODEL_H
#include <sys/socket.h>

namespace hyper {
namespace base {
    
enum ESocketModel {
    TCP = SOCK_STREAM,
    UDP = SOCK_DGRAM,
};
}
}

#endif // HYPER_BASE_E_SOCKET_MODEL_H