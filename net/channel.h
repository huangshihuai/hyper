#ifndef HYPER_NET_CHANNEL_H
#define HYPER_NET_CHANNEL_H
#include <string>
#include <memory>
#include "interface/i_socket.h"
#include "interface/i_channel.h"

namespace hyper {
namespace net {
using namespace hyper::interface;

class Channel : public IChannel {
public:
    Channel();
    virtual ~Channel();
    inline SOCKET getFd() override { return m_connection->getFd(); };
    int32 getEvents() override { return m_events; };
    void setEvents(int32 events) override { m_events = events; };
    inline void onEvents() override { m_connection->onEvents(this); };
    inline void setEventLoop(std::shared_ptr<IEventLoop> eventLoop) override { m_eventLoop = eventLoop; };
    inline std::shared_ptr<IEventLoop> getEventLoop() override { return m_eventLoop; };
    inline void setConnection(std::shared_ptr<IConnection> connection) override { m_connection = connection; };
    void disConnection() override;
private:
    int32 m_events;
    std::shared_ptr<IEventLoop> m_eventLoop;
    std::shared_ptr<IConnection> m_connection;
};
}
}
#endif // HYPER_NET_CHANNEL_H