#include "interface/i_protocol.h"

namespace hyper {
namespace net {
using namespace interface;

class Protocol : public IProtocol {
public:
    Protocol();
    ~Protocol() override;
    bool packStream() override;
    bool unPackStream() override;
};

}
}