#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <cmath>
#include "big_integer.h"

#include <cstring>
#include <stdexcept>

using namespace std;

const int BASEPOW = 15;
const int BASE = (1 << BASEPOW);
const int NEEDEDBITS = BASE - 1;
int rubbish;

void normalize(int &signum, vector<int> &v)
{
    if (v.empty())
    {
        v.push_back(0);
    }
    while (v.size() != 1 && v.back() == 0)
    {
        v.pop_back();
    }
    if (v.size() == 1 && v.back() == 0)
    {
        signum = 0;
    }
}

int comp(big_integer const& a, big_integer const& b, bool absCompare = false) {
    if (!absCompare && a.sign() != b.sign())
    {
        return a.sign() - b.sign();
    }
    if (a.size() != b.size())
    {
        return a.size() - b.size();
    }
    for (int it = (int)a.size() - 1; it >= 0; it--)
    {
        if (a.v[it] != b.v[it])
        {
            return a.v[it] - b.v[it];
        }
    }
    return 0;
}

void add(vector<int> &res, const vector<int> a, const vector<int> &b)
{
    int carry = 0;
    res.resize(max(a.size(), b.size()));
    for (size_t it = 0; it < max(a.size(), b.size()); ++it)
    {
        carry += (it < a.size() ? a[it] : 0) + (it < b.size() ? b[it] : 0);
        res[it] = carry & NEEDEDBITS;
        carry >>= BASEPOW;
    }
    if (carry != 0)
    {
       res.push_back(carry);
    }
}

void subtract(vector<int> &res, const vector<int> a, const vector<int> b)
{
    res = a;
    for (size_t it = 0; it < a.size(); it++)
    {
        if (res[it] < (it < b.size() ? b[it] : 0))
        {
            res[it] += BASE;
            res[it + 1]--;
        }
        res[it] -= (it < b.size() ? b[it] : 0);
    }

    normalize(rubbish, res);
}

void multiply(vector<int> &res, const vector<int> a, const vector<int> &b)
{
    res.resize(a.size() + b.size() + 1);
    fill(res.begin(), res.end(), 0);

    for (size_t i = 0; i < a.size(); i++)
    {
        for (size_t j = 0; j < b.size(); j++)
        {
            res[i + j] += a[i] * b[j];
            if(res[i + j] > NEEDEDBITS) {
                res[i + j + 1] += res[i + j] >> BASEPOW;
                res[i + j] &= NEEDEDBITS;
            }
        }
    }

    for (size_t i = 0; i < res.size() - 1; i++)
    {
        res[i + 1] += res[i] >> BASEPOW;
        res[i] &= NEEDEDBITS;
    }

    normalize(rubbish, res);
}



void shortDivMod(const int dividendBase, const int dividerBase, const vector<int> &a, vector<int> & res, int &mod)
{
    mod = 0;
    res.resize(a.size(), 0);
    for (int it = (int)a.size() - 1; it >= 0; it--)
    {
        mod = mod * dividendBase + a[it];
        res[it] = mod / dividerBase;
        mod %= dividerBase;
    }
    normalize(rubbish, res);
}


void longDiv(vector<int> &res, const vector<int> a, const vector<int> &b)
{
    if (a.size() < b.size())
    {
        res = {0};
        return;
    }
    vector<int> temp, pref;
    res.resize(a.size() - b.size() + 2);
    fill(res.begin(), res.end(), 0);
    for(int it = (int)a.size() - 1; it >= 0; it--) {
        pref.insert(pref.begin(), a[it]);
        int l = 1, r = BASE;
        while (l < r)
        {
            int mid = (l + r) / 2;
            multiply(temp, {mid}, b);
            if (comp(big_integer(0, pref), big_integer(0, temp)) >= 0)
            {
                l = mid + 1;
            }
            else
            {
                r = mid;
            }
        }
        res[it] = l - 1;
        multiply(temp, {res[it]}, b);
        subtract(pref, pref, temp);
        while (pref.back() == 0)
        {
            pref.pop_back();

        }
    }

    normalize(rubbish, res);
}

vector<int> to_byte(int sign, vector<int> v)
{
    if (sign < 0)
    {
        int carry = 1;
        for (auto &x : v)
        {
            carry =  carry +  ((~x) & NEEDEDBITS);
            x = carry % BASE;
            carry /= BASE;
        }
    }
    v.push_back(sign >= 0 ? 0: NEEDEDBITS);
    return v;
}

void print(int x, int base = BASEPOW) {
    for(int i = 0; i < base; i++)
        cout << ((x >> i) & 1);

}

void print(const vector<int> &a) {
    cout << a.size() << "\n";
    for (auto x : a) {
        print(x);
        cout << " ";
    }
    cout << "\n";
}

