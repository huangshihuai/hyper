#ifndef HYPER_INTERFACE_I_ACCEPTOR_H
#define HYPER_INTERFACE_I_ACCEPTOR_H
#include <string>
#include "base/btype.h"
#include "interface/i_event_loop.h"
#include "interface/i_device.h"
#include "base/e_socket_model.h"

namespace hyper {
namespace interface {

using namespace hyper::base;

class IAcceptor {
public:
    IAcceptor() { };
    virtual ~IAcceptor() { };
    virtual bool startListen() = 0;
    virtual void setTcpNoDelay(bool on) = 0;
    virtual void setReuseAddr(bool on) = 0;
    virtual void setReusePort(bool on) = 0;
    virtual void setKeepAlive(bool on) = 0;
    virtual void setPort(uint32 port) = 0;
    virtual void setIp(const std::string &ip) = 0;
    virtual void setDispatch() = 0;
    virtual void setConnectorFactory() = 0;
    virtual void setSocketModel(ESocketModel socketModel) = 0;
};
}
}
#endif // HYPER_INTERFACE_I_ACCEPTOR_H