#include "net/common/io_bucket.h"
#include <iostream>
#include <string>
// 还未支持 Gtest
using namespace std;
int main()
{
    auto ioBucket = hyper::net::common::IOBucket::create(IO_BUCKET_ALIGN_SIZE);
    std::cout << ioBucket->capacity << endl;
    cout << ioBucket->isFull() << endl;
    cout << ioBucket->writableSize() << endl;
    cout << ioBucket->realFreeSize() << endl;
    char c[1];
    for (uint32 index = 0; index < ioBucket->capacity; ++index) {
        auto i = index % 26;
        c[0] = 'a' + i;
        ioBucket->write(c, 1);
    }

    cout << ioBucket->isFull() << endl;
    cout << ioBucket->writableSize() << endl;
    cout << ioBucket->realFreeSize() << endl;
    cout << ioBucket->readIndex << endl;
    cout << ioBucket->writeIndex << endl;
    string realStr = ioBucket->toString();
    cout << realStr << endl;
    char buf[IO_BUCKET_ALIGN_SIZE];
    auto realLen = ioBucket->read(buf, IO_BUCKET_ALIGN_SIZE);
    cout << "realLen: " << realLen << endl;
    cout << ioBucket->isFull() << endl;
    cout << ioBucket->writableSize() << endl;
    cout << ioBucket->realFreeSize() << endl;
    cout << ioBucket->readIndex << endl;
    cout << ioBucket->writeIndex << endl;
    ioBucket->adjustDiscardableBytes();
    cout << ioBucket->readIndex << endl;
    cout << ioBucket->writeIndex << endl;
    cout << ioBucket->writableSize() << endl;
    cout << ioBucket->realFreeSize() << endl;
    cout << "-------------\n";
    string out(buf, realLen);
    out.append(ioBucket->toString());
    if (realStr == out) {
        cout << "success\n";
    } else {
        cout << "error\n";
    }
    cout << out << endl;
    hyper::net::common::IOBucket::destroy(&ioBucket);
    ioBucket = nullptr;
    return 0;
}