#include "net/event_loop_thread_poll.h"
#include "base/macro.h"
#include <iostream>
#include <thread>

namespace hyper {
namespace net {
using namespace hyper::macro;

EventLoopThreadPoll::EventLoopThreadPoll(uint32 threadNumber)
        : m_threadNumber(threadNumber)
        , m_netModel(ENetModel::KERNEL_DISPATCH) {
}

EventLoopThreadPoll::~EventLoopThreadPoll() {
}

void EventLoopThreadPoll::quit() {
    for (auto it = m_eventLoopThread.begin(); it != m_eventLoopThread.end(); ++it) {
        (*it)->quit();
    }
    for (auto it = m_eventLoopThread.begin(); it != m_eventLoopThread.end(); ++it) {
        (*it)->waitQuit();
    }
}

bool EventLoopThreadPoll::init() {
    if (ENetModel::KERNEL_DISPATCH == m_netModel) {
        m_eventLoopThread.resize(m_threadNumber);
        for (uint32 index = 0; index < m_threadNumber; ++index) {
            m_eventLoopThread[index] = std::make_shared<EventLoopThread>();
        }
    }
    return true;
}

bool EventLoopThreadPoll::start() {
    for (uint32 index = 0; index < m_threadNumber; ++index) {
        HYPER_COMPARE(m_eventLoopThread[index]->start(), true, !=, return false,
                        "the start event loop thread failed");
    }
    return true;
}

}
} // namespace nameh
