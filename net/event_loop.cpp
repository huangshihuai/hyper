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
    return m_eventEpoll->poll(2000);
}
}
}