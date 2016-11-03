#pragma once

#include "node.h"

template <typename list, int value> 
struct push_front {
    typedef node<value, list> result;
}; 
