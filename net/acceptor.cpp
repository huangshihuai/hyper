#include "acceptor.h"
#include "net/socket.h"
#include "base/macro.h"
#include "sys/epoll.h"
#include "net/channel.h"
#include <memory>
#include <thread>

namespace hyper {
namespace net {

Acceptor::Acceptor(const std::shared_ptr<IOptional> optional) {
    m_socket = std::make_shared<Socket>();
    this->setTcpNoDelay(optional->getTcpNoDelay());
    this->setReuseAddr(optional->getReuseAddr());
    this->setReusePort(optional->getReusePort());
    this->setKeepAlive(optional->getKeepAlive());
    this->setPort(optional->getPort());
    this->setIp(optional->getIp());
    this->setSocketModel(optional->getServerType());
}

Acceptor::~Acceptor() {
}

void Acceptor::onEvents(IChannel *channel) {
    do {
        auto fd = m_socket->accept();
        if (fd == nullptr) {
            if (errno != EAGAIN && errno != EWOULDBLOCK) {
            }
            return;
        } else {
            std::cout << std::this_thread::get_id() << " accept success: " << fd->getFd() << std::endl;
            auto connect = m_connectFactory();
            connect->setSocket(fd);
            IChannel *nChannel = new Channel();
            nChannel->setConnection(connect);
            nChannel->setEvents(READ_EVENT);
            auto evenLoop = channel->getEventLoop();
            nChannel->setEventLoop(evenLoop);
            evenLoop->addNotification(nChannel);
        }
    } while (true);

}

bool Acceptor::startListen() {
    HYPER_COMPARE(m_socket->createSocket(), true, !=, return false, 
                "create sock failed");
    HYPER_COMPARE(m_socket->bindAddress(), true, !=, return false,
                "bind addr and prot failed");
    HYPER_COMPARE(m_socket->listen(16), true, !=, return false,
                "listen sock failed");
    return true;
}
}
}