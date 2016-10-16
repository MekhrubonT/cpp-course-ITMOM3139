#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <cmath>
#include "big_integer.h"

#include <cstring>
#include <stdexcept>

using namespace std;

const int64_t BASEPOW = 32;
const int64_t BASE = (1ll << BASEPOW);
const int64_t NEEDEDBITS = BASE - 1;


int normalize(vector<unsigned> &v, int signum = 0)
{
    if (v.empty())
    {
        v.push_back(0);
    }
    size_t pos = v.size() - 1;
    while (pos && v[pos] == 0)
    {
        pos--;
    }
    v.resize(pos + 1);
    return (v.size() == 1 && v.back() == 0) ? 0 : signum;
}

int vector_compare(vector<unsigned> const &a, vector<unsigned> const &b)
{
    if (a.size() != b.size())
    {
        return a.size() - b.size();
    }
    for (int it = (int)a.size() - 1; it >= 0; it--)
    {
        if (a[it] != b[it])
        {
            return a[it] > b[it] ? 1 : -1;
        }
    }
    return 0;
}


int comp(big_integer const& a, big_integer const& b, bool absCompare = false) {
    return (!absCompare && a.sign() != b.sign()) ? a.sign() - b.sign() : vector_compare(a.v, b.v);
}

void add(vector<unsigned> &res, const vector<unsigned> &a, const vector<unsigned> &b)
{
    uint64_t carry = 0;
    size_t asize = a.size();
    size_t bsize = b.size();
    res.resize(max(a.size(), b.size()));
    for (size_t it = 0; it < max(a.size(), b.size()); ++it)
    {
        carry += (int64_t) (it < asize ? a[it] : 0) + (it < bsize ? b[it] : 0);
        res[it] = carry & NEEDEDBITS;
        carry >>= BASEPOW;
    }
    if (carry != 0)
    {
       res.push_back(carry);
    }
}

void subtract(vector<unsigned> &res, const vector<unsigned> &a, const vector<unsigned> &b)
{
    int64_t carry = 0, ncarry;
    size_t asize = a.size();
    size_t bsize = b.size();
    res.resize(asize);
    for (size_t it = 0; it < asize; it++)
    {
        ncarry = 0;
        carry = a[it] - carry - (it < bsize ? b[it] : 0);
        if (carry < 0)
        {
            carry += BASE;
            ncarry = 1;
        }
        res[it] = carry;
        carry = ncarry;
    }

    normalize(res);
}

void multiplyShort(vector<unsigned> &res, const vector<unsigned> &a, uint64_t b)
{
    res.resize(a.size());
    uint64_t x = 0;
    for (size_t i = 0; i < a.size(); i++)
    {
        x += (uint64_t) a[i] * b;
        res[i] = (x & NEEDEDBITS);
        x >>= BASEPOW;
    }
    if (x)
    {
        res.push_back(x);
    }
}

void multiply(vector<unsigned> &res, const vector<unsigned> &a, const vector<unsigned> &b)
{
    vector<uint64_t> buf(a.size() + b.size() + 1, 0);
    uint64_t x;
    for (size_t i = 0; i < a.size(); i++)
    {
        for (size_t j = 0; j < b.size(); j++)
        {
            x = (uint64_t)a[i] * b[j] + buf[i + j];
            buf[i + j + 1] += (x >> BASEPOW);
            buf[i + j] = (x & NEEDEDBITS);
        }
    }

    res.resize(buf.size() - 1);
    for (size_t i = 0; i + 1 < buf.size(); i++)
    {
        buf[i + 1] += (buf[i] >> BASEPOW);
        res[i] = (buf[i] & NEEDEDBITS);
    }

    normalize(res);
}

unsigned shortDivMod(const int64_t dividendBase, const int64_t divider, const vector<unsigned> &a, vector<unsigned> & res, unsigned mod = 0)
{
    int64_t cur = 0;
    res.resize(a.size(), 0);
    for (int it = (int)a.size() - 1; it >= 0; it--)
    {
        cur = cur * dividendBase + a[it];
        res[it] = cur / divider;
        cur %= divider;
    }
    mod = cur;
    normalize(res);
    return mod;
}

