#ifndef HYPER_NET_CHANNEL_H
#define HYPER_NET_CHANNEL_H
#include "interface/i_channel.h"
namespace hyper {
namespace net {
using namespace hyper::interface;

class Channel : public IChannel {
public:
    virtual ~Channel();
    int32 handleRead() override;
	int32 handleWrite() override;
    SOCKET getFd() override;
    int32 getEvents() override;
    void onEvents(IPoll *poll) override {};
private:
    int m_eventType;
};
}
}
#endif // HYPER_NET_CHANNEL_H