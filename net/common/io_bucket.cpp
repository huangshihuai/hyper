#include "net/common/io_bucket.h"

namespace hyper {
namespace net {
namespace common {
    
inline uint32  alignmentSize(uint32 size) {
    return IO_BUCKET_ALIGN_SIZE + size - size % IO_BUCKET_ALIGN_SIZE;
}

IOBucket* createIOBucket(uint32 size) {
    uint32 alignSize = alignmentSize(size + sizeof(IOBucket));
    char *buf = (char*)malloc(alignSize * sizeof(char));
    IOBucket* bucket = (IOBucket*)(buf);
    bucket->writerIndex = 0;
    bucket->readerIndex = 0;
    bucket->capacity = alignSize - sizeof(IOBucket);
    bucket->data = buf + sizeof(IOBucket);
    bucket->data = nullptr;
    return bucket;
}



}
}
}