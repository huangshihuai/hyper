#include "net/service/net_model_factory.h"
#include "net/service/d_net_model_service.h"
#include "net/service/k_net_model_service.h"

namespace hyper {
namespace net {
namespace service {
NetModelFactory::NetModelFactory() {
}

NetModelFactory::~NetModelFactory() {
}

std::shared_ptr<INetModelService> NetModelFactory::getNetModel(ENetModel eNetModel) {
    std::shared_ptr<INetModelService> netModel = nullptr;
    switch (eNetModel) {
        case ENetModel::ACCEPT_DISPATCH: {
            netModel = std::make_shared<DNetModelService>();
            return netModel;
        }
        case ENetModel::KERNEL_DISPATCH: {
            netModel = std::make_shared<KNetModelService>();
            return netModel;
        }
        default: {
            return netModel;
        }
    }
}

}
}
}