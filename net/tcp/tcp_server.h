#ifndef HYPER_NET_TCP_TCP_SERVER_H
#define HYPER_NET_TCP_TCP_SERVER_H
#include "interface/i_net_server.h"

namespace hyper {
namespace net {

using namespace interface;

class TcpServer : public INetServer {
public:
    TcpServer();
    ~TcpServer();
};

}
}

#endif // HYPER_NET_TCP_TCP_SERVER_H