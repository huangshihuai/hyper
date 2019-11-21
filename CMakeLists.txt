cmake_minimum_required(VERSION 3.1)
project(hyper)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

include_directories(".")

add_subdirectory(net)

add_executable(echo_server "example/echo_server.cpp")
TARGET_LINK_LIBRARIES(echo_server net pthread)

add_executable(echo_client "example/echo_client.cpp")
TARGET_LINK_LIBRARIES(echo_client net pthread)

add_executable(echo_multi_server "example/echo_multi_server.cpp")
TARGET_LINK_LIBRARIES(echo_multi_server net pthread)

#add_library(hyper NET_SOURCE)