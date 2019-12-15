#pragma once
#include "base/btype.h"
#include "interface/i_protocol.h"
#include "net/protocols/protocols.h"

namespace hyper {
namespace net {
namespace protocols {
namespace im {

using namespace hyper::base;

struct ImHead {
    uint16 version;
    uint64_t magic;
    uint32_t bodySize;
};

class ImMessage : public hyper::interface::Message {
public:
    ImMessage() { };
    virtual ~ImMessage() {};
public:
    std::string msg;
};

class Im  {

public:
    ProtocolStateType static serialization(std::string &responseBuf, hyper::interface::Message *response);
    ProtocolStateType static unserialization(std::string &requestBuf, hyper::interface::Message *request);
    ImMessage static *createMessage();
    static void destroyMessage(hyper::interface::Message*);
    ProtocolStateType static executeParsingProtocol(hyper::interface::Message*);
};
}
}
}
}