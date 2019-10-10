#pragma once

#include <vector>
#include <sys/epoll.h>
#include "base/e_poll_events.h"
#include "base/btype.h"
#include "interface/i_poll.h"

namespace hyper {
namespace net {
namespace poll {
using namespace hyper::interface;
using namespace hyper::base;

class EventEpoll : public IPoll {
public:
    explicit EventEpoll(uint32 backlog = 20);
    virtual ~EventEpoll();
    bool init() override;
    uint32 poll(int32 timeout, std::vector<IChannel *> &channelList) override;
    int32 addNotification(IChannel* channel) override;
    void updateNotification(IChannel* channel) override;
    void removeNotification(IChannel *channel) override;
private:
    int32 update(int32 op, IChannel *channel);
private:
    poll_t m_epollFd;
    uint32 m_backlog;
    std::vector<struct epoll_event> m_eventList;
};
}
}
}