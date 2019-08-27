#include "net/connection.h"
#include "base/e_poll_events.h"

namespace hyper {
namespace net {
using namespace hyper::base;
void Connection::onEvents(IChannel *channel) {
    auto event = channel->getEvents();
    if (event & READ_EVENT) {
        // Read
        std::string data;
        std::string onResponse;
        int32 size = m_socket->read(data);
        if (size > 0) {
            this->onRequest(data, onResponse);
            return;
        }
        // delete it;
        this->onClose();
        // clear Net Connection
        channel->
    } else if (event & WRITE_EVENT) {
        // Wriet 
    } else {
        // error
    }
}

}
}