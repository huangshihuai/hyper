#include <iostream>
#include <chrono>
#include <thread>

#include "net_server.h"

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

        return m_eventLoopPoll->init();
    }

    bool NetServer::init() {
        m_eventLoopPoll = std::make_shared<EventLoopPoll>(m_optional->getThreadNumber());
        if (nullptr == m_eventLoopPoll) {
            return false;
        }
        return true;
    }

    void NetServer::waitQuit() {
        uint32  i = 0;
        do {
            auto brigingList = m_server->getBriging();
            std::for_each(brigingList.begin(), brigingList.end(), 
                    [](std::map<std::string, std::function<void (std::string, std::string)>>::reference a) {
                        auto func  = a.second;
                        func(a.first, "waitQuit");
            });
            std::cout << m_optional << std::endl;
            if (i++ == 5) {
                m_eventLoopPoll->quit();
                break;
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
        } while (true);
        return;
    }
}
}
}