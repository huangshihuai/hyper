#ifndef HYPER_NET_EVENT_LOOP_THREAD_POLL_H
#define HYPER_NET_EVENT_LOOP_THREAD_POLL_H
#include "interface/i_event_loop_thread_poll.h"
#include "net/event_loop_thread.h"
#include "base/btype.h"
#include <thread>
#include <vector>

namespace hyper {
namespace net {
using namespace hyper::base;
using namespace hyper::interface;

class EventLoopThreadPoll : public IEventLoopThreadPoll {
public:
    EventLoopThreadPoll(uint32 threadNumber);
    virtual ~EventLoopThreadPoll();
    bool init() override;
    bool start() override;
    inline void quit() override;
    inline void setNetModel(ENetModel netModel = ENetModel::KERNEL_DISPATCH) { m_netModel = netModel; };
private:
    uint32 m_threadNumber;
    ENetModel m_netModel;
    std::vector<std::shared_ptr<IEventLoopThread>> m_eventLoopThread;
};
}
}
#endif // HYPER_NET_EVENT_LOOP_THREAD_POLL_H