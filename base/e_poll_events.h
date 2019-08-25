#ifndef HYPER_BASE_E_POLL_EVENTS_H
#define HYPER_BASE_E_POLL_EVENTS_H
#include <sys/epoll.h>
namespace hyper {
namespace base {
#define READ_EVENT EPOLLIN
#define WRITE_EVENT EPOLLOUT
}
}
#endif // HYPER_BASE_E_POLL_EVENTS_H