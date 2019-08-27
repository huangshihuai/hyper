#ifndef HYPER_INTERFACE_I_NET_SERVER_H
#define HYPER_INTERFACE_I_NET_SERVER_H
#include "base/f_factory.h"

namespace hyper {
namespace interface {
using namespace hyper::base;
class IOptional;

class INetServer {
public:
    INetServer() { };
    virtual ~INetServer() { };
    virtual void setOptional(std::shared_ptr<IOptional> optional) = 0;
    virtual void addServerFactory(f_connectFactory serverFactory) = 0;
    virtual bool start() = 0;
    virtual void waitQuit() = 0;
};

}
}
#endif // HYPER_INTERFACE_I_NET_SERVER_H