#include "net/connection.h"
#include "base/e_poll_events.h"
#include <iostream>

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
        channel->disConnection();
        return;
    } else if (event & WRITE_EVENT) {
        // Wriet 
        int32 size = m_socket->write("hello");
        return;
    } else {
        // error
        std::cout << "Connection::onEvents error\n";
        return;
    }
    std::cout << "thundering herd\n";
}

}
}