#ifndef HYPER_NET_CHANNEL_H
#define HYPER_NET_CHANNEL_H
#include "interface/i_channel.h"
namespace hyper {
namespace net {
using namespace hyper::interface;

class Channel : public IChannel {
public:
    virtual ~Channel();
};
}
}
#endif // HYPER_NET_CHANNEL_H