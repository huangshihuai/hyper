#pragma once
#include <memory>
#include "interface/i_net_model_service.h"
#include "base/e_net_model.h"

using namespace hyper::interface;
using namespace hyper::base;

namespace hyper {
namespace net {
namespace service {

class NetModelFactory {
public:
    NetModelFactory();
    virtual ~NetModelFactory();
    static std::shared_ptr<INetModelService> getNetModel(ENetModel netModel);
};

}
}
}
