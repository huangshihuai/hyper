#include "net/socket.h"
#include "base/btype.h"
#include "base/macro.h"
#include <memory>
#include <iostream>
#include <chrono>
#include <thread>

using namespace hyper::net;
int main() {
    auto socket = std::make_shared<Socket>();
    socket->setPort(2375);
    socket->setIp("0.0.0.0");
    HYPER_COMPARE(socket->createSocket(), true, !=, return 1,
                "create socket failed");
    HYPER_COMPARE(socket->connect(), true, !=, return 1,
                "connect failed");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    socket->shutdown();
    return 0;
}