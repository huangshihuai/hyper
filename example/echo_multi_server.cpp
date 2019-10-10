#include <iostream>
#include <memory>
#include "net/option.h"
#include "net/connection.h"
#include "net/net_server.h"
using namespace hyper::net;
using namespace hyper::interface;

class echoServerImpl : public Connection {
public:
    echoServerImpl() {
        m_index.store(1, std::memory_order_acq_rel);
    }

    void onRequest(const std::string &request, std::string &response) override {
        std::cout << request << std::endl;
        int64_t index  = m_index.fetch_add(1, std::memory_order_seq_cst);
        response = "my name is hyper" + std::to_string(index);
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
    auto option = std::make_shared<Option>();
    option->setThreadNumber(3);
    option->setIp("0.0.0.0");
    option->setPort(2375);
    option->setConnectFactory(createFactory);

    auto netServer = std::make_shared<NetServer>();
    netServer->setOption(option);
    if (netServer->start()) {
        netServer->waitingQuit();
    }
    return 0;
}
