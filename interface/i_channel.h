#ifndef HYPER_INTERFACE_I_CHANNEL_H
#define HYPER_INTERFACE_I_CHANNEL_H
#include "base/btype.h"

namespace hyper {
namespace interface {
using namespace hyper::base;
class IPoll;

class IChannel {
public:
    IChannel() { };
    virtual ~IChannel() { };
    virtual void onEvents(IPoll *poll) = 0;
    virtual int32 handleRead() = 0;
	virtual int32 handleWrite() = 0;
    virtual SOCKET getFd() = 0;
    virtual int32 getEvents() = 0;
    //virtual void setEvents() = 0;
};
}
}
#endif // HYPER_INTERFACE_I_CHANNEL_H