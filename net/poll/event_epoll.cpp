#include "net/poll/event_epoll.h"
#include "base/macro.h"
#include <iostream>

namespace hyper {
namespace net {
namespace poll {
EventEpoll::EventEpoll(uint32 eventListBase) : m_epollFd(-1), m_eventListBase(eventListBase) {
    m_eventList.resize(m_eventListBase);
}

EventEpoll::~EventEpoll() {
}

bool EventEpoll::init() {
    m_epollFd = epoll_create1(EPOLL_CLOEXEC);
    HYPER_COMPARE(m_epollFd, 0, <=, return false, "EventEpoll::init failed");
    return true;
}

uint32 EventEpoll::poll(uint32 timeout/*, std::vector<IChannel> &channelList*/) {
    int size = epoll_wait(m_epollFd, &(*m_eventList.begin()), m_eventList.size(), timeout);
    std::cout << "EventEpoll::poll fd: " << m_epollFd << ", size: " << size << std::endl;
    return 0;
}

void EventEpoll::addEvent() {
}
void EventEpoll::updateEvent() {
}

}
}
}