big_integer from_byte(vector<int> v) {
    int sign = 1;
    if (v.back() == NEEDEDBITS)
    {
        sign = -1;
        v[0]--;
        bool flag = false;
        for(int i = 0; i + 1 < v.size(); i++)
        {
            if (v[i] < 0)
            {
                v[i] += BASE;
                v[i + 1]--;
            }
            v[i] = (~v[i]) & NEEDEDBITS;
            flag |= (v[i] != 0);

        }
        if (!flag)
        {
            v.back() = 1;
            v.push_back(NEEDEDBITS);
        }
    }
    v.pop_back();
    normalize(sign, v);
    return big_integer(sign, v);
}


enum operation { XOR, OR, AND };

big_integer byteFunctionBigInteger(const vector<int> &a, const vector<int> &b, operation op)
{
    vector<int> res(max(a.size(), b.size()));
//    print(a);
//    print(b);
    for(int i = 0; i < res.size(); i++)
    {
        switch(op)
        {
            case AND: res[i] = a[min((int)a.size() - 1, i)] & b[min((int)b.size() - 1, i)]; break;
            case OR: res[i] = a[min((int)a.size() - 1, i)] | b[min((int)b.size() - 1, i)]; break;
            case XOR: res[i] = a[min((int)a.size() - 1, i)] ^ b[min((int)b.size() - 1, i)]; break;
            default: break;
        }
    }
//    print(res);
    return from_byte(res);
}

big_integer leftShift(const vector<int> &a, int shift)
{
    vector<int> res(shift / BASEPOW, 0);
    int cur = 0, last = a.back();
    shift %= BASEPOW;
    for (auto x : a)
    {
        cur += x << shift;
        res.push_back(cur & NEEDEDBITS);
        cur >>= BASEPOW;
    }

    res.push_back(last);
    return from_byte(res);
}

big_integer rightShift(const vector<int> &a, int shift)
{
    vector<int> res;
    int last = a.back(), i = shift / BASEPOW;
    shift %= BASEPOW;
    int cur = a[i] >> shift;
    while(i + 1 < a.size())
    {
        cur = cur + (a[i + 1] << (BASEPOW - shift));
        res.push_back(cur & NEEDEDBITS);
        cur >>= BASEPOW;
        i++;
    }
    res.push_back(last);
    return from_byte(res);
}


big_integer::big_integer()
{
    v.resize(1, 0);
    signum = 0;
}

big_integer::big_integer(int sign, const vector<int> &other)
{
    signum = sign;
    v.insert(v.begin(), other.begin(), other.end());
}

big_integer::big_integer(big_integer const& other)
{
    signum = other.sign();
    v.insert(v.begin(), other.v.begin(), other.v.end());
}

big_integer::big_integer(int a)
{
    signum = 0;
    if(a != 0)
        signum = a > 0 ? 1: -1;
    a = abs(a);
    for (size_t it = 0; a != 0; it++)
    {
        v.push_back(a % BASE);
        a /= BASE;
    }
    normalize(signum, v);
}

big_integer ZERO(0), ONE(1);

big_integer::big_integer(std::string const& str)
{
    int st = 0, cur = 0;
    vector<int> temp;
    signum = 1;
    for (auto x : str)
    {
        if (x == '-')
        {
            signum = -1;
        }
        else
        {
            temp.push_back(x - 48);
        }
    }

    reverse(temp.begin(), temp.end());
    int mod;
    while (temp.size() != 1 || temp[0] != 0)
    {
        shortDivMod(10, BASE, temp, temp, mod);
        v.push_back(mod);
    }

    normalize(signum, v);
}

big_integer::~big_integer() {}

big_integer& big_integer::operator=(big_integer const& other)
{
    v.resize(other.size());
    signum = other.sign();
    for (size_t it = 0; it < other.size(); it++) {
        v[it] = other.v[it];
    }
    return *this;
}

big_integer& big_integer::operator+=(big_integer const& rhs)
{
    if (sign() == rhs.sign())
    {
        add(v, v, rhs.v);
    }
    else if (comp(*this, rhs, true) < 0)
    {
        subtract(v, rhs.v, v);
        signum = rhs.sign();
    }
    else
    {
        subtract(v, v, rhs.v);
    }
    normalize(signum, v);
    return *this;
}

big_integer& big_integer::operator-=(big_integer const& rhs)
{
    return *this += -rhs;
}

big_integer& big_integer::operator*=(big_integer const& rhs)
{
    multiply(v, v, rhs.v);
    signum *= rhs.sign();
    normalize(signum, v);
    return *this;
}

big_integer& big_integer::operator/=(big_integer const& rhs)
{
    longDiv(v, v, rhs.v);
    signum *= rhs.signum;
    normalize(signum, v);
    return *this;
}

