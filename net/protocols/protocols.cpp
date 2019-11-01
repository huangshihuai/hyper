#include "net/protocols/protocols.h"
#include "net/protocols/im.h"

namespace hyper {
namespace net {
namespace protocols {

const size_t MAX_PROTOCOL_SIZE = 32;

RegisterProtocols registerProtocols[] = {
    { nullptr, nullptr, },
    {
        hyper::net::protocols::im::Im::serialization,
        hyper::net::protocols::im::Im::unserialization,
        hyper::net::protocols::im::Im::createMessage,
        hyper::net::protocols::im::Im::destroyMessage,
    }
};
}
}
}