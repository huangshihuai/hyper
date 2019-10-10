#include "interface/i_socket.h"
#include <unistd.h>

namespace hyper {
namespace net {

using namespace interface;
class Socket : public ISocket {
public:
    Socket();
    virtual ~Socket();
    bool getTcpInfo(struct tcp_info* info) const;
    bool create();
    bool bindAddress();
    bool listen(int32 backlog);
    std::shared_ptr<ISocket>  accept();
    bool connect();
    inline SOCKET getFd() const { return m_socketFd; };
    inline void close()  { ::close(m_socketFd); };
    inline void shutdown() { ::shutdown(m_socketFd, SHUT_RDWR); };
    inline void shutdownRead() { ::shutdown(m_socketFd, SHUT_RD); };
    inline void shutdownWrite() { ::shutdown(m_socketFd, SHUT_WR); };
    inline void setIp(const std::string &ip){ m_ip = ip; };
    inline void setPort(int32 port){ m_port = port; };
    inline void setSocketOption(std::shared_ptr<ISocketOption> socketOption) { m_socketOption = socketOption; };
    inline void setSocketFd(SOCKET fd) { m_socketFd = fd; };
    void setSocketFlags() override;
    int32 read(std::string &data);
    int32 write(const std::string &data);
private:
    uint32 m_port;
    std::string m_ip;
    std::shared_ptr<ISocketOption> m_socketOption;
    SOCKET m_socketFd;
    SocketState m_socketState;
};
}
}