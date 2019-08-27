#include "channel.h"
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
}
}
}