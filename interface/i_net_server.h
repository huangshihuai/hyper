#pragma once

#include "base/f_factory.h"

namespace hyper {
namespace interface {
using namespace hyper::base;
class IOption;

class INetServer {
public:
    INetServer() { };
    virtual ~INetServer() { };
    virtual void setOption(std::shared_ptr<IOption> Option) = 0;
    virtual bool start() = 0;
    virtual void waitingQuit() = 0;
};

}
}