#include "net/service/d_net_model_service.h"

namespace hyper {
namespace net {
namespace service {

DNetModelService::DNetModelService() {
}

DNetModelService::~DNetModelService() {
}

bool DNetModelService::start(std::shared_ptr<IOption> option) {
    return true;
}

void DNetModelService::quit() {
}

void DNetModelService::waitingQuit() {

}

}
}
}
