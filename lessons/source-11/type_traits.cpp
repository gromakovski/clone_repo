#include <type_traits>

namespace custom {

    template<typename T>
    struct remove_const {
        using type = T;
    };
    template<typename T>
    struct remove_const<const T> {
        using type = T;
    };

    template<typename T>
    using remove_const_t = typename remove_const<T>::type;




    template<typename T>
    struct is_void {
        static const bool value = false;
    };
    template<>
    struct is_void<void> {
        static const bool value = true;
    };

    template<typename T>
    constexpr bool is_void_v = is_void<T>::value;

}

int main() {

    custom::remove_const_t<const int> value = 42;
    // Check constant removal
    ++value;

    static_assert(custom::is_void_v<void>);

    return 0;
}