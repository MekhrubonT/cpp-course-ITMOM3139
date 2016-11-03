#pragma once

#include "node.h"

template <typename List, size_t pos, int Value>
struct insert
{
	typedef node<List::data, typename insert<typename List::next, pos - 1, Value>::result> result;	
};

template <typename List, int Value>
struct insert<List, 0, Value>
{
	typedef node<Value, List> result;
};
