#ifndef HYPER_INTERFACE_I_SERVER_H
#define HYPER_INTERFACE_I_SERVER_H
#include <map>
#include <string>
#include <functional>
#include <algorithm>
namespace hyper {
namespace interface {

class IServer {
public:
    IServer() {};
    virtual ~IServer() {};
    virtual const std::map<std::string, std::function<void (std::string, std::string)>> &getBriging() = 0;
};
}
}
#endif // HYPER_INTERFACE_I_SERVER_H