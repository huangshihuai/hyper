#include "protocol.h"

namespace hyper {
namespace net {

Protocol::Protocol() {
}

Protocol::~Protocol() {
}

bool Protocol::packStream() {
    return true;
}

bool Protocol::unPackStream() {
    return true;
}

}
}