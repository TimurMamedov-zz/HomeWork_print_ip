#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <tuple>
#include <type_traits>
#include <sstream>

template <typename... Args>
struct container_traits : std::false_type {};

template <typename... Args>
struct container_traits<std::vector<Args...> > : std::true_type {};

template <typename... Args>
struct container_traits<std::list<Args...> > : std::true_type {};

template<typename... Args>
struct is_vector_or_list
{
    static constexpr bool const value = container_traits<Args...>::value;
};

template<typename T>
struct is_tuple : std::false_type {};

/// @private
template<typename... Ts>
struct is_tuple<std::tuple<Ts...> > : std::true_type {};

//-------------------------------------
template <typename T>
struct is_string : std::false_type {};

template <>
struct is_string<std::string> : std::true_type {};
//-------------------------------------

//print vector or list ip
template<typename T>
typename std::enable_if<is_vector_or_list<T>::value, void>::type
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
typename std::enable_if<is_string<T>::value, void>::type
print_ip(const T& str, std::ostringstream& os)
{
    os << str << "\n";
}

//print integral ip
template<typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print_ip(const T &num, std::ostringstream& os)
{
    auto size = sizeof(T);
    std::list<std::int16_t> ip;
    auto temp = num;
    while(size)
    {
        ip.emplace_front(temp & 255);
        temp = temp >> 8;
        size--;
    }
    print_ip(ip, os);
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

template<typename T>
typename std::enable_if<is_tuple<T>::value, void>::type
print_ip(const T &tuple, std::ostringstream& os)
{
    TuplePrinter<decltype(tuple), std::tuple_size<T>::value>::print(tuple, os);
    os << "\n";
}
