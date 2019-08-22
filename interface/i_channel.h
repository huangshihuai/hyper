#ifndef HYPER_INTERFACE_I_CHANNEL_H
#define HYPER_INTERFACE_I_CHANNEL_H
namespace hyper {
namespace interface {
class IChannel {
public:
    IChannel() { };
    virtual ~IChannel() = 0;
};
}
}
#endif // HYPER_INTERFACE_I_CHANNEL_H