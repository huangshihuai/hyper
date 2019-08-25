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

namespace hyper {
namespace net {

using namespace hyper::interface;
using namespace hyper::base;

class Acceptor : public IAcceptor
                , public IChannel {
public:
    Acceptor(const std::shared_ptr<IOptional> optional);
    virtual ~Acceptor();
    inline void setTcpNoDelay(bool on) override { m_socket->setTcpNoDelay(on); };
    inline void setReuseAddr(bool on) override { m_socket->setReuseAddr(on); };
    inline void setReusePort(bool on) override { m_socket->setReusePort(on); };
    inline void setKeepAlive(bool on) override { m_socket->setKeepAlive(on); };
    inline void setPort(uint32 port) override { m_socket->setPort(port); };
    inline void setIp(const std::string &ip) override { m_socket->setIp(ip); };
    inline void setSocketModel(ESocketModel socketModel) override { m_socket->setSocketModel(socketModel); } 
    bool startListen() override;
    inline void setDispatch() override { };
    inline void setConnectorFactory() override { };
    inline SOCKET getFd() override { std::cout << "getSocket - hsh" << m_socket->getFd();return m_socket->getFd(); };
    void onEvents(IPoll *poll) override;
    int32 handleRead() override;
	int32 handleWrite() override;
    int32 getEvents() override { return READ_EVENT; };
private:
    std::shared_ptr<ISocket> m_socket;
};
}
}
#endif // HYPER_NET_ACCEPTOR_H