#include "net/protocols/im.h"
#include "net/common/endian.h"
#include <netinet/in.h>
#include <cstring>

namespace hyper {
namespace net {
namespace protocols {
namespace im {
ImMessage *Im::createMessage() {
    return new ImMessage;
}

void Im::destroyMessage(hyper::interface::Message *message) {
    if (message != nullptr) {
        auto imMessage = dynamic_cast<ImMessage *>(message);
        delete imMessage;
    }
}

ProtocolStateType Im::executeParsingProtocol(hyper::interface::Message*) {
    // 
}

ProtocolStateType Im::serialization(std::string &responseBuf, hyper::interface::Message *response) {
    ImMessage *imMessage = dynamic_cast<ImMessage *>(response);
    ImHead imHead;
    imHead.version = htons(4);
    imHead.magic = common::htonll(65535);

    imHead.bodySize = htons(imMessage->msg.size());
    responseBuf.append((char *)&imHead, sizeof(ImHead));
    responseBuf.append((char *)imMessage->msg.data(), imMessage->msg.size());
    return ProtocolStateType::SUCCESS;
}

ProtocolStateType Im::unserialization(std::string &requestBuf, hyper::interface::Message *request) {
    const void *buf = requestBuf.data();
    const ImHead *tmp_head = static_cast<const ImHead *>(buf);
    ImHead imHead;
    ImMessage *imMessage = dynamic_cast<ImMessage *>(request);
    imHead.version = ntohs(tmp_head->version);
    imHead.magic = common::ntohll(tmp_head->magic);
    imHead.bodySize = ntohs(tmp_head->bodySize);
    const char *tmp_body = static_cast<const char *>((void *)((char *)buf + sizeof(ImHead)));
    imMessage->msg = "";
    imMessage->msg.append(tmp_body, imHead.bodySize);
    return ProtocolStateType::SUCCESS;
}

}
}
}
}