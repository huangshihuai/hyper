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
/*memory alignment*/
struct IOBucket {
    uint32 m_capacity;
    uint32 m_read;
    uint32 m_write;
    char *buf;
    uint32 getFreeSpace() const() { return m_capacity - m_write; };
    uint32 write(const uint8* data, uint32 length);
    uint32 read(uint8* data, uint32 );
};



}
}
}