#include "interface/i_socket.h"
#include <unistd.h>

namespace hyper {
namespace net {

using namespace interface;

class Socket : public ISocket {
public:
    Socket();
    virtual ~Socket();
    bool getTcpInfo(struct tcp_info* info) const override;
    bool create() override;
    bool bindAddress() override;
    bool listen(int32 backlog) override;
    std::shared_ptr<ISocket>  accept() override;
    bool connect() override;
    inline SOCKET getFd() const override { return m_socketFd; };
    inline void close() override { ::close(m_socketFd); };
    inline void shutdown() override { ::shutdown(m_socketFd, SHUT_RDWR); };
    inline void shutdownRead() override { ::shutdown(m_socketFd, SHUT_RD); };
    inline void shutdownWrite() override { ::shutdown(m_socketFd, SHUT_WR); };
    inline void setIp(const std::string &ip) override { m_ip = ip; };
    inline void setPort(int32 port) override { m_port = port; };
    inline void setSocketOption(std::shared_ptr<ISocketOption> socketOption) override { m_socketOption = socketOption; };
    void setSocketFlags() override;
    int32 read(std::string &data) override;
    int32 write(const std::string &data) override;
private:
    bool accept(SOCKET acceptFd);
    inline void setSocketFd(SOCKET fd) { m_socketFd = fd; };
private:
    uint32 m_port;
    std::string m_ip;
    std::shared_ptr<ISocketOption> m_socketOption;
    SOCKET m_socketFd;
    SocketState m_socketState;
};
}
}