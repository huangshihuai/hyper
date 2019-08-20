#include "interface/i_socket.h"

namespace hyper {
namespace net {
using namespace interface;
class Socket : public ISocket {
public:
    SOCKET getFd() const override; 
    bool getTcpInfo(struct tcp_info* info) const override;
    void bindAddress() override;
    void listen() override;
    int  accept() override;
    void connect() override;
    void shutdownWrite() override;
    void setTcpNoDelay(bool on) override;
    void setReuseAddr(bool on) override;
    void setReusePort(bool on) override;
    void setKeepAlive(bool on) override;
};
}
}