#pragma once

#include "node.h"

template <typename List, int Value>
struct push_back
{
    typedef node<List::data, typename push_back<typename List::next, Value>::result> result;
};

template <int Value>
struct push_back<nil, Value>
{
    typedef node<Value, nil> result;
};
