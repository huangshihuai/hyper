#include <iostream>
#include <memory>
#include <cstring>
#include "net/options.h"
//#include "net/connection.h"
#include "interface/i_connection.h"
#include "net/net_server.h"
#include "net/protocols/im.h"
#include "net/common/endian.h"

using namespace hyper::net;
using namespace hyper::interface;
class echoServerImpl : public IConnection {
public:
    echoServerImpl() {
        m_index.store(1, std::memory_order_acq_rel);
    }

    void onRequest(const hyper::interface::Message* request, hyper::interface::Message* response) {
        auto requestMessage = dynamic_cast<const hyper::net::protocols::im::ImMessage *>(request);
        std::cout << "client request: " << requestMessage->msg << std::endl;
        auto responseMessage = dynamic_cast<hyper::net::protocols::im::ImMessage *>(response);
        auto index = m_index.load(std::memory_order_consume);
        responseMessage->msg = "{\"name\":\"backend\",\"age\":"  + std::to_string(index) + "}";
        m_index.fetch_add(1, std::memory_order_release);
    }
    
    void onClose() {
        std::cout << "close\n";
    }
private:
    std::atomic_int64_t m_index;
};

std::shared_ptr<hyper::interface::IConnection> createFactory() {
    return std::make_shared<echoServerImpl>();
}

int main(void) {
    auto option = std::make_shared<Options>();
    option->setDaemonize(false);
    option->setThreadNumber(3);
    option->setIp("0.0.0.0");
    option->setPort(2375);
    option->setReusePort(true);
    option->setReuseAddr(true);
    option->setProtocols(ProtocolTypes::IM);
    option->setSocketDomain(ESocketDomain::IPV4);
    option->setConnectFactory(createFactory);

    auto netServer = std::make_shared<NetServer>();
    netServer->setOption(option);
    if (netServer->start()) {
        netServer->waitingQuit();
    }
    return 0;
}
