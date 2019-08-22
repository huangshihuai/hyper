#ifndef HYPER_NET_POLL_EVENT_EPOLL_H
#define HYPER_NET_POLL_EVENT_EPOLL_H
#include <sys/epoll.h>

#include "interface/i_poll.h"
#include "interface/i_channel.h"
#include "base/btype.h"

namespace hyper {
namespace net {
namespace poll {
using namespace hyper::interface;
using namespace hyper::base;

class EventEpoll : public IPoll {
public:
    explicit EventEpoll(uint32 eventListBase = 20);
    virtual ~EventEpoll();
    bool init() override;
    uint32 poll(uint32 timeout/*, std::vector<IChannel> &channelList*/) override;
    void addEvent() override;
    void updateEvent() override;
private:
    EPOLL m_epollFd;
    uint32 m_eventListBase;
    std::vector<struct epoll_event> m_eventList;
};
}
}
}
#endif // HYPER_NET_POLL_EVENT_EPOLL_H
