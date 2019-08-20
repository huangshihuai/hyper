#ifndef HYPER_INTERFACE_EVENT_LOOP_POLL_H
#define HYPER_INTERFACE_EVENT_LOOP_POLL_H
#include "base/btype.h"
#include <thread>
#include <vector>

namespace hyper {
namespace interface {
using namespace hyper::base;

class IEventLoopPoll {
public:
    IEventLoopPoll() { };
    virtual ~IEventLoopPoll() { };

    virtual bool init() = 0;
    virtual void loop() = 0;
    virtual void quit() = 0;
};
}
}
#endif // HYPER_INTERFACE_EVENT_LOOP_POLL_H