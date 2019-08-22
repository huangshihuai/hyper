#include <iostream>
#include <chrono>
#include <thread>

#include "net_server.h"
#include "net/event_loop_thread_poll.h"

namespace hyper {
namespace net {
namespace tcp {

    NetServer::NetServer() {
    }

    NetServer::~NetServer() {
    }

    bool NetServer::start() {
        if (!init()) {
            return false;
        }

        return m_eventLoopThreadPoll->start();
    }

    bool NetServer::init() {
        m_eventLoopThreadPoll = std::make_shared<EventLoopThreadPoll>(m_optional->getThreadNumber());
        if (nullptr == m_eventLoopThreadPoll) {
            return false;
        }
        return m_eventLoopThreadPoll->init();
    }

    void NetServer::waitQuit() {
        int i = 0;
        do {
            // wait signal
            if (i++ >= 5) {
                m_eventLoopThreadPoll->quit();
                break;
            }
            std::this_thread::sleep_for(std::chrono::seconds(5));
        } while (true);
        return;
    }
}
}
}