big_integer& big_integer::operator%=(big_integer const& rhs)
{
    return (*this = *this - (*this / rhs) * rhs);
}

big_integer& big_integer::operator&=(big_integer const& rhs)
{
    *this = byteFunctionBigInteger(to_byte(sign(), v), to_byte(rhs.sign(), rhs.v), AND);
    return *this;
}

big_integer& big_integer::operator|=(big_integer const& rhs)
{
    return (*this = byteFunctionBigInteger(to_byte(sign(), v), to_byte(rhs.sign(), rhs.v), OR));
}

big_integer& big_integer::operator^=(big_integer const& rhs)
{
    return (*this = byteFunctionBigInteger(to_byte(sign(), v), to_byte(rhs.sign(), rhs.v), XOR));
}

big_integer& big_integer::operator<<=(int rhs)
{
    return (*this = leftShift(to_byte(sign(), v), rhs));
}

big_integer& big_integer::operator>>=(int rhs)
{
    return (*this = rightShift(to_byte(sign(), v), rhs));
}

big_integer big_integer::operator+() const
{
    return *this;
}

big_integer big_integer::operator-() const
{
    return big_integer(-signum, v);
}

big_integer big_integer::operator~() const
{
    return -*this - ONE;
}

big_integer& big_integer::operator++()
{
    return *this += ONE;
}

big_integer big_integer::operator++(int)
{
    big_integer r = *this;
    ++*this;
    return r;
}

big_integer& big_integer::operator--()
{
    return *this -= ONE;
}

big_integer big_integer::operator--(int)
{
    big_integer r = *this;
    --*this;
    return r;
}

big_integer operator+(big_integer a, big_integer const& b)
{
    return a += b;
}

big_integer operator-(big_integer a, big_integer const& b)
{
    return a -= b;
}

big_integer operator*(big_integer a, big_integer const& b)
{
    return a *= b;
}

big_integer operator/(big_integer a, big_integer const& b)
{
    return a /= b;
}

big_integer operator%(big_integer a, big_integer const& b)
{
    return a %= b;
}

big_integer operator&(big_integer a, big_integer const& b)
{
    return a &= b;
}

big_integer operator|(big_integer a, big_integer const& b)
{
    return a |= b;
}

big_integer operator^(big_integer a, big_integer const& b)
{
    return a ^= b;
}

big_integer operator<<(big_integer a, int b)
{
    return a <<= b;
}

big_integer operator>>(big_integer a, int b)
{
    return a >>= b;
}


bool operator==(big_integer const& a, big_integer const& b)
{
    return !comp(a, b);
}

bool operator!=(big_integer const& a, big_integer const& b)
{
    return comp(a, b);
}

bool operator<(big_integer const& a, big_integer const& b)
{
    return comp(a, b) < 0;
}

bool operator>(big_integer const& a, big_integer const& b)
{
    return comp(a, b) > 0;
}

bool operator<=(big_integer const& a, big_integer const& b)
{
    return comp(a, b) <= 0;
}

bool operator>=(big_integer const& a, big_integer const& b)
{
    return comp(a, b) >= 0;
}

std::string to_string(big_integer const& a)
{
    string res;
    vector<int> v = a.v;
    int mod;

    while (v.size() != 1 || v[0] != 0)
    {
        shortDivMod(BASE, 10, v, v, mod);
        res += (char)(mod + 48);
    }

    if (a.sign() == -1)
    {
       res += "-";
    }
    reverse(res.begin(), res.end());
    return (res.empty() ? "0" : res);
}

std::ostream& operator<<(std::ostream& s, big_integer const& a)
{
    return s << to_string(a);
}
std::istream& operator>>(std::istream &s, big_integer &a)
{
    std::string d;
    s >> d;
    a = big_integer(d);
    return s;
}

int main()
{
//    big_integer x, y;
//    cin >> x >> y;
//    cout << x * y;

//    print(-216, 30);
//    cout << "\n";
//    print(-253, 30);
//    cout << "\n";
//    cout << (big_integer(-216) & big_integer(-253)) << "\n";
//    cout << ((-216) & (-253)) << "\n";
//    return 0;
//    for(int i = 0; i < 1e+5; i++) {
//        int x = rand() - rand();int y = rand() % 5;
////        if(to_string(x & y) != to_string(big_integer(x) & big_integer(y))) {
////            cout << x << ' ' << y << "\n";
////            break;
////        }
//        assert(to_string(x >> y) == to_string(big_integer(x) >> (y)));
//        assert(to_string(x << y) == to_string(big_integer(x) << (y)));
////        assert(to_string(x ^ y) == to_string(big_integer(x) ^ big_integer(y)));
//    }
    return 0;
}
