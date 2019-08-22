#ifndef HYPER_INTERFACE_I_NET_SERVER_H
#define HYPER_INTERFACE_I_NET_SERVER_H
#include "interface/i_server.h"
#include <memory>

namespace hyper {
namespace interface {
class IOptional;

enum ENetServer {
    TCP,
    UDP,
};

class INetServer {
public:
    INetServer() {};
    virtual ~INetServer() {};
    virtual void setOptional(std::shared_ptr<IOptional> optional) = 0;
    virtual void addServer(std::shared_ptr<IServer> server) = 0;
    virtual bool start() = 0;
    virtual void waitQuit() = 0;
protected:
    virtual bool init() = 0;
};

}
}
#endif // HYPER_INTERFACE_I_NET_SERVER_H