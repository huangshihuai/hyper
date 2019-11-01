#pragma once

#include <string>
#include <memory>
#include "base/btype.h"
#include "interface/i_event_loop.h"
#include "base/e_socket.h"
#include "base/f_factory.h"
#include "interface/i_options.h"
#include "interface/i_socket_option.h"

namespace hyper {
namespace interface {

using namespace hyper::base;

class IAcceptor {
public:
    IAcceptor() { };
    virtual ~IAcceptor() { };
    virtual bool startListen() = 0;
    virtual void setDispatch() = 0;
    virtual void setConnectorFactory(f_connectFactory connectFactory) = 0;
};
}
}