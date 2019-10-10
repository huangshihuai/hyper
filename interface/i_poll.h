#pragma once

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
    virtual uint32 poll(int32 timeout, std::vector<IChannel *> &channelList) = 0;
    virtual int32 addNotification(IChannel *channel) = 0;
    virtual void updateNotification(IChannel* channel) = 0;
    virtual void removeNotification(IChannel *channel) = 0;
};
}
}
