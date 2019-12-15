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
    uint32 write(const char * const buf, const uint32 len);
    uint32 read(char * const buf, const uint32 len);
    uint32 readableSize() const { return m_readableSize; };
private:
    void destroyAllIOBucket();
    void extend();
    void headMoveToTail();
private:
    uint32 m_readableSize;
    uint32 capacity;
    IOBucket* m_head; // read handle
    IOBucket* m_pos;  // write handle
    IOBucket* m_tail; //
};

}
}
}