#ifndef HYPER_INTERFACE_I_EVENT_LOOP_H
#define HYPER_INTERFACE_I_EVENT_LOOP_H
#include "base/btype.h"

namespace hyper {
namespace interface {
using namespace hyper::base;
class IEventLoop {
public:
    IEventLoop() {}
    virtual ~IEventLoop() {}
    virtual bool init() = 0;
    virtual uint32 loop() = 0;
};
}
}
#endif // HYPER_INTERFACE_I_EVENT_LOOP_H