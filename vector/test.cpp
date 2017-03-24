#include <bits/stdc++.h>
#include "vector.h"



struct a
{
    virtual ~a() = 0;

    virtual void f() = 0;
};

a::~a()
{
    std::cout << "DOIT\n";
}

struct b : a
{
    ~b()
    {

    }
    void f()
    {
    }
};


int main()
{
    b bb;

}


//int main()
//{
//
//std::cout << "THIS FILE\n";
////    vector a;
////    a.push_back(123);
////    std::cout << a.front();
//    vector a;
////    const int N = 1000;
////    for (int i = 0; i < N; i++) {
////        std::string d = "";
////        d += (i + 48);
////        a.push_back("Mekhrubon" + d);
////    }
//    for (int i = 0; i < 11; i++) {
//        std::string x = "1";
//        a.insert(a.begin(), x);
//    }
//    for (auto x : a)
//        std::cout << x << "\n";
////    std::cout << a.size() << "\n";
////    std::cout << a.capacity() << "\n";
////    std::cout << a.empty() << "\n";
////
//////    for (int i = 0; i < N; i++) {
//////        assert(a.back() == a[a.size() - 1]);
//////        assert(a.front() == a[0]);
//////        a.pop_back();
//////    }s
////
////    vector b;
////    b = a;
////    a.erase(a.begin(), a.end());
//////    for (auto it = a.begin(); it != a.end(); it++)
//////        std::cout << *it << "\n";
//////    std::cout << "\n";
//////    for (auto it = b.begin() + 2; it != b.end() - 2; it++)
//////        std::cout << *it << "\n";
//////    b.insert(b.begin() + 5, "123");
//////a.clear();
////
////    std::cout << a.size() << "\n";
////    std::cout << a.capacity() << "\n";
////    std::cout << a.empty() << "\n";
//}
