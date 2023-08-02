#pragma once
#include <memory>

namespace sinfer {

template<typename T>
class singleton {
public:
    static std::shared_ptr<T> instance() {
        static std::shared_ptr<T> v(new T);
        return v;
    }

    singleton(const singleton &) = delete;
    singleton &operator=(const singleton) = delete;
protected:
    //struct token {};
    singleton() = default;
};

}