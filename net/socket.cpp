#include "net/socket.h"
#include <sys/ioctl.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <cstring>
#include <string.h>
#include <iostream>
#include <thread>

namespace hyper {
namespace net{
Socket::Socket() {
    m_socketState = SocketState::NONE;
    m_socketFd = -1;
}
Socket::~Socket() {
}

bool Socket::getTcpInfo(struct tcp_info* info) const {
    return true;
}

bool Socket::create() {
    if (m_socketOption->getSocketType() != ESocketType::TCP && 
        m_socketOption->getSocketType() != ESocketType::UDP) {
        std::cout << "the socket model failed: " << m_socketOption->getSocketType() << std::endl;;
        return false;
    }
    m_socketFd = 0;
    int type = m_socketOption->getSocketType() | SOCK_CLOEXEC;
    if (m_socketOption->getNonBlock()) {
        type |= SOCK_NONBLOCK;
    }
    
    auto afInet = m_socketOption->getSocketDomain();
    // m_socketFd = ::socket(afInet, m_socketOption->getSocketType() | SOCK_CLOEXEC | SOCK_NONBLOCK, IPPROTO_TCP);
    m_socketFd = ::socket(afInet, type, IPPROTO_TCP);
    if (m_socketFd < 0) {
        std::cout << "errno" << errno << strerror(errno) << std::endl;
        return false;
    }
    setSocketFlags();
    m_socketState = SocketState::CREATE;
    return true;
}

void Socket::setSocketFlags() {
    if (m_socketOption->getReuseAddr()) {
        int reuseAddr = 1;
        setsockopt(m_socketFd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuseAddr, sizeof(int));
    }
    if (m_socketOption->getReusePort()) {
        int reusePort = 1;
        setsockopt(m_socketFd, SOL_SOCKET, SO_REUSEPORT, (char *)&reusePort, sizeof(int));
    }
    if (m_socketOption->getSocketType() == ESocketType::TCP) {
        if (m_socketOption->getTcpNoDelay()) {
            // disable Nagle algorithm
            int tcpNoDelay = 1;
            setsockopt(m_socketFd, IPPROTO_TCP, TCP_NODELAY, (char *)&tcpNoDelay, sizeof(int));
        }
        if (m_socketOption->getKeepAlive()) {
            int keepalive = 1;
            setsockopt(m_socketFd, SOL_SOCKET, SO_KEEPALIVE, (char *)&keepalive, sizeof(int));
        }
    }
    /*
    if (m_fast) {
        int fast = 6;
        // https://github.com/shadowsocks/shadowsocks/wiki/TCP-Fast-Open
        setsockopt(fd, SOL_TCP, TCP_FASTOPEN, (char *)&fast, sizeof(int));
    }
    // TCP_DEFER_ACCEPT
    */
}

bool Socket::bindAddress() {
    if (m_socketState != SocketState::CREATE && m_socketFd > 0) {
        return false;
    }
    struct sockaddr_in srv;
    auto afInet = m_socketOption->getSocketDomain();
    srv.sin_family = afInet;
    if ("0.0.0.0" == m_ip) {
        srv.sin_addr.s_addr = INADDR_ANY;
    } else {
        srv.sin_addr.s_addr = ::inet_addr(m_ip.c_str());
    }
    srv.sin_port = htons(m_port);
    int ret = ::bind(m_socketFd, (struct sockaddr*)&srv, sizeof(sockaddr));
    if (ret < 0) {
        return false;
    }
    return true;
}

bool Socket::listen(int32 backlog) {
    auto ret = ::listen(m_socketFd, backlog);
    if (ret < 0) {
        std::cout << "listn failed\n";
        return false;
    }
    return true;
}

std::shared_ptr<ISocket> Socket::accept() {
    auto socket = std::make_shared<Socket>();
    socket->setSocketOption(m_socketOption);
    if (!socket->accept(m_socketFd)) {
        return nullptr;
    }
    return socket;
}

bool Socket::accept(SOCKET acceptFd) {
    struct sockaddr clientAddr;
    socklen_t in_len;
    in_len = sizeof(clientAddr);
    int type = SOCK_CLOEXEC | (m_socketOption->getNonBlock() ? SOCK_NONBLOCK : 0x00);
    m_socketFd = ::accept4(acceptFd, &clientAddr, &in_len, type);
    if (m_socketFd < 0) {
        std::cout << std::this_thread::get_id() << " accept fd error: " << strerror(errno) << std::endl;
        return false;
        // LOG strerror(errno);
    }
    // get remote ip and prot;
    sockaddr_in sin;
    memcpy(&sin, &clientAddr, sizeof(sin));
    setIp(inet_ntoa(sin.sin_addr));
    setPort(sin.sin_port);
    setSocketFlags();
    return true;
}

bool Socket::connect() {
    if (m_socketState != SocketState::CREATE || m_socketFd < 0) {
        std::cout << "the connection failed\n";
        return false;
    }
    if (m_socketOption->getSocketType() != ESocketType::TCP) {
        std::cout << "the socket type must tcp\n";
        return false;
    }
    struct sockaddr_in clientAddr;
    auto afInet = m_socketOption->getSocketDomain();
    clientAddr.sin_family = afInet;
    clientAddr.sin_port = htons(m_port);
    clientAddr.sin_addr.s_addr = inet_addr(m_ip.c_str());
    do {
        int ret = ::connect(m_socketFd, (struct sockaddr *)&clientAddr, sizeof(struct sockaddr));
        if (ret != 0) {
            int32 errcode = errno;
            if (errcode == EINPROGRESS || errcode == EALREADY) {
                continue;
            } else {
                std::cout << "errno: " << errno << " " << strerror(errno) << std::endl;
                abort();
                return false;
            }
        }
        break;
    } while(true);
    return true;;
}

int32 Socket::read(std::string &data) {
    // see man recv.
    char ioBuf[2048];
    int32 bufsize = 2048;
    int32 readLen = 0;
    do {
		int32 ret = ::recv(getFd(), ioBuf, bufsize, MSG_HYPER);
		if (ret > 0) {
			readLen += ret;
			bufsize -= ret;
		} else if (ret == 0) {
			/*Socket closed*/
			return SOCKET_CLOSE;
		} else if (ret == -1) {
			int32 errcode = errno;
			if (errcode == EINTR) {
				continue;
			} else if (errcode == EAGAIN || errcode == EWOULDBLOCK) {
				/*No data can be read*/
				break;
			} else {
                // print log 
				/*Unexpected error, Socket closed*/
				return SOCKET_CLOSE;
			}
		}
	} while (bufsize > 0);
    ioBuf[readLen] = '\0';
    data.append(ioBuf, readLen);
	return readLen;
}

int32 Socket::write(const std::string &data) {
    const char *buf = data.c_str();
    int32 bufSize = data.size();
    int32 writeLen = 0;
    do {
        int32 ret = ::send(getFd(), (buf + writeLen), bufSize, MSG_HYPER);
        if (ret >= 0) {
            writeLen += ret;
            bufSize -= ret;
        } else if (ret == -1) {
            int32 errcode =  errno;
            if (errcode == EINTR) {
                continue;
            } else if (EAGAIN == errcode || EWOULDBLOCK == errcode) {
                return writeLen;
            }
            /* Socket closed*/
            return SOCKET_CLOSE;
        }
        if (bufSize == 0) {
            break;
        }
    } while (true);
    return writeLen;
}
}
}