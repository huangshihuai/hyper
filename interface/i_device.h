#ifndef HYPER_INTERFACE_I_DEVICE_H
#define HYPER_INTERFACE_I_DEVICE_H
#include <unistd.h>
#include <string>
#include "base/btype.h"

namespace hyper {
namespace interface {
using namespace hyper::base;
class IDevice {
public:
	IDevice() { }
	virtual ~IDevice() { };
	virtual int32 handleRead() = 0;
	virtual int32 handleWrite() = 0;
	virtual int32 recycle() = 0;
	virtual int32 onFail() = 0;
	virtual void setFd(SOCKET fd) = 0;
	virtual SOCKET getFd() const = 0;
	virtual int32 addNotify(int32 ev_type) = 0;
	virtual int32 clearNotify() = 0;
	virtual int32 modifyNotify(int32 ev_type) = 0;
	virtual int32 getNotify() const = 0;
	virtual int32 shutDownRead() = 0;
	virtual int32 shutDownWrite() = 0;
	virtual int32 setAddr(const std::string& addr, int32 port) = 0;
	virtual int32 getAddr(std::string& addr, int32 &port) const = 0;
	virtual const std::string& getIp() const = 0;
	virtual int32 getPort() const = 0;
	virtual int32 getEvents() const = 0;
private:
	virtual int32 clear() = 0;
};
}
}
#endif // HYPER_INTERFACE_I_DEVICE_H