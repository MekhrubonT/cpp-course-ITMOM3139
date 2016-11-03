#pragma once

#include "node.h"


template <typename List>
struct pop_back
{
	typedef node<List::data, typename pop_back<typename List::next>::result> result;
};

template <int Data>
struct pop_back<node<Data, nil>>
{
	typedef nil result;
};