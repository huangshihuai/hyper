#ifndef HYPER_BASE_F_FACTORY_H
#define HYPER_BASE_F_FACTORY_H
#include <memory>
#include <string>
#include <functional>
#include "interface/i_connection.h"

namespace hyper {
namespace base {
using namespace::hyper::interface;
typedef std::function<std::shared_ptr<IConnection>()> f_connectFactory;
typedef std::function<void(const std::string &onRequestData)> f_onRequest;
}
}
#endif // HYPER_BASE_F_FACTORY_H