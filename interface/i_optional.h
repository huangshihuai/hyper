#ifndef HYPER_INTERFACE_I_OPTIONAL_H
#define HYPER_INTERFACE_I_OPTIONAL_H
#include <ostream>
#include <memory>
#include "base/e_net_model.h"
#include "base/btype.h"
#include "interface/i_protocol.h"
#include "interface/i_net_server.h"
namespace hyper {
namespace interface {

using namespace hyper::base;

class IOptional {
public:
    IOptional() {}
    virtual ~IOptional() {}
    virtual void setProtocol(ENetProtocol netProtocolType) = 0;
    virtual void setServerType(ENetServer serverType) = 0;
    virtual void setProtocol(std::shared_ptr<IProtocol> netProtocol) = 0;
    virtual void setTcpNoDelay(bool on) = 0;
    virtual void setReuseAddr(bool on) = 0;
    virtual void setReusePort(bool on) = 0;
    virtual void serKeepAlive(bool on) = 0;
    virtual void setSingle(bool on) = 0;
    virtual void setThreadNumber(uint32 threadNumber) = 0;
    virtual void setPort(uint32 port) = 0;
    virtual void setNetModel(ENetModel netModel) = 0;

    // virtual void getProtocol() const = 0;
    virtual ENetServer getServerType() const = 0;
    virtual bool getTcpNoDelay() const = 0;
    virtual bool getReuseAddr() const = 0;
    virtual bool getReusePort() const = 0;
    virtual bool getKeepAlive() const = 0;
    virtual bool getSingle() const = 0;
    virtual uint32 getThreadNumber() const = 0;
    virtual uint32 getPort() const = 0;
    virtual ENetModel getNetModel() const = 0;

    virtual std::string getStrProtocol() const = 0;
    virtual std::string getStrTcpNoDelay() const = 0;
    virtual std::string getStrReuseAddr() const = 0;
    virtual std::string getStrReusePort() const = 0;
    virtual std::string getStrKeepAlive() const = 0;
    virtual std::string getStrSingle() const = 0;
    virtual std::string getStrServerType() const = 0;
    virtual std::string getStrThreadNumber() const = 0;
    virtual std::string getStrPort() const = 0;

    friend std::ostream &operator<<(std::ostream &out, const IOptional &optional) {
        return out << "m_netProtocol:" << optional.getStrProtocol() << ","
                << "m_tcpNoDelay:" << optional.getStrTcpNoDelay() << ","
                << "m_reuseAddr:" << optional.getStrReuseAddr() << ","
                << "m_reusePort:" << optional.getStrReusePort() << ","
                << "m_keepAlive:" << optional.getStrKeepAlive() << ","
                << "m_single:" << optional.getStrSingle() << ","
                << "m_serverType:" << optional.getStrServerType() << ","
                << "m_threadNumver:" << optional.getStrThreadNumber() << std::endl;
    }
    friend inline std::ostream &operator<<(std::ostream &out, const std::shared_ptr<IOptional> optional) {
        return out << (*optional);
    }
};

}
}
#endif // HYPER_INTERFACE_I_OPTIONAL_H