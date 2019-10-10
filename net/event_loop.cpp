#include "net/event_loop.h"
#include <thread>

namespace hyper {
namespace net {
EventLoop::EventLoop() {
    m_eventEpoll = std::make_shared<hyper::net::poll::EventEpoll>();
}

bool EventLoop::init() {
    return m_eventEpoll->init();
}

EventLoop::~EventLoop() {
}

uint32 EventLoop::loop() {
    m_eventEpoll->poll(2000, m_channelList);
    for (auto channel : m_channelList) {
        channel->onEvents();
    }
    return 0;
}

inline void EventLoop::addNotification(IChannel* channel) {
    m_eventEpoll->addNotification(channel);
}

inline void EventLoop::removeNotification(IChannel *channel) {
    m_eventEpoll->removeNotification(channel);
}

inline void EventLoop::updateNotification(IChannel *channel) {
    m_eventEpoll->updateNotification(channel);
}

}
}


