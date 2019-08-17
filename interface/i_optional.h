#ifndef HYPER_INTERFACE_I_OPTIONAL_H
#define HYPER_INTERFACE_I_OPTIONAL_H
#include "interface/i_protocol.h"

namespace hyper {
namespace interface {

class IOptional {
public:
    IOptional() {}
    ~IOptional() {}
    virtual void setProtocol(NetProtocol netProtocol) = 0;
    virtual void setTcpNoDelay(bool on) = 0;
    virtual void setReuseAddr(bool on) = 0;
    virtual void setReusePort(bool on) = 0;
    virtual void serKeepAlive(bool on) = 0;
    virtual void setSingle(bool on) = 0;
};

}
}
#endif // HYPER_INTERFACE_I_OPTIONAL_H