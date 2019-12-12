#pragma once
#include <string>
#include "base/btype.h"

using namespace hyper::base;

namespace hyper {
namespace net {
namespace common {

/* memory alignment */
#define IO_BUCKET_ALIGN_SIZE 2048

/*
+-------------------+------------------+------------------------+
| discardable bytes |  readable bytes  |      writable bytes    |
+-------------------+------------------+------------------------+
|                   |                  |                        |
| 0     <=     readerIndex   <=   writerIndex    <=    capacity |
+---------------------------------------------------------------+
*/
// memory alignment //
struct IOBucket {
    uint32 peek(uint8 *buf, int32 len);
    char *write() { return (data + writerIndex); };
    uint32 getWriteSpace() const { return capacity - writerIndex; };
    char *read() { return (data + readerIndex); };
    uint32 getReadSpace() const { return writerIndex - readerIndex; };
    bool isFull() const { return capacity == readerIndex; };
    void clear() { readerIndex = writerIndex = 0; };
    std::string toString() const;
    void discardReadBytes();
    uint32 getRelayWriteSpace();
    uint32 capacity;
    uint32 readerIndex;
    uint32 writerIndex;
    IOBucket *next;
    char *data;
};

inline uint32  alignmentSize(uint32 size);
IOBucket* createIOBucket(uint32 size);


}
}
}