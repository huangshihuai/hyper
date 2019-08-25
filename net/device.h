#ifndef HYPER_NET_DEVICE_H
#define HYPER_NET_DEVICE_H
#include <unistd.h>
#include <sys/socket.h>
#include <string>

#include "interface/i_device.h"

#include "base/btype.h"

namespace hyper {
namespace net {
using namespace hyper::base;
using namespace hyper::interface;

class Device : public IDevice {
public:
    Device();
    virtual ~Device();
    int32 handleRead() override { return 0; };
    int32 handleWrite() override { return 0; };
    int32 recycle() override { return 0; };
    int32 onFail() override { return recycle(); }
    void setFd(SOCKET fd) override { m_fd = fd; }
    SOCKET getFd() const override { return m_fd; }
    int32 addNotify(int32 ev_type) override { return 0; };
    int32 clearNotify() override { return 0; };
    int32 modifyNotify(int32 ev_type) override { return 0; };
    int32 getNotify() const override { return m_noti; }
    int32 shutDownRead() override { return shutdown(m_fd, 0); }
    int32 shutDownWrite() override { return shutdown(m_fd, 1); }
    int32 setAddr(const std::string& addr, int32 port) override {
        m_addr = addr;
        m_port = port;
        return 0;
    }
    int32 getAddr(std::string& addr, int32 &port) const override {
        addr = m_addr;
        port = m_port;
        return 0;
    }
    inline const std::string& getIp() const override { return m_addr; }
    inline int32 getPort() const override { return m_port; }
    inline int32 getEvents() const override { return m_events; }
private:
    int32 clear() override { return 0; };

private:
    SOCKET  m_fd;
    std::string m_addr;
    int32 m_port;
    int32 m_noti;
    int32 m_events;
};
}
}
#endif // HYPER_NET_DEVICE_H