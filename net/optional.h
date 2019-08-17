#ifndef HYPER_INTERFACE_NET_OPTIONAL_H
#define HYPER_INTERFACE_NET_OPTIONAL_H
#include "interface/i_optional.h"

namespace hyper {
namespace net {

using namespace interface;

class Optional : public IOptional {
public:
    Optional();
    ~Optional();
    inline void setProtocol(NetProtocol netProtocol) override { m_netProtocol = netProtocol; };
    inline void setTcpNoDelay(bool on) override { m_tcpNoDelay = on; };
    inline void setReuseAddr(bool on) override { m_reuseAddr = on; };
    inline void setReusePort(bool on) override { m_reusePort = on; };
    inline void serKeepAlive(bool on) override { m_keepAlive = on; };
    inline void setSingle(bool on) override { m_single = on; };
private:
    NetProtocol m_netProtocol;
    bool m_tcpNoDelay;
    bool m_reuseAddr;
    bool m_reusePort;
    bool m_keepAlive;
    bool m_single;
};
}
}
#endif // HYPER_INTERFACE_NET_OPTIONAL_H