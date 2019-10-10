#pragma once

#include <string>
#include <memory>
#include "interface/i_socket.h"
#include "interface/i_channel.h"
#include "interface/i_connection.h"

namespace hyper {
namespace net {
using namespace hyper::interface;

class Channel : public IChannel {
public:
    Channel();
    virtual ~Channel();
    inline SOCKET getFd() override { return m_socket->getFd(); };
    uint32 getEvents() override { return m_events; };
    void setEvents(uint32 events) override { m_events = events; };
    void onEvents() override;
    inline void setEventLoop(std::shared_ptr<IEventLoop> eventLoop) override { m_eventLoop = eventLoop; };
    inline std::shared_ptr<IEventLoop> getEventLoop() override { return m_eventLoop; };
    inline void setConnection(std::shared_ptr<IConnection> connection) override { m_connection = connection; };
    void disConnection() override;
    void addResponseData(const std::string &onResponseData) override;
    inline void setSocket(std::shared_ptr<ISocket> socket) override { m_socket  = socket; };
private:
    int32 onRead();
    int32 onWrite();
    void onClose(int32 errCode);
private:
    uint32 m_events;
    std::shared_ptr<IEventLoop> m_eventLoop;
    std::shared_ptr<IConnection> m_connection;
    std::shared_ptr<ISocket> m_socket;
    std::string m_wirteBuf;
};
}
}
