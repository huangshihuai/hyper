#pragma once
#include "net/common/io_bucket.h"

namespace hyper {
namespace net {
namespace common {

class IOBuffer {
public:
    
private:
    IOBucket *m_head;
    IOBucket *m_tail;
    IOBucket *m_writePos;
    IOBucket *m_readPos;
};

}
}
}