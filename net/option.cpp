#include "net/option.h"

namespace hyper {
namespace net {
Option::Option() : m_serverType(ESocketType::TCP), m_tcpNoDelay(true), m_reuseAddr(true),
                        m_reusePort(true), m_keepAlive(true), m_single(true) {
}

Option::~Option() {
    
}

std::ostream &operator<<(std::ostream &out, const Option &Option) {
    return out << "m_netProtocol:" << Option.getStrProtocol() << ","
                << "m_tcpNoDelay:" << Option.getStrTcpNoDelay() << ","
                << "m_reuseAddr:" << Option.getStrReuseAddr() << ","
                << "m_reusePort:" << Option.getStrReusePort() << ","
                << "m_keepAlive:" << Option.getStrKeepAlive() << ","
                << "m_single:" << Option.getStrSingle();
}

std::ostream &operator<<(std::ostream &out, const std::shared_ptr<Option> Option) {
    return out << *Option;
}

}
}