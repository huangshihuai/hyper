#pragma once

#include <atomic>
#include <thread>
#include <memory>
#include "interface/i_event_loop_thread.h"
#include "interface/i_event_loop.h"
#include "net/event_loop.h"
#include "interface/i_channel.h"

namespace hyper {
namespace net {
using namespace hyper::interface;

class EventLoopThread : public IEventLoopThread {
public:
    EventLoopThread();
    virtual ~EventLoopThread() {}
    bool start() override;
    void waitingQuit() override;
    void quit() override;
    void addNotification(IChannel* channel) override;
    int init() override;
protected:
    void loop();
private:
     std::atomic_bool m_quit;
     std::thread m_thread;
     std::shared_ptr<IEventLoop> m_eventLoop;
};
}
}
