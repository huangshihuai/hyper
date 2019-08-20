#ifndef HYPER_NET_EVENT_LOOP_POLL_H
#define HYPER_NET_EVENT_LOOP_POLL_H
#include "interface/i_event_loop_poll.h"
#include <thread>
#include <vector>

namespace hyper {
namespace net {
using namespace hyper::base;
using namespace hyper::interface;

class EventLoopPoll : public IEventLoopPoll {
public:
    EventLoopPoll(uint32 threadNumber);
    virtual ~EventLoopPoll();

    bool init() override;
    void loop() override;
    inline void quit() override;
private:
    uint32 m_threadNumber;
    bool m_quit;
    std::vector<std::thread> m_eventLoop;
};
}
}
#endif // HYPER_NET_EVENT_LOOP_POLL_H