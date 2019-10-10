#pragma once
#include <string>
#include "base/btype.h"
#include "base/e_socket_type.h"

namespace hyper {
namespace interface {

using namespace hyper::base;

class ISocketOption {
public:
    ISocketOption() {}
    virtual ~ISocketOption() {}
    virtual void setSocketType(ESocketType socketType) = 0;
    virtual void setTcpNoDelay(bool on) = 0;
    virtual void setReuseAddr(bool on) = 0;
    virtual void setReusePort(bool on) = 0;
    virtual void setKeepAlive(bool on) = 0;
    virtual void setFast(bool on) = 0;
    virtual void setNonBlock(bool on) = 0;

    virtual ESocketType getSocketType() const = 0;
    virtual bool getTcpNoDelay() const = 0;
    virtual bool getReuseAddr() const = 0;
    virtual bool getReusePort() const = 0;
    virtual bool getKeepAlive() const = 0;
    virtual bool getFast() const = 0;
    virtual bool getNonBlock() const = 0;
};
}
}