#ifndef HYPER_INTERFACE_I_EVENT_LOOP_THREAD_H
#define HYPER_INTERFACE_I_EVENT_LOOP_THREAD_H
#include "base/e_net_model.h"
#include "interface/i_channel.h"
namespace hyper {
namespace interface {

class IEventLoopThread {
public:
    IEventLoopThread() {}
    virtual ~IEventLoopThread() {}
    virtual bool start() = 0;
    virtual void addNotification(IChannel* channels) = 0;
    virtual void waitQuit() = 0;
    virtual void quit() = 0;
    virtual int init() = 0;
};
}
}
#endif // HYPER_INTERFACE_I_EVENT_LOOP_THREAD_H