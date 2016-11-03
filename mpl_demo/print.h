#pragma once

#include <iostream>
#include "node.h"

template <typename T>
struct print_impl
{
    static void do_print()
    {
        std::cout << ", " << T::data;
        print_impl<typename T::next>::do_print();
    }
};

template <>
struct print_impl<nil>
{
    static void do_print()
    {
        std::cout << ']';
    }
};

template <int Data, typename Next>
std::ostream& operator<<(std::ostream& os, node<Data, Next>)
{
    std::cout << '[' << Data;
    print_impl<Next>::do_print();
    return os;
}

inline std::ostream& operator<<(std::ostream& os, nil)
{
    std::cout << "[]";
    return os;
}
