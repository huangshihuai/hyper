#ifndef HYPER_INTERFACE_I_SOCKET_H
#define HYPER_INTERFACE_I_SOCKET_H
#include <netinet/in.h>
#include <netinet/tcp.h>
#include "base/btype.h"

namespace hyper {
namespace interface {
using namespace hyper::base;

class ISocket {
public:
    explicit ISocket(SOCKET socketFd) : m_socketFd(socketFd) { };
    virtual ~ISocket() { };
    virtual SOCKET getFd() const = 0;
    virtual bool getTcpInfo(struct tcp_info* info) const = 0;
    virtual void bindAddress() = 0;
    virtual void listen() = 0;
    virtual int  accept() = 0;
    virtual void connect() = 0;
    virtual void shutdownWrite() = 0;
    virtual void setTcpNoDelay(bool on) = 0;
    virtual void setReuseAddr(bool on) = 0;
    virtual void setReusePort(bool on) = 0;
    virtual void setKeepAlive(bool on) = 0;
private:
    const SOCKET m_socketFd;
};
}
}

#endif // HYPER_INTERFACE_I_SOCKET_H