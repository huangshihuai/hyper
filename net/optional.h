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
    inline void setServerType(ESocketModel serverType) override { m_serverType = serverType; };
    inline void setThreadNumber(uint32 threadNumber) override { m_threadNumber = threadNumber; };
    inline void setPort(uint32 port) override { m_port = port; };
    inline void setIp(const std::string &ip) { m_ip = ip; };
    inline void setNetModel(ENetModel netModel = ENetModel::KERNEL_DISPATCH) { m_netModel = netModel; };

    ESocketModel getServerType() const override { return m_serverType; };
    bool getTcpNoDelay() const override { return m_tcpNoDelay; };
    bool getReuseAddr() const override { return m_reuseAddr; };
    bool getReusePort() const override { return m_reusePort; };
    bool getKeepAlive() const override { return m_keepAlive; };
    bool getSingle() const override { return m_single; };
    uint32 getThreadNumber() const override { return m_threadNumber; };
    uint32 getPort() const override { return m_port; };
    const std::string getIp() const override { return m_ip; };
    ENetModel getNetModel() const override { return m_netModel; };

    std::string getStrProtocol() const override { return "netProtocol"; };
    std::string getStrTcpNoDelay() const override { return m_tcpNoDelay ? "TRUE" : "FALSE"; };
    std::string getStrReuseAddr() const override { return m_reuseAddr ? "TRUE" : "FALSE"; };
    std::string getStrReusePort() const override { return m_reusePort ? "TRUE" : "FALSE"; };
    std::string getStrKeepAlive() const override { return m_keepAlive ? "TRUE" : "FALSE"; };
    std::string getStrSingle() const override { return m_single ? "TRUE" : "FALSE"; };
    std::string getStrServerType() const override { return m_serverType == ESocketModel::TCP ? "TCP" : "UDP"; };
    std::string getStrThreadNumber() const override { std::stringstream ss; ss << m_threadNumber; return ss.str(); };
    std::string getStrPort() const override { std::stringstream ss; ss << m_port; return ss.str(); };
    
    friend std::ostream &operator<<(std::ostream &out, const Optional &optional);
    friend std::ostream &operator<<(std::ostream &out, const std::shared_ptr<Optional> optional);
private:
    ENetProtocol m_netProtocolType;
    ESocketModel m_serverType;
    std::shared_ptr<IProtocol> m_netProtocol;
    bool m_tcpNoDelay;
    bool m_reuseAddr;
    bool m_reusePort;
    bool m_keepAlive;
    bool m_single;
    uint32 m_threadNumber;
    uint32 m_port;
    std::string m_ip;
    ENetModel m_netModel;
};
}
}
#endif // HYPER_INTERFACE_NET_OPTIONAL_H