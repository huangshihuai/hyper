#pragma once

namespace hyper {
namespace base {

enum ProtocolTypes{
    STREAM,
    IM,
};

enum ProtocolStateType {
    SUCCESS,
    NOT_FOUND,
    AGAIN,
    FAILE,
};

}
}