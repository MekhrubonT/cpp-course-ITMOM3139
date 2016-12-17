// #include <bits/stdc++.h>
#include "bind.h"
#include <iostream>

using namespace hw_bind;

place_holder<1> _1;
place_holder<2> _2;
place_holder<3> _3;

int main() {
	auto f = [](int &a, int &b, int &c) {a = b = c = 0; return a + b + c;};
	int a = 1, b = 2, c = 3;
	auto g = bind(f, _1, _2, c);
	std::cout << g(a, b) << "\n";
	std::cout << a << ' ' << b << ' ' << c << "\n";
}