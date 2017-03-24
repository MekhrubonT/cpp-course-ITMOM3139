#include <bits/stdc++.h>

using namespace std;

template<typename... Args>
struct tv {};

// is_same<tv<Args1...>, tv<Args2...>>::value

template <typename L, typename R>
struct issame
{
	const static int value = 0;
};

template <typename L>
struct issame<L, L>
{
	const static int value = 1;
};

template<typename V1, typename V2>
struct myis_same;

template<typename A1, typename... args1, typename B1, typename... args2>
struct myis_same<tv<A1, args1...>, tv<B1, args2...>> {
	const static int value =  myis_same<tv<args1...>, tv<args2...>>::value && issame<A1, B1>::value;
};

template<typename args1, typename args2>
struct myis_same<tv<args1>, tv<args2>> {
	const static int value =  issame<args1, args2>::value;
};
template<typename args2, typename... otherArgs>
struct myis_same<tv<>, tv<args2, otherArgs...>> {
	const static int value = 0;
};
template<typename args2, typename... otherArgs>
struct myis_same<tv<args2, otherArgs...>, tv<>> {
	const static int value = 0;
};


int main() {
	cout << "Here\n";
	cout << myis_same<tv<int, double>, tv<int, double>>::value << "\n";
}