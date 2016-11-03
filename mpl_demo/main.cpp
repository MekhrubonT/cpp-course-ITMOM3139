#include <iostream>
#include "node.h"
#include "is_nil.h"
#include "print.h"
#include "push_back.h"
#include "push_front.h"
#include "pop_back.h"
#include "pop_front.h"
#include "size.h"
#include "erase.h"
#include "insert.h"
#include "reverse.h"

typedef node<1, nil> list_1;
typedef node<1, node<2, nil>> list_12;
typedef node<1, node<2, node<3, nil>>> list_123;
typedef node<1, node<2, node<3, node<4, nil>>>> list_1234;
typedef node<1, node<2, node<3, node<4, node<5, nil>>>>> list_12345;

#if defined(_MSC_VER)                                                 \
 || defined(__GNUC__) && __GNUC__ < 6
// MSVC and GCC (pre 6.x) don't support C++17 terse static assert
#define static_assert(x) static_assert(x, #x)
#endif

static_assert(list_1::data == 1   && is_nil<list_1::next>::value);
static_assert(list_12::data == 1  && list_12::next::data == 2  && is_nil<list_12::next::next>::value);
static_assert(list_123::data == 1 && list_123::next::data == 2 && list_123::next::next::data == 3 && is_nil<list_123::next::next::next>::value);

static_assert((std::is_same<list_12, push_back<list_1, 2>::result>::value));
static_assert((std::is_same<list_123, push_back<list_12, 3>::result>::value));

typedef push_back<
			push_back<
				push_back<
					push_back<
						push_back<node<1, nil>, 2>::result
						, 3>::result
					, 4>::result
				, 5>::result
			, 6>::result 
			list7;
//typedef 
//push_back<
//push_back<node<1, nil>, 2>::result, 3>::result list7;

int main()
{
	std::cout << list_1() << "\n";
	std::cout << list_12() << "\n";
	std::cout << list_123() << "\n";
	std::cout << list_1234() << "\n";
	std::cout << list_12345() << "\n";

	std::cout << reverse<nil>::result() << "\n";
	std::cout << reverse<insert<list_12345, 0, 10>::result>::result() << "\n";
//	std::cout << insert<nil, 1, 10>::result() << "\n";
}
