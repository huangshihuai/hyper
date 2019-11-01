#pragma once

#include <string>
#include <memory>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include "base/btype.h"
#include "base/e_socket.h"
#include "interface/i_socket_option.h"

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

/* Bits in the FLAGS argument to `send', `recv', et al.  */
enum {
    MSG_HYPER = 0x0,
#define MSG_HYPER MSG_HYPER
};

class ISocket {
public:
    explicit ISocket() { };
    virtual ~ISocket() { };
    virtual SOCKET getFd() const = 0;
    virtual bool getTcpInfo(struct tcp_info* info) const = 0;
    virtual bool create() = 0;
    virtual bool bindAddress() = 0;
    virtual bool listen(int32 backlog) = 0;
    virtual std::shared_ptr<ISocket>  accept() = 0;
    virtual bool connect() = 0;
    virtual void close() = 0;
    virtual void shutdown() = 0;
    virtual void shutdownRead() = 0;
    virtual void shutdownWrite() = 0;
    virtual void setPort(int32 port) = 0;
    virtual void setIp(const std::string &ip) = 0;
    //virtual void setSocketFd(SOCKET fd) = 0;
    virtual void setSocketOption(std::shared_ptr<ISocketOption> socketOption) = 0;
    virtual void setSocketFlags()  = 0;
    virtual int32 read(std::string &data) = 0;
    virtual int32 write(const std::string &data) = 0;
};
}
}
