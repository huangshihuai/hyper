#include "net/common/io_bucket.h"

namespace hyper {
namespace net {
namespace common {
IOBucket::IOBucket() : m_capacity(0) , m_readerIndex(0)
                        , m_writerIndex(0), m_data(nullptr) {
}
IOBucket::IOBucket(char *data_in, uint32 data_capacity) : m_capacity(data_capacity) , m_readerIndex(0)
                        , m_writerIndex(0), m_data(data_in) {
}



}
}
}