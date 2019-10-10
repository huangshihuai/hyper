#include <iostream>
#include <memory>
#include "net/option.h"
#include "net/connection.h"
#include "net/net_server.h"
#include <unistd.h>
using namespace hyper::net;
using namespace hyper::interface;

class echoServerImpl : public Connection {
public:
    echoServerImpl() {
        index = 1;
    }

    void onRequest(const std::string &request, std::string &response) override {
        std::cout << "test request: " << request << std::endl;
        response = "my name is hyper" + std::to_string(index);
        ++index;
    }

    void onClose() {
        std::cout << "close\n";
    }
private:
    uint32 index;
};

std::shared_ptr<echoServerImpl> _echoServerImpl;

std::shared_ptr<hyper::interface::IConnection> createFactory() {
    return _echoServerImpl;
}

int main(void) {
    _echoServerImpl = std::make_shared<echoServerImpl>();
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
