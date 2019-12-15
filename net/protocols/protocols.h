#pragma once
#include <functional>
#include "base/btype.h"
#include "base/e_protocols.h"
#include "interface/i_protocol.h"

namespace hyper {

namespace net {
namespace protocols {
    
using namespace hyper::base;

struct RegisterProtocols {
    std::function<ProtocolStateType (std::string &responseBuf, hyper::interface::Message *response)> serialization;
    std::function<ProtocolStateType (std::string &requestBuf, hyper::interface::Message *request)> unserialization;
    std::function<hyper::interface::Message *()> createMessage;
    std::function<void (hyper::interface::Message*)> destroyMessage;
    std::function<ProtocolStateType (hyper::interface::Message* message)> executeParsingProtocol;
};

extern RegisterProtocols registerProtocols[];

ProtocolStateType executeParsingProtocol(hyper::interface::Message* message, const ProtocolTypes protocolTypes);

}
}
}