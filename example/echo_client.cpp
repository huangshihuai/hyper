#include "net/socket.h"
#include "base/btype.h"
#include "base/macro.h"
#include "net/socket_option.h"
#include <memory>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

using namespace hyper::net;

int doWrite(std::shared_ptr<ISocket> socket, std::string write) {
    size_t size = 0;
    do {
        size = socket->write(write);
        if (size < 0) {
            return -1;
        }
        if (size == write.size()) {
            return 0;
        }
        write = write.substr(0, size);
    } while(true);
}

int doRead(std::shared_ptr<ISocket> socket) {
    std::string readBuf;
    int32 readSize = 0;
    do {
        readSize = socket->read(readBuf);
        if (readSize < 0) {
            return -1;
        }
        if (readSize > 0) {
            break;
        }
    } while(true);
    std::cout << readBuf << std::endl;
    return readSize;
}

void testMessage() {
    auto socketOption = std::make_shared<SocketOption>();
    socketOption->setKeepAlive(true);
    socketOption->setReuseAddr(true);
    socketOption->setReusePort(true);
    socketOption->setTcpNoDelay(true);
    socketOption->setNonBlock(true);
    auto socket = std::make_shared<Socket>();
    socket->setPort(2375);
    socket->setIp("0.0.0.0");
    socket->setSocketOption(socketOption);
    HYPER_COMPARE(socket->create(), true, !=, return,
                "create socket failed");
    HYPER_COMPARE(socket->connect(), true, !=, return,
                "connect failed");
    std::string write = "say hello";
    int32 index = 1;
    do {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        auto buf = write + std::to_string(index);
        ++index;
        if (-1 == doWrite(socket, buf)) {
            break;
        }
        if (-1 == doRead(socket)) {
            break;
        }
    } while(true);
    socket->shutdown();
}

int main() {
    std::vector<std::thread> threads;
    for (uint32_t i = 0; i < 4; ++i) {
        std::thread con(testMessage);
        threads.push_back(std::move(con));
    }

    for (auto &con : threads) {
        con.join();
    }
}