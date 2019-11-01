#include "net/socket.h"
#include "base/btype.h"
#include "base/macro.h"
#include "net/socket_option.h"
#include "net/common/endian.h"
#include "net/protocols/protocols.h"
#include "net/protocols/im.h"
#include <memory>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <cstring>

using namespace hyper::net;
#define MAX_THREAD 10

int doWrite(std::shared_ptr<ISocket> socket, std::string responseData) {
    size_t size = 0;
    do {
        std::string responseReady;
        auto response = protocols::im::Im::createMessage();
        auto imMessage = dynamic_cast<protocols::im::ImMessage *>(response);
        imMessage->msg = responseData;
        protocols::im::Im::serialization(responseReady, imMessage);
        protocols::im::Im::destroyMessage(response);
        size = socket->write(responseReady);
        if (size < 0) {
            return size;
        }
        if (size == responseReady.size()) {
            return 0;
        }
        responseReady = responseReady.substr(0, size);
    } while(true);
}

int doRead(std::shared_ptr<ISocket> socket) {
    std::string readBuf;
    int32 readSize = 0;
    do {
        readSize = socket->read(readBuf);
        if (readSize < 0) {
            return readSize;
        }
        if (readSize > 0) {
            break;
        }
    } while(true);
    auto request = protocols::im::Im::createMessage();
    protocols::im::Im::unserialization(readBuf, request);
    auto imMessage = dynamic_cast<protocols::im::ImMessage *>(request);
    std::cout << "server request: " << imMessage->msg << std::endl;
    protocols::im::Im::destroyMessage(request);
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
    std::string write = "{\"name\":\"client\",\"age\":";
    int32 index = 1;
    do {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        auto buf = write + std::to_string(index) + "}";
        ++index;
        if (SOCKET_CLOSE == doWrite(socket, buf)) {
            break;
        }
        if (SOCKET_CLOSE == doRead(socket)) {
            break;
        }
    } while(true);
    socket->close();
}

int main() {
    std::vector<std::thread> threads;
    for (uint32_t i = 0; i < MAX_THREAD; ++i) {
        std::thread con(testMessage);
        threads.push_back(std::move(con));
    }

    for (auto &con : threads) {
        con.join();
    }
}