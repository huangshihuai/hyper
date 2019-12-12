#pragma once
#include <queue>
#include "net/common/io_bucket.h"

namespace hyper {
namespace net {
namespace common {

class IOBuffer {
public:
    explicit IOBuffer();
    ~IOBuffer();
private:
    IOBucket* m_readBucket;
    IOBucket* m_writeBucket;
};

}
}
}