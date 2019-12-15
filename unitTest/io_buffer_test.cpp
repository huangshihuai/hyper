#include "net/common/io_buffer.h"
#include <iostream>
#include <string>
using namespace std;
int main()
{
    hyper::net::common::IOBuffer ioBuffer;
    char str[IO_BUCKET_ALIGN_SIZE];
    auto readLen = ioBuffer.read(str, IO_BUCKET_ALIGN_SIZE);
    cout << readLen << endl;
    ioBuffer.write("1234567890", 10);
    readLen = ioBuffer.read(str, 10);
    cout << readLen << endl;
    cout << str << endl;
    readLen = ioBuffer.read(str, IO_BUCKET_ALIGN_SIZE);
    cout << readLen << endl;

    char c[1];
    uint32 writeSize = 0;
    string writeBuff;
    for (uint32 index = 0; index < 4 * IO_BUCKET_ALIGN_SIZE; ++index) {
        auto i = index % 26;
        c[0] = 'a' + i;
        writeBuff.append(c, 1);
        writeSize += ioBuffer.write(c, 1);
    }

    uint32 readSize = 0;
    string readBuff;
    for (uint32 index = 1; index; ++index) {
        auto len = ioBuffer.read(str, index);
        if (len <= 0) {
            break;
        }
        readBuff.append(str, len);
        readSize += len;
    }
    cout << writeSize << endl;
    cout << readSize << endl;
    if (readBuff == writeBuff) {
        cout << writeBuff << endl;
        cout << "success\n";
    } else {
        cout << "error\n";
    }
    return 0;
}