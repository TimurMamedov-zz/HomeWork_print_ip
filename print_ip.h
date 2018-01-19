#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <tuple>
#include <type_traits>

template <typename... Args>
struct container_traits
{
    static bool const value = false;
};

template <typename... Args>
struct container_traits<std::vector<Args...> >
{
    static bool const value = true;
};

template <typename... Args>
struct container_traits<std::list<Args...> >
{
    static bool const value = true;
};

template<typename... Args>
struct is_vector_or_list
{
    static constexpr bool const value = container_traits<Args...>::value;
};
//-------------------------------------
template <typename T>
struct is_string
{
    static bool const value = false;
};

template <>
struct is_string<std::string>
{
    static bool const value = true;
};
//-------------------------------------
template <typename T>
struct is_tuple
{
    static bool const value = false;
};

template <typename... Args>
struct is_tuple<std::tuple<Args...> >
{
    static bool const value = true;
};
//------------------------------------------------------------------

template<typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print_ip(const T &bar)
{
    std::cout << "integral" << "\n";
}

template<typename T>
typename std::enable_if<is_vector_or_list<T>::value, void>::type
print_ip(const T &bar)
{
    std::cout << "is_vector_or_list" << "\n";
}

template<typename T>
typename std::enable_if<is_string<T>::value, void>::type
print_ip(const T &bar)
{
    std::cout << "is_string" << "\n";
}
//--------------------------------------------------------------------

template<class Tuple, std::size_t N>
struct TuplePrinter
{
    static void print(const Tuple& t)
    {
        static_assert(std::is_same<decltype(std::get<N-1>(t)),
                      decltype(std::get<N-2>(t))>::value,
                      "Need the same TYPE!!!");
        TuplePrinter<Tuple, N-1>::print(t);
        std::cout << "." << std::get<N-1>(t);
    }
};

template<class Tuple>
struct TuplePrinter<Tuple, 1>
{
    static void print(const Tuple& t)
    {
        std::cout << std::get<0>(t);
    }
};

template<typename... Args>
void print_ip(const std::tuple<Args...> &bar)
{
    TuplePrinter<decltype(bar), sizeof...(Args)>::print(bar);
    std::cout << "\n";
}
