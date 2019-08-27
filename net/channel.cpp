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
    this->m_eventLoop->clearNotify(this);
}
}
}