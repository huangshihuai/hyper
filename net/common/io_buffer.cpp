#include "net/common/io_buffer.h"
#include "net/common/io_bucket.h"

namespace hyper {
namespace net {
namespace common {

IOBuffer::IOBuffer() {
    m_head = IOBucket::create(IO_BUCKET_ALIGN_SIZE);
    m_tail = m_pos = m_head;
	m_readableSize = 0;
}

IOBuffer::~IOBuffer() {
	destroyAllIOBucket();
}

void IOBuffer::destroyAllIOBucket() {
	IOBucket* pos = m_head;
	IOBucket* handle = nullptr;
	for (;pos != nullptr; ) {
		handle = pos;
		pos = handle->next;
		IOBucket::destroy(&handle);
	}
	m_head = nullptr;
	m_pos = nullptr;
	m_tail = nullptr;
}

uint32 IOBuffer::write(const char * const buf, const uint32 len) {
    uint32 appendLen = 0;
    IOBucket* pos = m_pos;
    while (len > appendLen && pos) {
		if (pos->isFull()) {
			extend();
			pos = m_pos; 
		}
		appendLen += pos->write(buf + appendLen, len - appendLen);
    }
	m_readableSize += appendLen;
	return appendLen;
}

uint32 IOBuffer::read(char * const buf, const uint32 len) {
	uint32 totalReadLen = 0;
	IOBucket* pos = m_head;
	while (len > totalReadLen && pos) {
		auto readLen = pos->read(buf, len - totalReadLen);
		if (readLen <= 0) {
			break;
		}
		totalReadLen += readLen;
		if (0 == pos->readableSize()) {
			headMoveToTail();
		}
	}
	m_readableSize -= totalReadLen;
	return totalReadLen;
}

void IOBuffer::extend() {
	if (m_pos == m_tail) {
		// new throw.
		auto ioBucket = IOBucket::create(IO_BUCKET_ALIGN_SIZE);
		m_tail->next = ioBucket;
		m_tail = m_tail->next;
	}
	m_pos = m_pos->next;
}

void IOBuffer::headMoveToTail() {
	if (m_head->next == nullptr) {
		return;
	}
	auto pos = m_head;
	m_head = m_head->next;
	m_tail->next = pos;
	m_tail = m_tail->next;
	m_tail->next = nullptr;
}

}
}
}