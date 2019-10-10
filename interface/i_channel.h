#pragma once

#include <memory>
#include "base/btype.h"
#include "interface/i_event_loop.h"
#include "interface/i_connection.h"
#include "interface/i_socket.h"

namespace hyper {
namespace interface {
using namespace hyper::base;
using namespace hyper::interface;
class IConnection;
class IEventLoop;

class IChannel {
public:
    IChannel() { };
    virtual ~IChannel() { };
    virtual void onEvents() = 0;
    virtual SOCKET getFd() = 0;
    virtual uint32 getEvents() = 0;
    virtual void setEvents(uint32 events) = 0;
    virtual void setEventLoop(std::shared_ptr<IEventLoop> eventLoop) = 0;
    virtual std::shared_ptr<IEventLoop> getEventLoop() = 0;
    virtual void setConnection(std::shared_ptr<IConnection> connection) = 0;
    virtual void disConnection() = 0;
    virtual void addResponseData(const std::string &onResponseData) = 0;
    virtual void setSocket(std::shared_ptr<ISocket>) = 0;
};
}
}
