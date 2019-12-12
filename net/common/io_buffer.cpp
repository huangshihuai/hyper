#include "net/common/io_buffer.h"

namespace hyper {
namespace net {
namespace common {

IOBuffer::IOBuffer() {
    m_readBucket = createIOBucket(IO_BUCKET_ALIGN_SIZE);
    m_writeBucket = m_readBucket;
}

IOBuffer::~IOBuffer() {
    //
}



}
}
}