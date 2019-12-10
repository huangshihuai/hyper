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
    IOBucket();
    IOBucket(char *data_in, uint32 data_capacity);
    int32 peek(uint8 *buf, int32 len);
    char *write() { return (m_data + m_writerIndex); };
    uint32 getWriteSpace() const { return m_capacity - m_writerIndex; };
    char *read() { return (m_data + m_readerIndex); };
    uint32 getReadSpace() const { return m_writerIndex - m_readerIndex; };
    bool isFull() const { return m_capacity == m_readerIndex; };
    void clear() { m_readerIndex = m_writerIndex = 0; };
    std::string toString() const;
    void discardReadBytes();
    uint32 getRelayWriteSpace();
    uint32 m_capacity;
    uint32 m_readerIndex;
    uint32 m_writerIndex;
    char *m_data;
};



}
}
}