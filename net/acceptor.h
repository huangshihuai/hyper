#ifndef HYPER_NET_ACCEPTOR_H
#define HYPER_NET_ACCEPTOR_H

#include <memory>
#include <iostream>
#include "interface/i_optional.h"
#include "interface/i_acceptor.h"
#include "interface/i_channel.h"
#include "base/btype.h"
#include "interface/i_socket.h"
#include "base/e_poll_events.h"
#include "interface/i_connection.h"

namespace hyper {
namespace net {

using namespace hyper::interface;
using namespace hyper::base;


class Acceptor : public IAcceptor,
                    public IConnection {
public:
    Acceptor(const std::shared_ptr<IOptional> optional);
    virtual ~Acceptor();
    inline void setTcpNoDelay(bool on) override { m_socket->setTcpNoDelay(on); };
    inline void setReuseAddr(bool on) override { m_socket->setReuseAddr(on); };
    inline void setReusePort(bool on) override { m_socket->setReusePort(on); };
    inline void setKeepAlive(bool on) override { m_socket->setKeepAlive(on); };
    inline void setPort(uint32 port) override { m_socket->setPort(port); };
    inline void setIp(const std::string &ip) override { m_socket->setIp(ip); };
    inline void setSocketModel(ESocketModel socketModel) override { m_socket->setSocketModel(socketModel); };
    inline void setDispatch() override { };
    inline void setConnectorFactory(f_connectFactory connectFactory) override { m_connectFactory = connectFactory; };
    inline void setSocket(std::shared_ptr<ISocket> socket) override { m_socket = socket; };
    bool startListen() override;
public:
#pragma mark - the IConnection
    void onEvents(IChannel *channel) override;
    
    void onRequest(const std::string &onRequestData, std::string &onResponseData) override { };
    
    void onResponse() override { };

    void onClose() override { };

    SOCKET getFd() override { return m_socket->getFd(); };
private:
    std::shared_ptr<ISocket> m_socket;
    f_connectFactory m_connectFactory;
};
}
}
#endif // HYPER_NET_ACCEPTOR_H