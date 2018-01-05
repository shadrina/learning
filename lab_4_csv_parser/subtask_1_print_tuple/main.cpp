#include <tuple>
#include <iostream>

// sizeof...:
// returns the number of elements in a parameter pack

// std::enable_if:
// if expression is true, std::enable_if has a public member typedef type, equal to T(void);
// otherwise, there is no member typedef.
// is a convenient way to conditionally remove functions from overload resolution based on
// type traits and to provide separate function overloads for different type traits

// stolen from stackoverflow:)

template <size_t n, typename... T>
typename std::enable_if<(n >= sizeof...(T))>::type
print_tuple(std::ostream&, const std::tuple<T...>&) {}

template <size_t n, typename... T>
typename std::enable_if<(n < sizeof...(T))>::type
print_tuple(std::ostream& os, const std::tuple<T...> &tup) {
    if (n != 0)
        os << ", ";
    os << std::get<n>(tup);
    print_tuple<n+1>(os, tup);
}

template <typename... T>
std::ostream& operator<<(std::ostream& os, const std::tuple<T...> &tup) {
    os << "[";
    print_tuple<0>(os, tup);
    return os << "]";
}

int main() {
    std::cout << std::make_tuple(2, 3.14159F, 2345.678) << std::endl;
    std::cout << std::make_tuple("hello", 5) << std::endl;
    std::cout << std::make_tuple() << std::endl;
    return 0;
}