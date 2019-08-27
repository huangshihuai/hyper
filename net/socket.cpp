#include "net/socket.h"
#include <sys/ioctl.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <cstring>
#include <string.h>
#include <iostream>

namespace hyper {
namespace net{
Socket::Socket() {
    m_keepAlive = true;
    m_reuseAddr = true;
    m_reusePort = true;
    m_tcpNoDelay = false;
    m_socketState = SocketState::NONE;
    m_socketModel = ESocketModel::TCP;
    m_socketFd = -1;
}
Socket::~Socket() {
}

bool Socket::getTcpInfo(struct tcp_info* info) const {
    return true;
}

bool Socket::createSocket() {
    if (m_socketModel != SOCK_STREAM && m_socketModel != SOCK_DGRAM) {
        std::cout << "the socket model failed: " << m_socketModel << std::endl;;
        return false;
    }
    SOCKET fd = 0;
    fd = ::socket(AF_INET, m_socketModel | SOCK_CLOEXEC | SOCK_NONBLOCK, IPPROTO_TCP);
    if (fd < 0) {
        std::cout << "errno" << errno << strerror(errno) << std::endl;
        return false;
    }
    fd = setSocketOptional(fd);
    /*
    unsigned long nonblocking = 1;
    ioctl(fd, FIONBIO, (void *)&nonblocking);
    */
    m_socketFd = fd;
    m_socketState = SocketState::CREATE;
    return true;
}

SOCKET Socket::setSocketOptional(SOCKET fd) {
    if (m_reuseAddr) {
        int reuseAddr = 1;
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuseAddr, sizeof(int));
    }
    if (m_reusePort) {
        int reusePort = 1;
        setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, (char *)&reusePort, sizeof(int));
    }
    if (m_tcpNoDelay && m_socketModel == SOCK_STREAM) {
        // disable Nagle algorithm
        int tcpNoDelay = 1;
        setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *)&tcpNoDelay, sizeof(int));
    }
    if (m_keepAlive) {
        int keepalive = 1;
        setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&keepalive, sizeof(int));
    }
    return fd;
}

bool Socket::bindAddress() {
    if (m_socketState != SocketState::CREATE && m_socketFd > 0) {
        return false;
    }
    struct sockaddr_in srv;
    srv.sin_family = AF_INET;
    srv.sin_addr.s_addr = ::inet_addr(m_ip.c_str());
    std::cout << "bindAddress: " << m_port << std::endl;
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
    struct sockaddr clientAddr;
    socklen_t in_len;
    in_len = sizeof(clientAddr);
    auto fd = ::accept4(m_socketFd, &clientAddr, &in_len, SOCK_CLOEXEC | SOCK_NONBLOCK);
    if (fd < 0) {
        std::cout << "accept fd error: " << strerror(errno) << std::endl;
        return nullptr;
        // LOG strerror(errno);
    }
    std::shared_ptr<ISocket> socket = std::make_shared<Socket>();
    // get remote ip and prot;
    sockaddr_in sin;
    memcpy(&sin, &clientAddr, sizeof(sin));
    socket->setIp(inet_ntoa(sin.sin_addr));
    socket->setPort(sin.sin_port);
    fd = socket->setSocketOptional(fd);
    socket->setSocketFd(fd);
    return socket;
}

bool Socket::connect() {
    if (m_socketState != SocketState::CREATE && m_socketFd > 0) {
        std::cout << "the connection failed\n";
        return false;
    }
    if (m_socketModel != SOCK_STREAM) {
        std::cout << "the socket type must tcp\n";
        return false;
    }
    int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(m_port);
    clientAddr.sin_addr.s_addr = inet_addr(m_ip.c_str());
    int ret = ::connect(fd, (struct sockaddr *)&clientAddr, sizeof(struct sockaddr));
    if (0 != ret) {
        std::cout << errno << strerror(errno) << std::endl;
        return false;
    }
    m_socketFd = fd;
    return true;;
}

int32 Socket::read(std::string &data) {
    char ioBuf[2048];
    int32 bufsize = 2048;
    int32 readLen = 0;
    do {
		int32 ret = recv(getFd(), ioBuf, bufsize, 0);
		if (ret > 0) {
			readLen += ret;
			bufsize -= ret;
		}
		else if (ret == 0) {
			/*Socket closed*/
			return -1;
		}
		else if (ret == -1) {
			int32 errcode = errno;
			if (errcode == EINTR) {
				continue;
			}
			else if (errcode == EAGAIN 
				|| errcode == EWOULDBLOCK) {
				/*No data can be read*/
				break;
			}
			else {
				/*Unexpected error*/
				return -1;
			}
		}
	}while(bufsize > 0);
    data = ioBuf;
	return readLen;
}

}
}