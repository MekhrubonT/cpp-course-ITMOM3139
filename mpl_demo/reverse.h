#pragma once

#include "node.h"

template <typename List, typename Result>
struct my_reverse
{
	typedef typename my_reverse<typename List::next, node<List::data, Result>>::result result;
};

template <typename Result>
struct my_reverse<nil, Result>
{
	typedef Result result;
};

template <typename List>
struct reverse
{
	typedef typename my_reverse<List, nil>::result result;
};
