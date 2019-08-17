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

class Device : public IDevice {
public:
    Device();
    virtual ~Device();
    virtual int32 handleRead(IEventLoop* l);
    virtual int32 handleWrite(IEventLoop* l);
    virtual int32 recycle();
    virtual int32 onFail(){ return recycle(); }
    virtual void setFd(SOCKET fd){ m_fd = fd; }
    virtual SOCKET getFd() const{ return m_fd; }
    virtual int32 addNotify(IEventLoop* l, int32 ev_type);
    virtual int32 clearNotify(IEventLoop* l);
    virtual int32 modifyNotify(IEventLoop* l, int32 ev_type);
    virtual int32 getNotify() const{ return m_noti; }
    virtual int32 shutDownRead(){ return shutdown(m_fd, 0); }
    virtual int32 shutDownWrite(){ return shutdown(m_fd, 1); }
    virtual int32 setAddr(const std::string& addr, int32 port){
        m_addr = addr;
        m_port = port;
        return 0;
    }
    virtual int32 getAddr(std::string& addr, int32 &port) const{
        addr = m_addr;
        port = m_port;
        return 0;
    }
    virtual const std::string& getIp() const{
        return m_addr;
    }
    virtual int32 getPort() const{
        return m_port;
    }
private:
    virtual int32 clear();

private:
    SOCKET  m_fd;
    std::string m_addr;
    int32 m_port;
    int32 m_noti;
};
}
}
#endif // HYPER_NET_DEVICE_H