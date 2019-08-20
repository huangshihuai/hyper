#ifndef HYPER_INTERFACE_NET_OPTIONAL_H
#define HYPER_INTERFACE_NET_OPTIONAL_H
#include <sstream>
#include "interface/i_optional.h"

namespace hyper {
namespace net {

using namespace interface;

class Optional : public IOptional {
public:
    Optional();
    virtual ~Optional();
    inline void setProtocol(ENetProtocol netProtocolType) override { m_netProtocolType = netProtocolType; };
    inline void setProtocol(std::shared_ptr<IProtocol> netProtocol) override { 
        m_netProtocolType = ENetProtocol::CUSTOM;
        m_netProtocol = netProtocol;
     };
    inline void setTcpNoDelay(bool on) override { m_tcpNoDelay = on; };
    inline void setReuseAddr(bool on) override { m_reuseAddr = on; };
    inline void setReusePort(bool on) override { m_reusePort = on; };
    inline void serKeepAlive(bool on) override { m_keepAlive = on; };
    inline void setSingle(bool on) override { m_single = on; };
    inline void setServerType(ENetServer serverType) override { m_serverType = serverType; };
    inline void setThreadNumber(uint32 threadNumber) override { m_threadNumber = threadNumber; };
    inline uint32 getThreadNumber() const override { return m_threadNumber; };

    std::string getStrProtocol() const override { return "netProtocol"; };
    std::string getStrTcpNoDelay() const override { return m_tcpNoDelay ? "TRUE" : "FALSE"; };
    std::string getStrReuseAddr() const override { return m_reuseAddr ? "TRUE" : "FALSE"; };
    std::string getStrReusePort() const override { return m_reusePort ? "TRUE" : "FALSE"; };
    std::string getStrKeepAlive() const override { return m_keepAlive ? "TRUE" : "FALSE"; };
    std::string getStrSingle() const override { return m_single ? "TRUE" : "FALSE"; };
    std::string getStrServerType() const override { return m_serverType == ENetServer::TCP ? "TCP" : "UDP"; };
    std::string getStrThreadNumber() const override { std::stringstream ss; ss << m_threadNumber; return ss.str(); };
    
    friend std::ostream &operator<<(std::ostream &out, const Optional &optional);
    friend std::ostream &operator<<(std::ostream &out, const std::shared_ptr<Optional> optional);
private:
    ENetProtocol m_netProtocolType;
    ENetServer m_serverType;
    std::shared_ptr<IProtocol> m_netProtocol;
    bool m_tcpNoDelay;
    bool m_reuseAddr;
    bool m_reusePort;
    bool m_keepAlive;
    bool m_single;
    uint32 m_threadNumber;
};
}
}
#endif // HYPER_INTERFACE_NET_OPTIONAL_H