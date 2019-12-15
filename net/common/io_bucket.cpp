#include "net/common/io_bucket.h"
#include <string.h>

namespace hyper {
namespace net {
namespace common {
    
inline uint32 IOBucket::alignmentSize(uint32 size) {
    return IO_BUCKET_ALIGN_SIZE + size - size % IO_BUCKET_ALIGN_SIZE;
}

IOBucket* IOBucket::create(uint32 size) {
    uint32 alignSize = IOBucket::alignmentSize(size + sizeof(IOBucket));
    //char *buf = (char*)malloc(alignSize * sizeof(char));
    char *buf = new char[alignSize];
    IOBucket* bucket = (IOBucket*)(buf);
    bucket->writeIndex = 0;
    bucket->readIndex = 0;
    bucket->capacity = alignSize - sizeof(IOBucket);
    bucket->data = buf + sizeof(IOBucket);
    bucket->next = nullptr;
    return bucket;
}

void IOBucket::destroy(IOBucket **ioBucket) {
    char *buf = (char *)(*ioBucket);
    delete[] buf;
    (*ioBucket) = nullptr;
}

void IOBucket::adjustDiscardableBytes() {
    auto len = writeIndex - readIndex;
    ::memmove(data, (data + readIndex), len);
    readIndex = 0;
    writeIndex = len;
}

uint32 IOBucket::write(const char *buf, const uint32 len) {
    uint32 realLen = capacity - writeIndex;
    if (len < realLen) {
        realLen = len;
    }
    ::memmove((data + writeIndex), buf, realLen);
    writeIndex += realLen;
    return realLen;
}

uint32 IOBucket::read(char *buf, uint32 len) {
    uint32 realLen = writeIndex - readIndex;
    if (len < writeIndex - readIndex) {
        realLen = len;
    }
    ::memmove(buf, (data + readIndex), realLen);
    readIndex += realLen;
    return realLen;
}


}
}
}