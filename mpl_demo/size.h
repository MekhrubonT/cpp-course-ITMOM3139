#pragma once

#include "node.h"

template <typename List>
struct size
{
	static const int result = size<typename List::next>::result + 1;
};

template <>
struct size<nil>
{
	static const int result = 0;
};