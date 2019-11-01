#include "net/poll/event_epoll.h"
#include "base/macro.h"
#include <iostream>
#include <cassert>
#include <errno.h>
#include <string.h>

namespace hyper {
namespace net {
namespace poll {
EventEpoll::EventEpoll(uint32 backlog) : m_epollFd(-1), m_backlog(backlog) {
    m_eventList.resize(m_backlog);
}

EventEpoll::~EventEpoll() {
}

bool EventEpoll::init() {
    m_epollFd = epoll_create1(EPOLL_CLOEXEC);
    HYPER_COMPARE(m_epollFd, 0, <=, return false, "EventEpoll::init failed");
    return true;
}

uint32 EventEpoll::poll(int32 timeout, std::vector<IChannel *> &channelList) {
    channelList.clear();
    int32 size = epoll_wait(m_epollFd, &(*m_eventList.begin()), static_cast<int>(m_eventList.size()), timeout);
    for (int32 index = 0; index < size; ++index) {
        auto channel = static_cast<IChannel *>(m_eventList[index].data.ptr);
        channel->setEvents(m_eventList[index].events);
        channelList.push_back(channel);
    }
    // time
    return 0;
}

int32 EventEpoll::addNotification(IChannel* channel) {
    // No Support EPOLLONESHOT EPOLLET
    // std::cout << "add notification\n";
    assert(channel != nullptr);
    return update(HYPER_OP_ADD, channel);
}

void EventEpoll::removeNotification(IChannel *channel) {
    // std::cout << "remove notification\n";
    update(HYPER_OP_DEL, channel);
}

void EventEpoll::updateNotification(IChannel* channel) {
    // std::cout << "update notification\n";
    update(HYPER_OP_MOD, channel);
}

int32 EventEpoll::update(int32 op, IChannel *channel) {
    struct epoll_event ev;
    ev.events = HYPER_LT;
    ev.data.ptr = nullptr;
    do {
        if (op == HYPER_OP_DEL) {
            break;
        }
        ev.events = HYPER_ET;
        auto events = channel->getEvents();
        if(events & HYPER_READ) {
            ev.events |= HYPER_READ;
        }

        if(events & HYPER_WRITE) {
            ev.events |= HYPER_WRITE;
        }
        ev.data.ptr = static_cast<void *>(channel);
    } while (false);
    auto ret = epoll_ctl(m_epollFd, op, channel->getFd(), &ev);
    if(ret < 0) {
        std::cout << "epoll_ctl failed, strerrno: " << strerror(errno) << channel->getFd() << std::endl;
    }
    // std::cout << "m_epollFd: " << m_epollFd << ", op: " << op << ", events: " << ev.events << ", ret: " << ret << std::endl;
    return	ret;  
}

}
}
}
