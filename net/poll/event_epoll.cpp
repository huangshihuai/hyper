#include "net/poll/event_epoll.h"
#include "base/macro.h"
#include <iostream>
#include <cassert>
#include <errno.h>
#include <string.h>

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
    for (auto index = 0; index < size; ++index) {
        auto channel = static_cast<IChannel *>(m_eventList[index].data.ptr);
        channel->setEvents(m_eventList[index].events);
        channel->onEvents();
    }
    return 0;
}

int32 EventEpoll::addEvent(IChannel* channel) {
    // No Support EPOLLONESHOT
    std::cout << "add event\n";
    assert(channel != nullptr);
    struct epoll_event ev;
    auto events = channel->getEvents();
    if(events & READ_EVENT){
        ev.events |= EPOLLIN;
    }
    if(events & WRITE_EVENT){
        ev.events |= EPOLLOUT;
    }
    ev.data.ptr = static_cast<void *>(channel);
    auto ret = epoll_ctl(m_epollFd, EPOLL_CTL_ADD, channel->getFd(), &ev);
    if(ret < 0) {
        std::cout << "epoll_ctl failed, strerrno: " << strerror(errno) << std::endl;
        // error 
    }
    return	ret;  
}
void EventEpoll::updateEvent() {
}

}
}
}