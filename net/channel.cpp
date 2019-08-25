#include "channel.h"
namespace hyper {
namespace net {

Channel::~Channel() {
}

int32 Channel::handleRead() {
    return 0;
}
int32 Channel::handleWrite() { 
    return 0;
}
SOCKET Channel::getFd() {
    return 0;
}
int32 Channel::getEvents() {
    return 0;
}
}
}