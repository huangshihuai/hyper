#pragma once
#include "interface/i_socket_option.h"

namespace hyper {
namespace net {
using namespace hyper::interface;
using namespace hyper::base;

class SocketOption : public ISocketOption {
public:
    SocketOption() {};
    virtual  ~SocketOption() {};
    inline void setSocketType(ESocketType socketType) override { m_socketType = socketType; };
    inline void setTcpNoDelay(bool on) override { m_tcpNoDelay = on; };
    inline void setReuseAddr(bool on) override { m_reuseAddr = on; };
    inline void setReusePort(bool on) override { m_reusePort = on; };
    inline void setKeepAlive(bool on) override { m_keepAlive = on; };
    inline void setFast(bool on) override { m_fast = on; };
    inline void setNonBlock(bool on) override { m_nonBlock = on; };
    inline void setSocketDomain(ESocketDomain socketDomain = ESocketDomain::IPV4) override { m_socketDomain = socketDomain; };

    inline ESocketType getSocketType() const override { return m_socketType; };
    inline bool getTcpNoDelay() const override { return m_tcpNoDelay; };
    inline bool getReuseAddr() const override { return m_reuseAddr; };
    inline bool getReusePort() const override { return m_reusePort; };
    inline bool getKeepAlive() const override { return m_keepAlive; };
    inline bool getFast() const override { return m_fast; };
    inline bool getNonBlock() const override { return m_nonBlock; };
    inline ESocketDomain getSocketDomain() const override { return m_socketDomain; };
private:
    ESocketType m_socketType = ESocketType::TCP;
    ESocketDomain m_socketDomain = ESocketDomain::IPV4;
    bool m_tcpNoDelay = true;
    bool m_reuseAddr = false;
    bool m_reusePort = false;
    bool m_keepAlive = true;
    bool m_fast = false;
    bool m_nonBlock = false;
    
};
}
}