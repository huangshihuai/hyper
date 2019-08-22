#include "acceptor.h"

namespace hyper {
namespace net {

Acceptor::Acceptor(const std::shared_ptr<IOptional> optional) {
    m_tcpNoDelay = optional->getTcpNoDelay();
    m_reuseAddr = optional->getReuseAddr();
    m_reusePort = optional->getReusePort();
    m_keepAlive = optional->getKeepAlive();
    m_port = optional->getPort();
}

Acceptor::~Acceptor() {
}

void Acceptor::init() {
}

int32 Acceptor::handleRead(IEventLoop* eventLoop) {
    return 0;
}
int32 handleWrite(IEventLoop* eventLoop) {
    return 0;
}

}
}