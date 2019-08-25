#ifndef HYPER_NET_TCP_TCP_SERVER_H
#define HYPER_NET_TCP_TCP_SERVER_H
#include <vector>

#include "interface/i_acceptor.h"
#include "interface/i_net_server.h"
#include "interface/i_optional.h"
#include "interface/i_event_loop_thread.h"

namespace hyper {
namespace net {

using namespace hyper::interface;

class NetServer : public INetServer {
public:
    NetServer();
    virtual ~NetServer();
    inline void setOptional(std::shared_ptr<IOptional> optional) override { m_optional = optional; };
    inline void addServer(std::shared_ptr<IServer> server) override { m_server = server; };
    void setServerFactory() override { };
    bool start() override;
    void waitQuit() override;
protected:
    bool init();
private:
    std::shared_ptr<IOptional> m_optional;
    std::shared_ptr<IServer> m_server;
    // Acceptor thread when if ENetModel is KERNEL_DISPATCH
    std::shared_ptr<IEventLoopThread> m_eventAcceptor;
    std::vector<std::shared_ptr<IEventLoopThread>> m_eventLoopThreadPoll;
};
}
}

#endif // HYPER_NET_TCP_TCP_SERVER_H