#include <iostream>

#include "either.h"

using namespace either_m;

struct xxx
{
    xxx(int a, int b, int c)
        : a(a)
        , b(b)
        , c(c)
    {}

    friend std::ostream& operator<<(std::ostream&, xxx const&);
private:
    int a, b, c;
};

std::ostream& operator<<(std::ostream& os, xxx const& x)
{
    os << x.a << x.b << x.c;
    return os;
}

int main()
{
    either<int, double> e1(3331);
    std::cout << "e1:\n";
    std::cout << e1.is_left() << ' ' << e1.is_right() << '\n';
    std::cout << e1.left() << '\n';

    either<int, double> e2(2.3);
    std::cout << "e2:\n";
    std::cout << e2.is_left() << ' ' << e2.is_right() << '\n';
    std::cout << e2.right() << '\n';

    either<int, double> e3 = e1;
    std::cout << "e3:\n";
    std::cout << e3.is_left() << ' ' << e3.is_right() << '\n';
    std::cout << e3.left() << '\n';

    either<int, double> e4 = e2;
    std::cout << "e4:\n";
    std::cout << e4.is_left() << ' ' << e4.is_right() << '\n';
    std::cout << e4.right() << '\n';

    either<int, double> e5 = std::move(e3);
    std::cout << "e5:\n";
    std::cout << e5.is_left() << ' ' << e5.is_right() << '\n';
    std::cout << e3.left() << '\n';

    either<int, double> e6(e4);
    std::cout << "e6:\n";
    std::cout << e6.is_left() << ' ' << e6.is_right() << '\n';
    std::cout << e6.right() << '\n';

    either<int, double> e7(emplace_left, 666);
    std::cout << "e7:\n";
    std::cout << e7.is_left() << ' ' << e7.is_right() << '\n';
    std::cout << e7.left() << '\n';

    either<int, double> e8(emplace_right, 3.14);
    std::cout << "e8\n";
    std::cout << e8.is_left() << ' ' << e8.is_right() << '\n';
    std::cout << e8.right() << '\n';

    e8.emplace(emplace_left, 1);
    std::cout << "e8\n";
    std::cout << e8.is_left() << ' ' << e8.is_right() << '\n';
    std::cout << e8.left() << '\n';

    e8.emplace(emplace_right, 3.1415);
    std::cout << "e8\n";
    std::cout << e8.is_left() << ' ' << e8.is_right() << '\n';
    std::cout << e8.right() << '\n';

    e7 = e8;
    std::cout << "e7\n";
    std::cout << e7.is_left() << ' ' << e7.is_right() << '\n';
    std::cout << e7.right() << '\n';

    std::cout << "-----------------------------------\n";
    swap(e1, e2);
    std::cout << "e1:\n";
    std::cout << e1.is_left() << ' ' << e1.is_right() << '\n';
    std::cout << e1.right() << '\n';
    std::cout << "e2:\n";
    std::cout << e2.is_left() << ' ' << e2.is_right() << '\n';
    std::cout << e2.left() << '\n';

    either<std::string, xxx> ee("qwerty");
    std::cout << "ee:\n";
    std::cout << ee.is_left() << ' ' << ee.is_right() << '\n';
    std::cout << ee.left() << '\n';

    ee.emplace(emplace_right, 1, 2, 3);
    std::cout << "ee:\n";
    std::cout << ee.is_left() << ' ' << ee.is_right() << '\n';
    std::cout << ee.right() << '\n';

    return 0;
}

