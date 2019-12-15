#pragma once
#include <string>
#include "base/btype.h"

using namespace hyper::base;

namespace hyper {
namespace net {
namespace common {

/* memory alignment */
#define IO_BUCKET_ALIGN_SIZE 1024

/*
+-------------------+------------------+------------------------+
| discardable bytes |  readable bytes  |      writable bytes    |
+-------------------+------------------+------------------------+
|                   |                  |                        |
| 0     <=     readIndex   <=   writeIndex    <=    capacity |
+---------------------------------------------------------------+
*/
// memory alignment //
struct IOBucket {
    inline static uint32 alignmentSize(uint32 size);
    static IOBucket* create(uint32 size);
    static void destroy(IOBucket **ioBucket);

    uint32 read(char *buf, const uint32 len);
    uint32 write(const char *buf, const uint32 len);
    void adjustDiscardableBytes();
    inline bool isFull() const { return capacity == writeIndex; };
    // TODO: writable space size
    inline uint32 writableSize() const { return capacity - writeIndex; };
    inline uint32 realFreeSize() const { return readIndex + capacity - writeIndex; };
    inline uint32 readableSize() const { return writeIndex - readIndex; }
    inline uint32 discardableSize() const { return readIndex; };
    inline void clear() { readIndex = writeIndex = 0; };
    inline std::string toString() const { return std::string(data + readIndex, writeIndex - readIndex); };
    uint32 capacity;
    uint32 readIndex;
    uint32 writeIndex;
    IOBucket* next;
    char *data;
};

}
}
}