#include <iostream>
#include <memory>
#include "net/optional.h"
#include "interface/i_protocol.h"
#include "interface/i_server.h"
#include "net/net_server.h"
#include <unistd.h>
using namespace hyper::net;
using namespace hyper::net::tcp;
using namespace hyper::interface;

class Custom : public hyper::interface::IProtocol {
public:
    Custom() {
        std::cout << "create custom" << std::endl;
    }

    ~Custom() {
        std::cout << "destroy custom" << std::endl;
    }

    bool packStream() override {
        return true;
    }

    bool unPackStream() override {
        return true;
    }
};

class echoServerImpl : public hyper::interface::IServer {
public:
    echoServerImpl() {
        m_functionList = std::map<std::string, std::function<void (std::string, std::string)>>();
        m_functionList["request"] = std::bind(&echoServerImpl::request, this, std::placeholders::_1, std::placeholders::_2);
    }

    inline const std::map<std::string, std::function<void (std::string, std::string)>> &getBriging() {
        return m_functionList;
    }

    void request(std::string req, std::string resp) {
        std::cout << req << resp << std::endl;
    }
private:
    std::map<std::string, std::function<void (std::string, std::string)>> m_functionList;
};

int main(void) {
    std::shared_ptr<IProtocol> custom = std::make_shared<Custom>();
    std::shared_ptr<IOptional> optional = std::make_shared<Optional>();
    optional->setProtocol(custom);
    optional->setThreadNumber(3);

    std::shared_ptr<IServer> echoServer = std::make_shared<echoServerImpl>();
    std::shared_ptr<INetServer> netServer = std::make_shared<NetServer>();
    netServer->setOptional(optional);
    netServer->addServer(echoServer);
    netServer->start();
    netServer->waitQuit();
    return 0;
}