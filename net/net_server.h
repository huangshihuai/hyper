#pragma once

#include <vector>
#include <memory>

#include "net/acceptor.h"
#include "net/net_server.h"
#include "net/option.h"
#include "net/event_loop_thread.h"
#include "net/service/net_model_factory.h"
#include "interface/i_net_model_service.h"

namespace hyper {
namespace net {

using namespace hyper::interface;

class NetServer : public INetServer {
public:
    NetServer();
    virtual ~NetServer();
    inline void setOption(std::shared_ptr<IOption> option) override { m_option = option; };
    bool start() override;
    void waitingQuit() override;
protected:
    bool init();
private:
    std::shared_ptr<IOption> m_option = nullptr;
    // Acceptor thread when if ENetModel is KERNEL_DISPATCH
    std::shared_ptr<IEventLoopThread> m_eventAcceptor = nullptr;
    std::vector<std::shared_ptr<IEventLoopThread>> m_eventLoopThreadPoll;
    std::shared_ptr<INetModelService> m_netModelService = nullptr;
};
}
}
