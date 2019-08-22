#ifndef HYPER_NET_ACCEPTOR_H
#define HYPER_NET_ACCEPTOR_H

#include <memory>
#include "interface/i_optional.h"
#include "interface/i_acceptor.h"
#include "interface/i_device.h"
#include "base/btype.h"

namespace hyper {
namespace net {

using namespace hyper::interface;
using namespace hyper::base;

class Acceptor : public IAcceptor {
public:
    Acceptor(const std::shared_ptr<IOptional> optional);
    virtual ~Acceptor();
    void init() override;
    inline void setTcpNoDelay(bool on) override { m_tcpNoDelay = on; };
    inline void setReuseAddr(bool on) override { m_reuseAddr = on; };
    inline void setReusePort(bool on) override { m_reusePort = on; };
    inline void serKeepAlive(bool on) override { m_keepAlive = on; };
    inline void setPort(uint32 port) override { m_port = port; };

public:
    int32 handleRead(IEventLoop* eventLoop) override;
    int32 handleWrite(IEventLoop* eventLoop) override;
private:
    bool m_tcpNoDelay;
    bool m_reuseAddr;
    bool m_reusePort;
    bool m_keepAlive;
    uint32 m_port;
};
}
}
#endif // HYPER_NET_ACCEPTOR_H