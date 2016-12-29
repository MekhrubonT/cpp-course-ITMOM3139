#include <iostream>
#include "either.h"

using namespace std;

int main() {
	using namespace either_m;
	either<int, pair<int,int>> a(5);
	either<int, pair<int,int>> b(a);
	cout << a.is_left() << "\n";
		cout << a.left() << "\n";
	cout << a.is_right() << "\n\n";
		// cout << a.right() << "\n";

	cout << b.is_left() << "\n";
		cout << b.left() << "\n";
	cout << b.is_right() << "\n\n";
	// 	cout << b.right() << "\n";
	a.emplace(emplace_right, 15, 10);
	cout << a.is_left() << "\n";
		// cout << a.left() << "\n";
	cout << a.is_right() << "\n\n";
	cout << '\t' << a.right().first << ' ' << a.right().second << "\n";

	// a.emplace(emplace_right, 1, 2);
	// cout << a.is_left() << "\n";
	// cout << a.is_right() << "\n";
}