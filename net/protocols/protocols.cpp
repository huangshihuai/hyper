#include "net/protocols/protocols.h"
#include "net/protocols/im.h"

namespace hyper {
namespace net {
namespace protocols {

const size_t MAX_PROTOCOL_SIZE = 1;

RegisterProtocols registerProtocols[] = {
    {
        hyper::net::protocols::im::Im::serialization,
        hyper::net::protocols::im::Im::unserialization,
        hyper::net::protocols::im::Im::createMessage,
        hyper::net::protocols::im::Im::destroyMessage,
        nullptr,
    }
};

ProtocolStateType executeParsingProtocol(hyper::interface::Message* message, const ProtocolTypes protocolTypes) {
    if (protocolTypes >= MAX_PROTOCOL_SIZE) {
        return ProtocolStateType::NOT_FOUND;
    }
    auto protocol = hyper::net::protocols::registerProtocols[protocolTypes];
    if (nullptr == protocol.executeParsingProtocol)
    return protocol.executeParsingProtocol(message);
    /*
    auto request = protocol.createMessage();
    protocol.unserialization(data, request);
    auto response = protocol.createMessage();
    m_connection->onRequest(request, response);
    protocol.serialization(responseStr, response);
    protocol.destroyMessage(request);
    protocol.destroyMessage(response);
    */
}
}
}
}