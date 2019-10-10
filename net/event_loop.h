#include <memory>
#include "interface/i_event_loop.h"
#include "net/poll/event_epoll.h"
#include "net/channel.h"

namespace hyper {
namespace net {

using namespace hyper::interface;
using namespace hyper::net::poll;

class EventLoop : public IEventLoop, std::enable_shared_from_this<EventLoop> {
public:
    EventLoop();
    virtual ~EventLoop();
    bool init() override;
    uint32 loop() override;
    void addNotification(IChannel* channel) override;
    void removeNotification(IChannel *channel)  override;
    void updateNotification(IChannel *channel) override;
private:
    std::shared_ptr<IPoll> m_eventEpoll;
    std::vector<IChannel *> m_channelList;
};
}
}