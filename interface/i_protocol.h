#ifndef HYPER_INTERFACE_I_PROTOCOL_H
#define HYPER_INTERFACE_I_PROTOCOL_H

namespace hyper {
namespace interface {

enum NetProtocol {
    STREAM,
    CUSTOM,
};

class IProtocol {
public:
    IProtocol() {}
    virtual ~IProtocol() {}
    virtual bool packStream() = 0;
    virtual bool unPackStream() = 0;
};
}
}
#endif // HYPER_INTERFACE_I_PROTOCOL_H