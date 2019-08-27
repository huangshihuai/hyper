#ifndef HYPER_INTERFACE_I_CONNECTION_H
#define HYPER_INTERFACE_I_CONNECTION_H
#include <string>
#include "base/btype.h"
#include "interface/i_channel.h"
#include "interface/i_socket.h"
namespace hyper {
namespace interface {
using namespace hyper::base;
class IChannel;
class IConnection {
public:
    IConnection() { };

    virtual ~IConnection() { };

    virtual void onEvents(IChannel *channel) = 0;

    virtual void onRequest(const std::string &onRequestData, std::string &onResponseData) = 0;
    
    virtual void onResponse() = 0;

    virtual void onClose() = 0;

    virtual SOCKET getFd() = 0;
    
    virtual void setSocket(std::shared_ptr<ISocket> socket) = 0;
};
}
}
#endif // HYPER_INTERFACE_I_CONNECTION_H