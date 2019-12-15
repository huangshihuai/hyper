#include "channel.h"
#include "base/e_poll_events.h"
#include <sys/epoll.h>
#include <iostream>

namespace hyper {
namespace net {

Channel::Channel() {
}

Channel::~Channel() {
}

void Channel::disConnection() {
    this->m_eventLoop->removeNotification(this);
    this->m_connection = nullptr;
    this->m_eventLoop = nullptr;
    this->m_socket = nullptr;
}

int32 Channel::onRead() {
    int32 size = m_socket->read(m_readBuf);
    if (size != -1) {
        auto protocol = hyper::net::protocols::registerProtocols[m_protocolType];
        auto request = protocol.createMessage();
        protocol.unserialization(m_readBuf, request);
        auto response = protocol.createMessage();
        m_connection->onRequest(request, response);
        protocol.serialization(m_wirteBuf, response);
        protocol.destroyMessage(request);
        protocol.destroyMessage(response);
    }
    this->setEvents(HYPER_WRITE | HYPER_READ);
    return size;
}

inline int32 Channel::onWrite() {
    int32 size = 0;
    do {
        if (m_wirteBuf.size() <= 0) {
            break;
        }
        size = m_socket->write(m_wirteBuf);
        if (size != -1) {
            m_wirteBuf = m_wirteBuf.erase(0, size);
        }
        if (m_wirteBuf.empty()) {
            break;
        }
        return size;
    } while (false);
    this->setEvents(HYPER_READ);
    this->m_eventLoop->updateNotification(this);
    return size;
}

inline void Channel::onClose(int32 errCode) {
    if (errCode >= 0) {
        this->m_eventLoop->updateNotification(this);
        return;
    }
    m_connection->onClose();
    disConnection();
}

void Channel::onEvents() {
    auto event = getEvents();
    std::cout << std::hex << (int)(HYPER_HUP) << "\t" << std::hex << (int)HYPER_ERR << std::endl;
    std::cout << "event: " << std::hex << (int)event << std::endl;
    int32 errCode = 0;
    // EPOLLHUP | EPOLLERR
    if (event & HYPER_HUP) {
        errCode = -1;
        std::cout << "HYPER_HUP\n";
    } else if (event & HYPER_ERR) {
        errCode = -1;
        std::cout << "HYPER_ERR\n";
    } else if (event & HYPER_READ) {
        // Read
        errCode = onRead();
        // protocol
        // to user space
    } else if (event & HYPER_WRITE) {
        errCode = onWrite();
    } else {
        // error
        errCode = errno;
        std::cout << "Connection::onEvents error," << errCode << ",events:" << event << std::endl;
    }
    onClose(errCode);
    std::cout << std::flush;
}
}
}
