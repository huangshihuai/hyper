#ifndef HYPER_NET_CONNECTION_H
#define HYPER_NET_CONNECTION_H

#include "interface/i_connection.h"

namespace hyper {
namespace net {
using namespace hyper::interface;
class Connection : public IConnection {
public:
    void onEvents(IChannel *channel) override;
    
    virtual void onRequest(const std::string &onRequestData, std::string &onResponseData) = 0;
    
    virtual void onResponse() = 0;

    virtual void onClose() = 0;

    SOCKET getFd() override { return m_socket->getFd(); }

    void setSocket(std::shared_ptr<ISocket> socket) override { m_socket = socket; };
private:
    std::shared_ptr<ISocket> m_socket;
};
}
}
#endif // HYPER_NET_CONNECTION_H