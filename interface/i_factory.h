#ifndef HYPER_INTERFACE_I_FACTORY_H
#define HYPER_INTERFACE_I_FACTORY_H
namespace hyper {
namespace net {
template<typename T>
class IFactory {
public:
    std::shared_ptr<T> getServer();
};
}
}
#endif // HYPER_INTERFACE_I_FACTORY_H