#include "acceptor.h"
#include "net/socket.h"
#include "base/macro.h"
#include <memory>

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

bool Acceptor::startListen() {
    HYPER_COMPARE(m_socket->createSocket(), true, !=, return false, 
                "create sock failed");
    HYPER_COMPARE(m_socket->bindAddress(), true, !=, return false,
                "bind addr and prot failed");
    HYPER_COMPARE(m_socket->listen(16), true, !=, return false,
                "listen sock failed");
    return true;
}

void Acceptor::onEvents(IPoll *poll) {
    do {
        auto fd = m_socket->accept();
        if (fd <= 0) {
            if (errno != EAGAIN && errno != EWOULDBLOCK) {
                // LOG
            }
            return;
        } else {
            std::cout << "accept success: " << fd << std::endl;
            ::shutdown(fd, 0); // read
            ::shutdown(fd, 1); // write
            /*
            if (setConnectorFactory == nullptr) {
                return;
            }
            IChannel *channel = setConnectorFactory();
            channel->
            poll->addEvent(channel);
            */
        }
    } while (true);
}

int32 Acceptor::handleRead() {
    return 0;
}

int32 Acceptor::handleWrite() {
    return 0;
}

}
}