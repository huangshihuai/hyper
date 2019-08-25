#include <memory>
#include "interface/i_event_loop.h"
#include "net/poll/event_epoll.h"
#include "interface/i_device.h"
#include "interface/i_channel.h"

namespace hyper {
namespace net {

using namespace hyper::interface;
using namespace hyper::net::poll;

class EventLoop : public IEventLoop {
public:
    EventLoop();
    virtual ~EventLoop();
    bool init() override;
    uint32 loop() override;
    void addEvent() override;
    void setNotification(IChannel* channel) override;
private:
    std::shared_ptr<IPoll> m_eventEpoll;
};
}
}