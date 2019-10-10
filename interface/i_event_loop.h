#pragma once

#include <memory>
#include "base/btype.h"
#include "interface/i_channel.h"

namespace hyper {
namespace interface {
using namespace hyper::base;
using namespace hyper::interface;

class IChannel;

class IEventLoop {
public:
    IEventLoop() {}
    virtual ~IEventLoop() {}
    virtual bool init() = 0;
    virtual uint32 loop() = 0;
    virtual void addNotification(IChannel *channel) = 0;
    virtual void removeNotification(IChannel *channel) = 0;
    virtual void updateNotification(IChannel *channel) = 0;
};

}
}