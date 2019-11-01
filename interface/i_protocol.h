#pragma once

namespace hyper {
namespace interface {
class Message {
public:
    Message() {};
    virtual ~Message() {};
};
class IProtocol {
public:
    IProtocol() {};
    virtual ~IProtocol() {};
};
}
}