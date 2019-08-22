#include "optional.h"

namespace hyper {
namespace net {
Optional::Optional() : m_netProtocolType(ENetProtocol::STREAM), m_serverType(ENetServer::TCP),
                        m_netProtocol(nullptr), m_tcpNoDelay(true), m_reuseAddr(true),
                        m_reusePort(true), m_keepAlive(true), m_single(true) {
}

Optional::~Optional() {
    
}

std::ostream &operator<<(std::ostream &out, const Optional &optional) {
    return out << "m_netProtocol:" << optional.getStrProtocol() << ","
                << "m_tcpNoDelay:" << optional.getStrTcpNoDelay() << ","
                << "m_reuseAddr:" << optional.getStrReuseAddr() << ","
                << "m_reusePort:" << optional.getStrReusePort() << ","
                << "m_keepAlive:" << optional.getStrKeepAlive() << ","
                << "m_single:" << optional.getStrSingle();
}

std::ostream &operator<<(std::ostream &out, const std::shared_ptr<Optional> optional) {
    return out << *optional;
}

}
}