#pragma once

#include <sys/epoll.h>
namespace hyper {
namespace base {
    #define HYPER_READ      EPOLLIN
    #define HYPER_PRI       EPOLLPRI
    #define HYPER_WRITE     EPOLLOUT
    #define HYPER_RDNORM    EPOLLRDNORM
    #define HYPER_RDBAND    EPOLLRDBAND
    #define HYPER_WRNORM    EPOLLWRNORM
    #define HYPER_WRBAND    EPOLLWRBAND
    #define HYPER_MSG       EPOLLMSG
    #define HYPER_ERR       EPOLLERR
    // EPOLLHUP see the ticke(https://elixir.bootlin.com/linux/v4.19/source/net/ipv4/tcp.c#L524)
    #define HYPER_HUP       EPOLLHUP
    #define HYPER_RDHUP     EPOLLRDHUP
    #define HYPER_EXCLUSIVE EPOLLEXCLUSIVE
    #define HYPER_WAKEUP    EPOLLWAKEUP
    #define HYPER_ONESHOT   EPOLLONESHOT
    #define HYPER_ET        EPOLLET
    #define HYPER_LT        0x0

    #define HYPER_OP_ADD       EPOLL_CTL_ADD
    #define HYPER_OP_DEL       EPOLL_CTL_DEL
    #define HYPER_OP_MOD       EPOLL_CTL_MOD
}
}