void longDiv(vector<unsigned> &res, const vector<unsigned> a, const vector<unsigned> &b)
{
    if (a.size() < b.size())
    {
        res = {0};
        return;
    }

    if (b.size() == 1)
    {
        shortDivMod(BASE, b[0], a, res);
        return;
    }

    vector<unsigned> temp, pref;
    res.resize(a.size() - b.size() + 2);
    fill(res.begin(), res.end(), 0);
    for(int it = (int)a.size() - 1; it >= 0; it--) {
        pref.insert(pref.begin(), a[it]);
        int64_t l = 1, r = vector_compare(pref, b) >= 0 ? BASE : 1;
        while (l < r)
        {
            int64_t mid = (l + r) >> 1;
            multiplyShort(temp, b, mid);
            if (vector_compare(pref, temp) >= 0)
            {
                l = mid + 1;
            }
            else
            {
                r = mid;
            }
        }

        res[it] = l - 1;
        if (l != 1)
        {
            multiplyShort(temp, b, res[it]);
            subtract(pref, pref, temp);
        }
        while (!pref.empty() && pref.back() == 0)
        {
            pref.pop_back();

        }
    }

    normalize(res);
}

vector<unsigned> to_byte(int sign, vector<unsigned> v)
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

big_integer from_byte(std::vector<unsigned> &v) {
    int sign = 1;
    if (v.back() == NEEDEDBITS)
    {
        sign = -1;
        v[0]--;
        bool flag = false;
        for(size_t i = 0; i + 1 < v.size(); i++)
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
    sign = normalize(v, sign);
    return big_integer(sign, v);
}


enum operation { XOR, OR, AND };

big_integer byteFunctionBigInteger(const vector<unsigned> &a, const vector<unsigned> &b, operation op)
{
    vector<unsigned> res(max(a.size(), b.size()));
    for(size_t i = 0; i < res.size(); i++)
    {
        switch(op)
        {
            case AND: res[i] = a[min(a.size() - 1, i)] & b[min(b.size() - 1, i)]; break;
            case OR: res[i] = a[min(a.size() - 1, i)] | b[min(b.size() - 1, i)]; break;
            case XOR: res[i] = a[min(a.size() - 1, i)] ^ b[min(b.size() - 1, i)]; break;
        }
    }
    return from_byte(res);
}

big_integer leftShift(const vector<unsigned> &a, int shift)
{
    vector<unsigned> res(shift / BASEPOW, 0);
    uint64_t cur = 0;
    unsigned last = a.back();
    shift %= BASEPOW;
    for (auto x : a)
    {
        cur += (uint64_t) x << shift;
        res.push_back(cur & NEEDEDBITS);
        cur >>= BASEPOW;
    }

    res.push_back(last);
    return from_byte(res);
}

big_integer rightShift(const vector<unsigned> &a, int shift)
{
    vector<unsigned> res;
    int last = a.back(), i = shift / BASEPOW;
    shift %= BASEPOW;
    int cur = a[i] >> shift;
    while(i + 1 < (int)a.size())
    {
        cur = cur + ((uint64_t)a[i + 1] << (BASEPOW - shift));
        res.push_back(cur & NEEDEDBITS);
        cur /= BASE;
        i++;
    }
    res.push_back(last);
    return from_byte(res);
}


big_integer::big_integer() : signum(0), v(1, 0) {}

big_integer::big_integer(int sign, const vector<unsigned> &other) : signum(sign), v(other) {}

big_integer::big_integer(big_integer const& other) : signum(other.sign()), v(other.v) {}

big_integer::big_integer(int a) : signum(a == 0 ? 0 : (a > 0 ? 1 : -1)), v(1, abs(a)) {}

big_integer ONE(1);

big_integer::big_integer(std::string const& str) : signum(1) {
    vector<unsigned> temp;
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
    unsigned mod = 0;
    while (temp.size() != 1 || temp[0] != 0)
    {
        mod = shortDivMod(10, BASE, temp, temp, mod);
        v.push_back(mod);
    }
    signum = normalize(v, signum);
}

big_integer::~big_integer() {}

big_integer& big_integer::operator=(big_integer const& other)
{
    signum = other.sign();
    v = other.v;
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
    signum = normalize(v, signum);
    return *this;
}

big_integer& big_integer::operator-=(big_integer const& rhs)
{
    return *this += -rhs;
}

big_integer& big_integer::operator*=(big_integer const& rhs)
{
    multiply(v, v, rhs.v);
    signum = normalize(v, signum * rhs.sign());
    return *this;
}

big_integer& big_integer::operator/=(big_integer const& rhs)
{
    longDiv(v, v, rhs.v);
    signum = normalize(v, signum * rhs.signum);
    return *this;
}

big_integer& big_integer::operator%=(big_integer const& rhs)
{
    return (*this = *this - (*this / rhs) * rhs);
}

big_integer& big_integer::operator&=(big_integer const& rhs)
{
    return *this = byteFunctionBigInteger(to_byte(sign(), v), to_byte(rhs.sign(), rhs.v), AND);
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
    vector<unsigned> v = a.v;
    unsigned mod = 0;
    while (v.size() != 1 || v[0] != 0)
    {
        mod = shortDivMod(BASE, 10, v, v, mod);
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
