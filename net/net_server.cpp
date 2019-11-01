#include <iostream>
#include <chrono>
#include <thread>
#include <sys/signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/fcntl.h>

#include "base/macro.h"
#include "net/net_server.h"
#include "net/acceptor.h"
#include "event_loop_thread.h"
#include "base/e_poll_events.h"
#include "net/service/net_model_factory.h"

using namespace hyper::net::service;

namespace hyper {
namespace net {
    bool g_quit = false;

    NetServer::NetServer() {
    }

    NetServer::~NetServer() {
    }

    bool NetServer::start() {
        if (!init()) {
            return false;
        }
        return true;
    }

    bool NetServer::init() {
        this->daemonize();
        this->installSignal();
        m_netModelService = NetModelFactory::getNetModel(m_option->getNetModel());
        if (nullptr == m_netModelService) {
            return false;
        }
        m_netModelService->setThread(m_option->getThreadNumber());
        m_netModelService->start(m_option);
        return true;
    }

    void NetServer::waitingQuit() {
        do {
            // coroutine thread
            std::this_thread::sleep_for(std::chrono::seconds(5));
        } while (!g_quit);
        m_netModelService->quit();
        m_netModelService->waitingQuit();
        return;
    }

    void NetServer::installSignal() {
        signal(SIGPIPE, SIG_IGN); // socket/pip read/write failed
        signal(SIGCHLD, SIG_IGN); // child process was exit, will notification parent process.
        signal(SIGTSTP, SIG_IGN); // receive signal will stop the process
        signal(SIGTTOU, SIG_IGN); // from terminal
        signal(SIGTTIN, SIG_IGN); // from terminal
        signal(SIGHUP,  SIG_IGN); // from terminal
        signal(SIGQUIT, SIG_IGN);
        signal(SIGURG,  SIG_IGN); // URG
        signal(SIGTERM, [](int sign) {
            switch(sign) {
                case SIGHUP:
                case SIGTERM:
                    g_quit = true;
                    break;
            }
        });
    }

    void NetServer::daemonize() {
        if (!m_option->getDaemonize()) {
            return;
        }
        // fork child
        pid_t pid = fork();
        if (pid < 0) {
            exit(-1);
        } else if (pid > 0) {
            exit(0);
        }

        // clear permission
        umask(0);

        // changes the current working directory of the calling process to the directory specified in path.
        chdir("/");

        // creates a new session if the calling process is not a process group leader.
        setsid();

        // make sure we have stdin/stdout/stderr reserved
        int fd = open("/dev/null", O_RDWR);
        if (fd != -1) {
            dup2(fd, STDIN_FILENO);
            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            if (fd > 2) {
                close(fd);
            }
        }
        /*
        close(0);
        close(1);
        close(2);
        auto tfd = open("/dev/null", O_RDWR);
        dup(tfd);
        dup(tfd);
        */
    }
}
}