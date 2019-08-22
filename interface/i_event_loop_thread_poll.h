#ifndef HYPER_INTERFACE_EVENT_LOOP_THREAD_POLL_H
#define HYPER_INTERFACE_EVENT_LOOP_THREAD_POLL_H
#include "base/e_net_model.h"

namespace hyper {
namespace interface {
using namespace hyper::base;

class IEventLoopThreadPoll {
public:
    IEventLoopThreadPoll() { };
    virtual ~IEventLoopThreadPoll() { };

    virtual bool init() = 0;
    virtual void quit() = 0;
    virtual bool start() = 0;
    virtual void setNetModel(ENetModel netModel = ENetModel::KERNEL_DISPATCH) = 0;
};
}
}
#endif // HYPER_INTERFACE_EVENT_LOOP_POLL_H