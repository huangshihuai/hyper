#pragma once
#include <memory>
#include "base/btype.h"
#include "interface/i_option.h"

using namespace hyper::base;

namespace hyper {
namespace interface {
class INetModelService {
public: 
    INetModelService() { };
    virtual ~INetModelService() {};
    virtual bool start(std::shared_ptr<IOption> option) = 0;
    virtual void quit() = 0;
    virtual void waitingQuit() = 0;
    virtual void setThread(uint32 threadNumber) = 0;
};
}
}