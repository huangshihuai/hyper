#pragma once

#include <ostream>
#include <memory>
#include "base/e_net_model.h"
#include "base/e_socket_type.h"
#include "base/btype.h"
#include "interface/i_net_server.h"
#include "base/f_factory.h"

namespace hyper {
namespace interface {

using namespace hyper::base;

class IOption {
public:
    IOption() {}
    virtual ~IOption() {}
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

    virtual std::string getStrProtocol() const = 0;
    virtual std::string getStrTcpNoDelay() const = 0;
    virtual std::string getStrReuseAddr() const = 0;
    virtual std::string getStrReusePort() const = 0;
    virtual std::string getStrKeepAlive() const = 0;
    virtual std::string getStrSingle() const = 0;
    virtual std::string getStrServerType() const = 0;
    virtual std::string getStrThreadNumber() const = 0;
    virtual std::string getStrPort() const = 0;

    friend std::ostream &operator<<(std::ostream &out, const IOption &Option) {
        return out << "m_netProtocol:" << Option.getStrProtocol() << ","
                << "m_tcpNoDelay:" << Option.getStrTcpNoDelay() << ","
                << "m_reuseAddr:" << Option.getStrReuseAddr() << ","
                << "m_reusePort:" << Option.getStrReusePort() << ","
                << "m_keepAlive:" << Option.getStrKeepAlive() << ","
                << "m_single:" << Option.getStrSingle() << ","
                << "m_serverType:" << Option.getStrServerType() << ","
                << "m_threadNumver:" << Option.getStrThreadNumber() << std::endl;
    }
    friend inline std::ostream &operator<<(std::ostream &out, const std::shared_ptr<IOption> Option) {
        return out << (*Option);
    }
};

}
}