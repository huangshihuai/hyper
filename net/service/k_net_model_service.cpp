#include "net/acceptor.h"
#include "net/options.h"
#include "base/macro.h"
#include "net/event_loop_thread.h"
#include "net/channel.h"
#include "net/service/k_net_model_service.h"
#include "net/socket.h"

namespace hyper {
namespace net {
namespace service {

KNetModelService::KNetModelService() {
    m_socketOption = std::make_shared<SocketOption>();
}

KNetModelService::~KNetModelService() {
}

bool KNetModelService::start(std::shared_ptr<IOptions> option) {
    if (m_threadNumber <= 0) {
        return false;
    }
    m_eventLoopThreadPoll.resize(m_threadNumber);
    auto socketOption = std::make_shared<SocketOption>();
    socketOption->setKeepAlive(option->getKeepAlive());
    socketOption->setReuseAddr(option->getReuseAddr());
    socketOption->setReusePort(option->getReusePort());
    socketOption->setTcpNoDelay(option->getTcpNoDelay());
    socketOption->setSocketDomain(option->getSocketDomain());
    socketOption->setNonBlock(true);

    for (size_t index = 0; index < m_threadNumber; ++index) {
        auto acceptor = new Acceptor;
        auto socket = std::make_shared<Socket>();
        socket->setIp(option->getIp());
        socket->setPort(option->getPort());
        socket->setSocketOption(socketOption);

        acceptor->setSocket(socket);
        acceptor->setEvents(HYPER_READ);
        acceptor->setConnectorFactory(option->getConnectFactory());
        acceptor->startListen();
        acceptor->setProtocol(option->getProtocols());
        m_eventLoopThreadPoll[index] = std::make_shared<EventLoopThread>();
        HYPER_COMPARE(m_eventLoopThreadPoll[index]->init(),
                        0, !=, return false, "init the event loop thread failed.");
        m_eventLoopThreadPoll[index]->addNotification(acceptor);
        HYPER_COMPARE(m_eventLoopThreadPoll[index]->start(),
                        true, !=, return false, "start the event loop thread failed.");
    }
    return true;
}

void KNetModelService::quit() {
    for (auto eventLoopThread : m_eventLoopThreadPoll) {
        eventLoopThread->quit();
    }
}

void KNetModelService::waitingQuit() {
    for (auto eventLoopThread : m_eventLoopThreadPoll) {
        eventLoopThread->waitingQuit();
    }
}

}
}
}
