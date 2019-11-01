#include "net/options.h"

namespace hyper {
namespace net {
Options::Options() : m_serverType(ESocketType::TCP), m_tcpNoDelay(true), m_reuseAddr(true),
                        m_reusePort(true), m_keepAlive(true), m_single(true) {
}

Options::~Options() {
    
}

std::ostream &operator<<(std::ostream &out, const Options &Options) {
    return out << "m_netProtocol:" << Options.getStrProtocol() << ","
                << "m_tcpNoDelay:" << Options.getStrTcpNoDelay() << ","
                << "m_reuseAddr:" << Options.getStrReuseAddr() << ","
                << "m_reusePort:" << Options.getStrReusePort() << ","
                << "m_keepAlive:" << Options.getStrKeepAlive() << ","
                << "m_single:" << Options.getStrSingle();
}

std::ostream &operator<<(std::ostream &out, const std::shared_ptr<Options> Options) {
    return out << *Options;
}

}
}