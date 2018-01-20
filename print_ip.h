#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <tuple>
#include <type_traits>
#include <sstream>

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

//print integral ip
template<typename T>
typename std::enable_if<std::is_integral<T>::value, std::string>::type
print_ip(const T &num, std::ostringstream& os)
{
    auto size = sizeof(T);
    while(size)
    {
        auto byte = num >> ((size - 1)*8);
        os << byte << ".";
        size--;
    }
    os << "\n";
}

//print vector or list ip
template<typename T>
typename std::enable_if<is_vector_or_list<T>::value, std::string>::type
print_ip(const T& cont, std::ostringstream& os)
{
    if(!cont.empty())
    {
        auto last = cont.end();
        last--;
        for(auto it = cont.cbegin(); it != last; it++)
        {
            os << *it << ".";
        }
        os << *last << "\n";
    }
}

//print string ip
template<typename T>
typename std::enable_if<is_string<T>::value, std::string>::type
print_ip(const T& str, std::ostringstream& os)
{
    os << str << "\n";
}

//print tuple ip
template<class Tuple, std::size_t N>
struct TuplePrinter
{
    static void print(const Tuple& t, std::ostringstream& os)
    {
        static_assert(std::is_same<decltype(std::get<N-1>(t)),
                      decltype(std::get<N-2>(t))>::value,
                      "Need the same TYPE!!!");
        TuplePrinter<Tuple, N-1>::print(t, os);
        os << "." << std::get<N-1>(t);
    }
};

template<class Tuple>
struct TuplePrinter<Tuple, 1>
{
    static void print(const Tuple& t, std::ostringstream& os)
    {
        os << std::get<0>(t);
    }
};

template<typename... Args>
void print_ip(const std::tuple<Args...> &bar, std::ostringstream& os)
{
    TuplePrinter<decltype(bar), sizeof...(Args)>::print(bar, os);
    os << "\n";
}
