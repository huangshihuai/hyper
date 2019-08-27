#ifndef HYPER_INTERFACE_I_SOCKET_H
#define HYPER_INTERFACE_I_SOCKET_H
#include <string>
#include <memory>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include "base/btype.h"
#include "base/e_socket_model.h"

namespace hyper {
namespace interface {
using namespace hyper::base;

enum SocketState {
    NONE,
    CREATE,
    BIND,
    LISTEN,
    CONNECT,
};

class ISocket {
public:
    explicit ISocket() { };
    virtual ~ISocket() { };
    virtual SOCKET getFd() const = 0;
    virtual bool getTcpInfo(struct tcp_info* info) const = 0;
    virtual bool createSocket() = 0;
    virtual bool bindAddress() = 0;
    virtual bool listen(int32 backlog) = 0;
    virtual std::shared_ptr<ISocket>  accept() = 0;
    virtual bool connect() = 0;
    virtual void shutdown() = 0;
    virtual void shutdownRead() = 0;
    virtual void shutdownWrite() = 0;
    virtual void setTcpNoDelay(bool on) = 0;
    virtual void setReuseAddr(bool on) = 0;
    virtual void setReusePort(bool on) = 0;
    virtual void setKeepAlive(bool on) = 0;
    virtual void setPort(int32 port) = 0;
    virtual void setIp(const std::string &ip) = 0;
    virtual void setSocketModel(ESocketModel socketModel) = 0;
    virtual void setSocketFd(SOCKET fd) = 0;
    virtual SOCKET setSocketOptional(SOCKET fd)  = 0;
    virtual int32 read(std::string &data) = 0;
    virtual int32 write(const std::string &data) = 0;
};
}
}

#endif // HYPER_INTERFACE_I_SOCKET_H