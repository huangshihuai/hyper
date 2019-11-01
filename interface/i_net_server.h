#pragma once

#include "base/f_factory.h"

namespace hyper {
namespace interface {
using namespace hyper::base;
class IOptions;

class INetServer {
public:
    INetServer() { };
    virtual ~INetServer() { };
    virtual void setOption(std::shared_ptr<IOptions> Options) = 0;
    virtual bool start() = 0;
    virtual void waitingQuit() = 0;
    virtual void installSignal() = 0;
    virtual void daemonize() = 0;
};

}
}