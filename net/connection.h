#pragma once

#include "interface/i_connection.h"
#include "interface/i_channel.h"

namespace hyper {
namespace net {
using namespace hyper::interface;
class Connection : public IConnection {
public:
    virtual void onRequest(const std::string &request, std::string &response) = 0;

    virtual void onClose() = 0;
private:
    IChannel *m_channel;
};
}
}
