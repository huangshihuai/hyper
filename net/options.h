#pragma once

#include <sstream>
#include "interface/i_options.h"

namespace hyper {
namespace net {

using namespace interface;

class Options : public IOptions {
public:
    Options();
    virtual ~Options();
    inline void setTcpNoDelay(bool on) override { m_tcpNoDelay = on; };
    inline void setReuseAddr(bool on) override { m_reuseAddr = on; };
    inline void setReusePort(bool on) override { m_reusePort = on; };
    inline void serKeepAlive(bool on) override { m_keepAlive = on; };
    inline void setSingle(bool on) override { m_single = on; };
    inline void setServerType(ESocketType serverType) override { m_serverType = serverType; };
    inline void setThreadNumber(uint32 threadNumber) override { m_threadNumber = threadNumber; };
    inline void setPort(uint32 port) override { m_port = port; };
    inline void setIp(const std::string &ip) { m_ip = ip; };
    inline void setNetModel(ENetModel netModel = ENetModel::KERNEL_DISPATCH) { m_netModel = netModel; };
    inline void setConnectFactory(f_connectFactory connectFactory) override { m_connectFactory = connectFactory; }
    inline void setDaemonize(bool on) override { m_daemonize = on; };
    inline void setProtocols(ProtocolTypes protocolTypes = ProtocolTypes::STREAM) override { m_protocolTypes = protocolTypes; };
    inline void setSocketDomain(ESocketDomain socketDomain = ESocketDomain::IPV4) override { m_socketDomain = socketDomain; };

    inline ESocketType getServerType() const override { return m_serverType; };
    inline bool getTcpNoDelay() const override { return m_tcpNoDelay; };
    inline bool getReuseAddr() const override { return m_reuseAddr; };
    inline bool getReusePort() const override { return m_reusePort; };
    inline bool getKeepAlive() const override { return m_keepAlive; };
    inline bool getSingle() const override { return m_single; };
    inline uint32 getThreadNumber() const override { return m_threadNumber; };
    inline uint32 getPort() const override { return m_port; };
    inline const std::string getIp() const override { return m_ip; };
    inline ENetModel getNetModel() const override { return m_netModel; };
    inline f_connectFactory getConnectFactory() const override { return m_connectFactory; };
    inline bool getDaemonize() const override {return m_daemonize; };
    inline ProtocolTypes getProtocols() const override { return m_protocolTypes; };
    inline ESocketDomain getSocketDomain() const override { return m_socketDomain; };

    std::string getStrProtocol() const override { return "netProtocol"; };
    std::string getStrTcpNoDelay() const override { return m_tcpNoDelay ? "TRUE" : "FALSE"; };
    std::string getStrReuseAddr() const override { return m_reuseAddr ? "TRUE" : "FALSE"; };
    std::string getStrReusePort() const override { return m_reusePort ? "TRUE" : "FALSE"; };
    std::string getStrKeepAlive() const override { return m_keepAlive ? "TRUE" : "FALSE"; };
    std::string getStrSingle() const override { return m_single ? "TRUE" : "FALSE"; };
    std::string getStrServerType() const override { return m_serverType == ESocketType::TCP ? "TCP" : "UDP"; };
    std::string getStrThreadNumber() const override { std::stringstream ss; ss << m_threadNumber; return ss.str(); };
    std::string getStrPort() const override { std::stringstream ss; ss << m_port; return ss.str(); };
    
    friend std::ostream &operator<<(std::ostream &out, const Options &Options);
    friend std::ostream &operator<<(std::ostream &out, const std::shared_ptr<Options> Options);
private:
    ESocketType m_serverType = ESocketType::TCP;
    ESocketDomain m_socketDomain = ESocketDomain::IPV4;
    bool m_tcpNoDelay = true;
    bool m_reuseAddr = true;
    bool m_reusePort = true;
    bool m_keepAlive = true;
    bool m_single = true;
    bool m_daemonize  = true;
    uint32 m_threadNumber;
    ENetModel m_netModel = ENetModel::KERNEL_DISPATCH;
    uint32 m_port = 80;
    std::string m_ip = "0.0.0.0";
    f_connectFactory  m_connectFactory = nullptr;
    ProtocolTypes m_protocolTypes;
};
}
}