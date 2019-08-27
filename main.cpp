#include <iostream>
#include <memory>
#include "net/optional.h"
#include "interface/i_protocol.h"
#include "interface/i_socket.h"
#include "net/connection.h"
#include "net/net_server.h"
#include <unistd.h>
using namespace hyper::net;
using namespace hyper::interface;

class echoServerImpl : public Connection {
public:
    echoServerImpl() {
    }

    void onRequest(const std::string &onRequestData, std::string &onResponseData) override {
        std::cout << onRequestData << std::endl;
    }
    
    void onResponse() override {
    }

    void onClose() override {
    }
};

std::shared_ptr<echoServerImpl> _echoServerImpl;
std::shared_ptr<hyper::interface::IConnection> createFactory() {
    return _echoServerImpl;
}

int main(void) {
    _echoServerImpl = std::make_shared<echoServerImpl>();
    std::shared_ptr<IOptional> optional = std::make_shared<Optional>();
    optional->setProtocol(ENetProtocol::STREAM);
    optional->setThreadNumber(3);
    optional->setIp("0.0.0.0");
    optional->setPort(2375);

    std::shared_ptr<hyper::interface::IConnection> echoServer = std::make_shared<echoServerImpl>();
    std::shared_ptr<INetServer> netServer = std::make_shared<NetServer>();
    netServer->setOptional(optional);
    netServer->addServerFactory(createFactory);
    if (netServer->start()) {
        netServer->waitQuit();
    }
    return 0;
}