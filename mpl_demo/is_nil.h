#pragma once

#include "node.h"

template <typename T>
struct is_nil
{
    static bool const value = false;
};

template <>
struct is_nil<nil>
{
    static bool const value = true;
};
