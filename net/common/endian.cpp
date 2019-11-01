
#include "net/common/endian.h"

#include <netinet/in.h>

namespace hyper {
namespace net {
namespace common {

base::uint64 ntohll(base::uint64 val) {
    if (__BYTE_ORDER == __LITTLE_ENDIAN) {
        return (((unsigned long long )::htonl((int)((val << 32) >> 32))) << 32) | (unsigned int)htonl((int)(val >> 32));
    } else if (__BYTE_ORDER == __BIG_ENDIAN) {
        return val;
    }
}
 
base::uint64 htonll(base::uint64  val) {
    if (__BYTE_ORDER == __LITTLE_ENDIAN) {
        return (((unsigned long long )::htonl((int)((val << 32) >> 32))) << 32) | (unsigned int)htonl((int)(val >> 32));
    } else if (__BYTE_ORDER == __BIG_ENDIAN) {
        return val;
    }
}

}
}
}