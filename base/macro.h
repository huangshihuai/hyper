#ifndef HYPER_BASE_MACRO_H
#define HYPER_BASE_MACRO_H
#include <iostream>

namespace hyper {
namespace macro {
#define HYPER_COMPARE(first, second, condition, doAction, printLog) \
    do { \
        if ((first) condition (second)) { \
            std::cout << printLog << std::endl; \
            doAction; \
        } \
    } while (false)
}
}

#endif // HYPER_BASE_MACRO_H