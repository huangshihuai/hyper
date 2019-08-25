#include <iostream>
#include <chrono>
#include <thread>

#include "base/macro.h"
#include "net_server.h"
#include "net/acceptor.h"
#include "event_loop_thread.h"

namespace hyper {
namespace net {
    NetServer::NetServer() {
    }

    NetServer::~NetServer() {
    }

    bool NetServer::start() {
        if (!init()) {
            return false;
        }
        return true;
    }

    bool NetServer::init() {

        if (ENetModel::KERNEL_DISPATCH != m_optional->getNetModel()) {
            return false;
        }
        auto threadNumber = m_optional->getThreadNumber();
        m_eventLoopThreadPoll.resize(threadNumber);
        for (size_t index = 0; index < threadNumber; ++index) {
            Acceptor *acceptor = new Acceptor(m_optional);
            acceptor->startListen();
            m_eventLoopThreadPoll[index] = std::make_shared<EventLoopThread>();
            HYPER_COMPARE(m_eventLoopThreadPoll[index]->init(),
                            0, !=, return false, "init the event loop thread failed");
            m_eventLoopThreadPoll[index]->setNotification(acceptor);
            HYPER_COMPARE(m_eventLoopThreadPoll[index]->start(),
                            true, !=, return false, "start the event loop thread failed");
        }
        return true;
    }

    void NetServer::waitQuit() {
        int i = 0;
        do {
            // wait signal
            std::this_thread::sleep_for(std::chrono::seconds(5));
        } while (true);
        return;
    }
}
}