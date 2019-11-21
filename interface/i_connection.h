#pragma once

#include <string>
#include "base/btype.h"
#include "interface/i_channel.h"
#include "interface/i_socket.h"
#include "interface/i_protocol.h"

namespace hyper {
namespace interface {
using namespace hyper::base;
class IChannel;
class IConnection {
public:
    IConnection() { };

    virtual ~IConnection() { };

    virtual void onRequest(const hyper::interface::Message* request, hyper::interface::Message* response) = 0;

    virtual void onClose() = 0;
};
}
}
