#include <iostream>
#include <chrono>
#include <thread>

#include "base/macro.h"
#include "net/net_server.h"
#include "net/acceptor.h"
#include "event_loop_thread.h"
#include "base/e_poll_events.h"
#include "net/service/net_model_factory.h"

using namespace hyper::net::service;

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
        m_netModelService = NetModelFactory::getNetModel(m_option->getNetModel());
        if (nullptr == m_netModelService) {
            return false;
        }
        m_netModelService->setThread(m_option->getThreadNumber());
        m_netModelService->start(m_option);
        return true;
    }

    void NetServer::waitingQuit() {
        do {
            // wait signal
            std::this_thread::sleep_for(std::chrono::seconds(5));
        } while (true);
        m_netModelService->quit();
        m_netModelService->waitingQuit();
        return;
    }
}
}