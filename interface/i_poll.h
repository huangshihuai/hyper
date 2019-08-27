#ifndef HYPER_INTERFACE_I_POLL_H
#define HYPER_INTERFACE_I_POLL_H
#include <memory>

#include "base/btype.h"
#include "interface/i_channel.h"
namespace hyper {
namespace interface {
using namespace hyper::base;
class IChannel;

class IPoll {
public:
    IPoll() { }
    virtual ~IPoll() { }
    virtual bool init() = 0;
    virtual uint32 poll(uint32 timeout/*, std::vector<IChannel> &channelList*/) = 0;
    virtual int32 addEvent(IChannel *channel) = 0;
    virtual void updateEvent() = 0;
    virtual void removeNotification(IChannel *channel) = 0;
};
}
}
#endif // HYPER_INTERFACE_I_POLL_H