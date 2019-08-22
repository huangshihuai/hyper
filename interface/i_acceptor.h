#ifndef HYPER_INTERFACE_I_ACCEPTOR_H
#define HYPER_INTERFACE_I_ACCEPTOR_H
#include "base/btype.h"
#include "interface/i_event_loop.h"

namespace hyper {
namespace interface {

using namespace hyper::base;

class IAcceptor {
public:
    IAcceptor() { };
    virtual ~IAcceptor() { };
    virtual void init() = 0;
    virtual void setTcpNoDelay(bool on) = 0;
    virtual void setReuseAddr(bool on) = 0;
    virtual void setReusePort(bool on) = 0;
    virtual void serKeepAlive(bool on) = 0;
    virtual void setPort(uint32 port) = 0;
public:
    virtual int32 handleRead(IEventLoop* eventLoop) = 0;
    virtual int32 handleWrite(IEventLoop* eventLoop) = 0;
};
}
}
#endif // HYPER_INTERFACE_I_ACCEPTOR_H