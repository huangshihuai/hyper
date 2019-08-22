#include <memory>
#include <iostream>

int main() {
    auto p = std::make_unique<int>(10);
    auto d = p;
    std::cout << d.use_count() << std::endl;
    *d = 100;
    std::cout << p.use_count() << " " << d.use_count() << std::endl;
    std::cout << *p << " " << *d << std::endl;
    return 0;
}