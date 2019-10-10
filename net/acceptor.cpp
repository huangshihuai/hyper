#include "acceptor.h"
#include "net/socket.h"
#include "base/macro.h"
#include "net/channel.h"
#include <memory>
#include <thread>

namespace hyper {
namespace net {

Acceptor::Acceptor() {
    m_socket = std::make_shared<Socket>();
}

Acceptor::~Acceptor() {
}

void Acceptor::onEvents() {
    auto event = getEvents();
    if (HYPER_READ & event) {
        connected();
        return;
    }
    
}

void Acceptor::connected() {
    do {
        auto socket = m_socket->accept();
        if (socket == nullptr) {
            if (errno != EAGAIN && errno != EWOULDBLOCK) {
            }
            return;
        } else {
            // std::cout << std::this_thread::get_id() << " accept success: " << socket->getFd() << std::endl;
            auto connector = m_connectFactory();
            IChannel *channel = new Channel();
            channel->setConnection(connector);
            channel->setEvents(HYPER_READ);
            channel->setEventLoop(m_eventLoop);
            channel->setSocket(socket);
            m_eventLoop->addNotification(channel);
        }
    } while (true);
}

bool Acceptor::startListen() {
    HYPER_COMPARE(m_socket->create(), true, !=, return false, 
                "create sock failed");
    HYPER_COMPARE(m_socket->bindAddress(), true, !=, return false,
                "bind addr and prot failed");
    HYPER_COMPARE(m_socket->listen(16), true, !=, return false,
                "listen sock failed");
    return true;
}
}
}
