#pragma once
#include <string>
#include "base/btype.h"

using namespace hyper::base;

namespace hyper {
namespace net {
namespace common {

/* memory alignment */
#define IO_BUCKET_ALIGN_SIZE 8192

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
    uint32 m_capacity;
    uint32 m_readerIndex;
    uint32 m_writerIndex;
    char *data;
    IOBucket(char *data_in, uint32 data_size);
    int32 peek(uint8 *buf, int32 len);
    int32 write(const uint8 *buf, int32 len);
    int32 read(uint8 *buf, int32 len);
    bool isFull() const { return true; };
    void clear();
    std::string toString() const;
    void discardReadBytes();
    uint32 getWriteSpace();
    uint32 getReadSpace();
    uint32 getRlayWriteSpace();
};



}
}
}