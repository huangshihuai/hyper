#pragma once

#include <vector>
#include <memory>
#include "interface/i_net_model_service.h"
#include "interface/i_event_loop_thread.h"
#include "net/socket_option.h"

using namespace hyper::interface;

namespace hyper {
namespace net {
namespace service {

class KNetModelService : public INetModelService {
public:
    KNetModelService();
    virtual ~KNetModelService();
    bool start(std::shared_ptr<IOption> option) override;
    void quit() override;
    void waitingQuit() override;
    void setThread(uint32 threadNumber) override { m_threadNumber = threadNumber; };
private:
    uint32 m_threadNumber = 0;
    std::vector<std::shared_ptr<IEventLoopThread>> m_eventLoopThreadPoll;
    std::shared_ptr<SocketOption> m_socketOption = nullptr;
};

}
}
}
