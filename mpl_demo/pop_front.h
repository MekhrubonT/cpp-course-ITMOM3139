#pragma once

#include "node.h"
#include "is_nil.h"

template <typename List>
struct pop_front
{
	typedef typename List::next result;
};