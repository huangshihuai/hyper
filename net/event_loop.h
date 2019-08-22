#include "interface/i_event_loop.h"
#include "net/poll/event_epoll.h"
#include <memory>

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
private:
    std::shared_ptr<IPoll> m_eventEpoll;
};
}
}