#include <bits/stdc++.h>
#include "bind.h"

using namespace std;

int sum(int a, int b) {
	return a + b;
}

template <typename T1, typename T2, typename T3, typename T4>
void order_print(T1 a, T2 b, T3 c, T4 d) {
	std::cout << a << ' ' << b << ' ' << c << ' ' << d << "\n";
}


void order_print(int (&a)[20]) {
	for (auto x : a)
		std::cout << x << ' ';
}

int main() {
	auto mul2 = my_bind(sum, placeholder<1>(), placeholder<1>());
	cout << mul2(100) << "\n";

	auto rev_print = my_bind(order_print<string, char, double, int>, placeholder<4>(), placeholder<3>(), placeholder<2>(), 
		placeholder<1>());
	rev_print(1, 2., '3', "4");
}