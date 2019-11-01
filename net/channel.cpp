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

void Channel::addResponseData(const std::string &onResponseData) {
    m_wirteBuf += onResponseData;
}

int32 Channel::onRead() {
    std::string data;
    std::string responseStr;
    int32 size = m_socket->read(data);
    if (size != -1) {
        auto protocol = hyper::net::protocols::registerProtocols[m_protocolType];
        auto request = protocol.createMessage();
        protocol.unserialization(data, request);
        auto response = protocol.createMessage();
        m_connection->onRequest(request, response);
        protocol.serialization(responseStr, response);
        protocol.destroyMessage(request);
        protocol.destroyMessage(response);
    }
    if (!responseStr.empty()) {
        m_wirteBuf = responseStr;
        this->setEvents(HYPER_WRITE);
    }
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
    int32 errCode = 0;
    if (event & HYPER_READ) {
        // Read
        errCode = onRead();
        // protocol
        // to user space
    } else if (event & HYPER_WRITE) {
        errCode = onWrite();
    } else {
        // error
        errCode = -1;
        std::cout << "Connection::onEvents error," << errno << ",events:" << event << std::endl;
    }
    onClose(errCode);
    std::cout << std::flush;
}
}
}
