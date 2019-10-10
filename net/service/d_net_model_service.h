#pragma once

#include "interface/i_net_model_service.h"

using namespace hyper::interface;

namespace hyper {
namespace net {
namespace service {
    
class DNetModelService : public INetModelService {
public:
    DNetModelService();
    virtual ~DNetModelService();
    bool start(std::shared_ptr<IOption> option) override;
    void quit() override;
    void waitingQuit() override;
    void setThread(uint32 threadNumber) override { };
};

}
}
}
