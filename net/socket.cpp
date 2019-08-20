#include "net/socket.h"

namespace hyper {
namespace net{
SOCKET Socket::getFd() const { 
    SOCKET fd = 0;
    return fd;
} 
bool Socket::getTcpInfo(struct tcp_info* info) const {
    return true;
}
void Socket::bindAddress(){}
void Socket::listen(){}
int  Socket::accept() {
    return 0;
}
void Socket::connect(){}
void Socket::shutdownWrite(){}
void Socket::setTcpNoDelay(bool on){}
void Socket::setReuseAddr(bool on){}
void Socket::setReusePort(bool on){}
void Socket::setKeepAlive(bool on){}
}
}