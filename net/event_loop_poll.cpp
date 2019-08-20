#include "net/event_loop_poll.h"
#include <iostream>
#include <thread>

namespace hyper {
namespace net {
EventLoopPoll::EventLoopPoll(uint32 threadNumber) : m_threadNumber(threadNumber), m_quit(false) {
}

EventLoopPoll::~EventLoopPoll() {
}

void EventLoopPoll::quit() {
    m_quit = true;
    for (auto it = m_eventLoop.begin(); it != m_eventLoop.end(); ++it) {
        it->join();
    }
}

bool EventLoopPoll::init() {
    m_eventLoop.resize(m_threadNumber);
    for (uint32 index = 0; index < m_threadNumber; ++index) {
        m_eventLoop[index] = std::thread(&EventLoopPoll::loop, this);
        std::cout << "start thread" << index << std::endl;
    }
    return true;
}

void EventLoopPoll::loop() {
    do {
        std::cout << "thread id:" << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } while (!m_quit);
}

}
} // namespace nameh
