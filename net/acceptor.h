#pragma once

#include <memory>
#include <iostream>
#include "interface/i_options.h"
#include "interface/i_acceptor.h"
#include "interface/i_channel.h"
#include "base/btype.h"
#include "interface/i_socket.h"
#include "base/e_poll_events.h"
#include "interface/i_connection.h"
#include "net/socket_option.h"

namespace hyper {
namespace net {

using namespace hyper::interface;
using namespace hyper::base;


class Acceptor : public IAcceptor, public IChannel {
public:
    Acceptor();
    virtual ~Acceptor();
    bool startListen() override;
    inline void setDispatch() override { };
    inline void setConnectorFactory(f_connectFactory connectFactory) override { m_connectFactory = connectFactory; };
private:
    void connected();
public:
    void onEvents() override;
    SOCKET getFd() override { return m_socket->getFd(); }
    uint32 getEvents() override { return m_events; };
    void setEvents(uint32 events) override { m_events = events; };
    void setEventLoop(std::shared_ptr<IEventLoop> eventLoop) override { m_eventLoop = eventLoop; };
    std::shared_ptr<IEventLoop> getEventLoop() override { return m_eventLoop; };
    void disConnection() override { };
    void addResponseData(const std::string &onResponseData) override { };
    inline void setConnection(std::shared_ptr<IConnection> connection) override { };
    inline void setSocket(std::shared_ptr<ISocket> socket) override { m_socket  = socket; };
    inline void setProtocol(ProtocolTypes protocolType) { m_protocolType = protocolType; };
private:
    uint32 m_events;
    std::shared_ptr<ISocket> m_socket = nullptr;
    f_connectFactory m_connectFactory = nullptr;
    std::shared_ptr<IEventLoop> m_eventLoop = nullptr;
    ProtocolTypes m_protocolType;
};
}
}