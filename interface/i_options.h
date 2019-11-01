#pragma once

#include <ostream>
#include <memory>
#include "base/e_net_model.h"
#include "base/e_socket.h"
#include "base/btype.h"
#include "interface/i_net_server.h"
#include "base/f_factory.h"
#include "base/e_protocols.h"

namespace hyper {
namespace interface {

using namespace hyper::base;

class IOptions {
public:
    IOptions() {}
    virtual ~IOptions() {}
    virtual void setServerType(ESocketType serverType) = 0;
    virtual void setTcpNoDelay(bool on) = 0;
    virtual void setReuseAddr(bool on) = 0;
    virtual void setReusePort(bool on) = 0;
    virtual void serKeepAlive(bool on) = 0;
    virtual void setSingle(bool on) = 0;
    virtual void setThreadNumber(uint32 threadNumber) = 0;
    virtual void setPort(uint32 port) = 0;
    virtual void setIp(const std::string &ip) = 0;
    virtual void setNetModel(ENetModel netModel) = 0;
    virtual void setConnectFactory(f_connectFactory) = 0;
    virtual void setDaemonize(bool on) = 0;
    virtual void setProtocols(ProtocolTypes protocolTypes) = 0;
    virtual void setSocketDomain(ESocketDomain socketDomain) =  0;

    // virtual void getProtocol() const = 0;
    virtual ESocketType getServerType() const = 0;
    virtual bool getTcpNoDelay() const = 0;
    virtual bool getReuseAddr() const = 0;
    virtual bool getReusePort() const = 0;
    virtual bool getKeepAlive() const = 0;
    virtual bool getSingle() const = 0;
    virtual uint32 getThreadNumber() const = 0;
    virtual uint32 getPort() const = 0;
    virtual const std::string getIp() const = 0;
    virtual ENetModel getNetModel() const = 0;
    virtual f_connectFactory getConnectFactory() const = 0;
    virtual bool getDaemonize() const = 0;
    virtual ProtocolTypes getProtocols() const = 0;
    virtual ESocketDomain getSocketDomain() const =  0;


    virtual std::string getStrProtocol() const = 0;
    virtual std::string getStrTcpNoDelay() const = 0;
    virtual std::string getStrReuseAddr() const = 0;
    virtual std::string getStrReusePort() const = 0;
    virtual std::string getStrKeepAlive() const = 0;
    virtual std::string getStrSingle() const = 0;
    virtual std::string getStrServerType() const = 0;
    virtual std::string getStrThreadNumber() const = 0;
    virtual std::string getStrPort() const = 0;

    friend std::ostream &operator<<(std::ostream &out, const IOptions &Options) {
        return out << "m_netProtocol:" << Options.getStrProtocol() << ","
                << "m_tcpNoDelay:" << Options.getStrTcpNoDelay() << ","
                << "m_reuseAddr:" << Options.getStrReuseAddr() << ","
                << "m_reusePort:" << Options.getStrReusePort() << ","
                << "m_keepAlive:" << Options.getStrKeepAlive() << ","
                << "m_single:" << Options.getStrSingle() << ","
                << "m_serverType:" << Options.getStrServerType() << ","
                << "m_threadNumver:" << Options.getStrThreadNumber() << std::endl;
    }
    friend inline std::ostream &operator<<(std::ostream &out, const std::shared_ptr<IOptions> Options) {
        return out << (*Options);
    }
};

}
}