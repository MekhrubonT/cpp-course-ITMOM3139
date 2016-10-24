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


big_integer::vector::node::node(unsigned capacity, unsigned *d) : s(d), capacity(capacity) {}

big_integer::vector::SMO::SMO(unsigned capacity = 0, unsigned value = 0) {
    if (capacity <= big_integer::vector::SMALL_OBJECT_SIZE) {
        memset(s, 0, sizeof(s));
        fill(s, s + capacity, value);
    } else {
        x.capacity = capacity;
        x.s = new unsigned[capacity];
        fill(x.s, x.s + capacity, value);
    }
}
big_integer::vector::vector() : v(), sz(0) {}

big_integer::vector::vector(unsigned sz, unsigned value, int sg = 0) : v(sz, value), sz(0) {
    set_size(sz);
    set_sign(sg);
    set_mode(sz <= SMALL_OBJECT_SIZE ? SMALL_OBJECT : SMALL_OBJECT ^ 1);
}

big_integer::vector::~vector() {
    if (mode() != SMALL_OBJECT) {
        delete[] v.x.s;
    }
}

template <typename T>
big_integer::vector::vector(const T& x) {
    set_size(x.size());
    set_sign(0);
    set_mode(size() <= 3 ? SMALL_OBJECT : SMALL_OBJECT ^ 1);
    if (mode() == SMALL_OBJECT) {
        memcpy(v.s, x.begin(), sizeof(unsigned) * x.size());
    } else {
        v.x.capacity = size();
        v.x.s = new unsigned[size()];
        memcpy(v.x.s, x.begin(), sizeof(unsigned) * x.size());
    }
}
big_integer::vector::vector(const big_integer::vector& x) {
    set_size(x.size());
    set_sign(x.sign());
    set_mode(size() <= 3 ? SMALL_OBJECT : SMALL_OBJECT ^ 1);
    if (mode() == SMALL_OBJECT) {
        memcpy(v.s, x.begin(), sizeof(unsigned) * x.size());
    } else {
        v.x.capacity = size();
        v.x.s = new unsigned[size()];
        memcpy(v.x.s, x.begin(), sizeof(unsigned) * x.size());
    }
}


big_integer::vector& big_integer::vector::operator=(vector const &other) {

    if (begin() != other.begin()) {
        clear();
        for (auto x : other)
            push_back(x);
        set_sign(other.sign());
    }
    return *this;
}

void big_integer::vector::clear() {
    if (mode() != SMALL_OBJECT)
        delete[] v.x.s;
    memset(v.s, 0, sizeof(v.s));
    sz = 0;
}


int big_integer::vector::sign() const {
    return (sz >> SIGN_BIT) & 1;
}
int big_integer::vector::mode() const {
    return (sz >> MODE_BIT) & 1;
}
unsigned big_integer::vector::size() const {
    return sz & SIZE_CONST;
}

bool big_integer::vector::empty() const {
    return size() == 0;
}

unsigned& big_integer::vector::back() {
    return operator[](size() - 1);
}

const unsigned big_integer::vector::back() const {
    return operator[](size() - 1);
}

unsigned& big_integer::vector::operator[](unsigned ind) {
    return mode() == SMALL_OBJECT ? v.s[ind] : v.x.s[ind];
}

const unsigned big_integer::vector::operator[](unsigned ind) const {
    return mode() == SMALL_OBJECT ? v.s[ind] : v.x.s[ind];
}

unsigned* big_integer::vector::begin() {
    return mode() == SMALL_OBJECT ? v.s : v.x.s;
}
unsigned* big_integer::vector::end() {
    return begin() + size();
}
unsigned const* big_integer::vector::begin() const {
    return mode() == SMALL_OBJECT ? v.s : v.x.s;
}
unsigned const* big_integer::vector::end() const {
    return begin() + size();
}

void big_integer::vector::set_size(unsigned d) {
    sz = d | (sign() << SIGN_BIT) | (mode() << MODE_BIT);
}

void big_integer::vector::set_mode(unsigned x) {
    assert(x == SMALL_OBJECT || x == (SMALL_OBJECT ^ 1));
    sz = (sz & ~(1ll << MODE_BIT)) | (x << MODE_BIT);
}

void big_integer::vector::set_sign(unsigned x) {
    assert(x <= 1);
    sz = (sz & ~(1ll << SIGN_BIT)) | (x << SIGN_BIT);
}


void big_integer::vector::flip_to_small_object() {
    unsigned* d = v.x.s;
    memcpy(v.s, d, sizeof(v.s));
    delete[] d;
    set_mode(SMALL_OBJECT);
}

void big_integer::vector::flip_from_small_object(unsigned old_size, unsigned capacity = 10) {
    unsigned *d = new unsigned[capacity];
    memset(d, 0, sizeof(unsigned) * capacity);
    memcpy(d, v.s, sizeof(v.s));
    set_mode(SMALL_OBJECT ^ 1);
    v.x.capacity = capacity;
    v.x.s = d;
}


void big_integer::vector::node::update_capacity(unsigned new_capacity, unsigned copy_size, bool fill_zero = false) {
    unsigned* d = new unsigned[new_capacity];
    if (fill_zero && sizeof(d) > sizeof(s)) {
        memset(d, 0, sizeof(unsigned) * copy_size);
    }
    memcpy(d, s, sizeof(unsigned) * copy_size);
    delete[] s;
    s = d;
}

void big_integer::vector::node::ensure_capacity(unsigned new_size) {
    if (new_size > capacity) {
        update_capacity(capacity << 1, capacity);
        capacity <<= 1;
    } else if (new_size * 4 < capacity) {
        update_capacity(capacity >> 1, capacity >> 1);
        capacity >>= 1;
    }
}


void big_integer::vector::push_back(unsigned d) {
    if (size() == SMALL_OBJECT_SIZE) {
        flip_from_small_object(SMALL_OBJECT_SIZE);
    }
    if (mode() == SMALL_OBJECT) {
        v.s[size()] = d;
    } else {
        v.x.ensure_capacity(size() + 1);
        v.x.s[size()] = d;
    }
    sz++;
}
void big_integer::vector::insert(unsigned* place, int x) {
    unsigned pos = place - begin();
    push_back(x);
    place = pos + begin();
    unsigned* it = end() - 1;
    while (it > place) {
        swap(*it, *(it - 1));
        it--;
    }
}

void big_integer::vector::pop_back() {
    sz--;
    if (mode() != SMALL_OBJECT) {
        v.x.ensure_capacity(size());
    }
    if (size() == SMALL_OBJECT_SIZE) {
        flip_to_small_object();
    }
}

void big_integer::vector::resize(unsigned new_size) {
//    if (mode() == SMALL_OBJECT) {
//        while (size() > new_size)
//            pop_back();
//        if (new_size > SMALL_OBJECT_SIZE) {
//            flip_from_small_object(size(), new_size);
//            set_size(new_size);
//        } else {
//            while (size() < new_size)
//                push_back(0);
//        }
//    } else {
////        if (v.x.capacity * 2 <= new_size) {
////            v.x.update_capacity(new_size, v.x.capacity, true);
////            v.x.capacity = new_size;
////        } else if (v.x.capacity > 2 * new_size) {
////            unsigned x = SMALL_OBJECT_SIZE;
////            int d = max(x, new_size);
////            v.x.update_capacity(d, d);
////            v.x.capacity = d;
////            while (size() > new_size)
////                pop_back();
////
////        } else {
////        }
        while (size() < new_size)
            push_back(0);
        while (size() > new_size) {
            pop_back();
        }
//    }
//    set_size(new_size);

}

int normalize(big_integer::vector &a, int signum = 0)
{
    if (a.empty()) {
        a.push_back(0);
    } else {
        unsigned pos = a.size() - 1;
        while (pos && a[pos] == 0)
        {
            pos--;
        }
        a.resize(pos + 1);
    }
    return (a.size() == 1 && a.back() == 0) ? 0 : signum;
}

/// ####################### HERE IS OK #########################

//template<typename T, typename U>
int comp(const big_integer::vector& a, const big_integer::vector &b, bool absCompare = false) {
    if (!absCompare && a.sign() != b.sign())
        return b.sign()- a.sign();

    if (a.size() != b.size()) {
        return a.size() - b.size();
    }
    for (int it = (int)a.size() - 1; it >= 0; it--) {
        if (a[it] != b[it]) {
            return a[it] > b[it] ? 1 : -1;
        }
    }
    return 0;
}

int comp(big_integer const& a, big_integer const& b, bool absCompare = false) {
    return comp(a.data, b.data, absCompare);
}

//template<typename T>
void add(big_integer::vector &res, const big_integer::vector &a, const big_integer::vector &b)
{
    uint64_t carry = 0;
    unsigned asize = a.size();
    unsigned bsize = b.size();
    res.resize(max(a.size(), b.size()));
    for (unsigned it = 0; it < max(a.size(), b.size()); ++it)
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

void subtract(big_integer::vector &res, const big_integer::vector &a, const big_integer::vector &b)
{
    int64_t carry = 0, ncarry;
    unsigned asize = a.size();
    unsigned bsize = b.size();
    res.resize(asize);
    for (unsigned it = 0; it < asize; it++) {
        ncarry = 0;
        carry = a[it] - carry - (it < bsize ? b[it] : 0);
        if (carry < 0) {
            carry += BASE;
            ncarry = 1;
        }
        res[it] = carry;
        carry = ncarry;
    }

    normalize(res);
}

void multiplyShort(big_integer::vector &res, const big_integer::vector &a, uint64_t b)
{
    res.resize(a.size());
//    res.clear();
    uint64_t x = 0;
    for (unsigned i = 0; i < a.size(); i++) {
        x += (uint64_t) a[i] * b;
        res[i] = (x & NEEDEDBITS);
        x >>= BASEPOW;
    }
    if (x) {
        res.push_back(x);
    }
}

void multiply(big_integer::vector &res, const big_integer::vector &a, const big_integer::vector &b)
{
    vector<uint64_t> buf(a.size() + b.size() + 1, 0);
    uint64_t x;
    for (unsigned i = 0; i < a.size(); i++) {
        for (unsigned j = 0; j < b.size(); j++) {
            x = (uint64_t)a[i] * b[j] + buf[i + j];
            buf[i + j + 1] += (x >> BASEPOW);
            buf[i + j] = (x & NEEDEDBITS);
        }
    }

    res.resize(buf.size() - 1);
    for (unsigned i = 0; i + 1 < buf.size(); i++) {
        buf[i + 1] += (buf[i] >> BASEPOW);
        res[i] = (buf[i] & NEEDEDBITS);
    }

    normalize(res, 0);
}

unsigned shortDivMod(const int64_t dividendBase, const int64_t divider, const big_integer::vector &a, big_integer::vector & res, unsigned mod = 0)
{
    int64_t cur = 0;
    res.resize(a.size());
    for (int it = (int)a.size() - 1; it >= 0; it--)
    {
        cur = cur * dividendBase + a[it];
        res[it] = cur / divider;
        cur %= divider;
    }
    mod = cur;
    normalize(res, 0);
    return mod;
}

void longDiv(big_integer::vector &res, const big_integer::vector a, const big_integer::vector &b)
{
    if (a.size() < b.size())
    {
        res = std::initializer_list<unsigned>({0});
        return;
    }

    if (b.size() == 1)
    {
        shortDivMod(BASE, b[0], a, res);
        return;
    }

    big_integer::vector temp, pref;
    res.resize(a.size() - b.size() + 2);
    fill(res.begin(), res.end(), 0);
    for(int it = (int)a.size() - 1; it >= 0; it--) {
        pref.insert(pref.begin(), a[it]);
        int64_t l = 1, r = comp(pref, b) >= 0 ? BASE : 1;
        while (l < r)
        {
            int64_t mid = (l + r) >> 1;
            multiplyShort(temp, b, mid);
            if (comp(pref, temp) >= 0)
            {
                l = mid + 1;
            }
            else
            {
                r = mid;
            }
        }
        if (it < (int)res.size())
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
//    cout << "Res=\n";
//    cout << res.size() << "\n";
//    for (auto x : res)
//        cout << x << ' ';
//    cout << "\n";

    normalize(res);
}

big_integer::vector to_byte(int sign, big_integer::vector v)
{
    if (sign == 1)
    {
        int carry = 1;
        for (auto &x : v)
        {
            carry =  carry +  ((~x) & NEEDEDBITS);
            x = carry % BASE;
            carry /= BASE;
        }
    }
    v.push_back(sign == 0 ? 0: NEEDEDBITS);
    return v;
}

big_integer from_byte(big_integer::vector &v) {
    int sign = 0;
    if (v.back() == NEEDEDBITS)
    {
        sign = 1;
        v[0]--;
        bool flag = false;
        for(unsigned i = 0; i + 1 < v.size(); i++)
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
    v.set_sign(normalize(v, v.sign()));
    return big_integer(sign, v);
}



big_integer byteFunctionBigInteger(const big_integer::vector &a, const big_integer::vector &b, big_integer::operation op)
{
    big_integer::vector res(max(a.size(), b.size()), 0);
    for(unsigned i = 0; i < res.size(); i++)
    {
        switch(op)
        {
            case big_integer::operation::AND: res[i] = a[min(a.size() - 1, i)] & b[min(b.size() - 1, i)]; break;
            case big_integer::operation::OR: res[i] = a[min(a.size() - 1, i)] | b[min(b.size() - 1, i)]; break;
            case big_integer::operation::XOR: res[i] = a[min(a.size() - 1, i)] ^ b[min(b.size() - 1, i)]; break;
        }
    }
    return from_byte(res);
}

big_integer leftShift(const big_integer::vector &a, int shift)
{
    big_integer::vector res(shift / BASEPOW, 0);
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

big_integer rightShift(const big_integer::vector &a, int shift)
{
    big_integer::vector res;
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

int big_integer::sign() const {
    return data.sign();
}
unsigned big_integer::size() const {
    return data.size();
}
int big_integer::mode() const {
    return data.mode();
}

void big_integer::set_sign(unsigned x) {
    data.set_sign(x);
}
void big_integer::set_size(unsigned x) {
    data.set_size(x);
}
void big_integer::set_mode(int x) {
    data.set_mode(x);
}



big_integer::big_integer() : data(1, 0, 0) {
}

big_integer::big_integer(int sign, const vector &other) : data(other) {
    data.set_sign(sign);
    set_sign(normalize(data, sign));
}

big_integer::big_integer(big_integer const& other) : data(other.data) {}

big_integer::big_integer(int a) : data(1, abs(a), a < 0) {
}

big_integer ONE(1);

big_integer::big_integer(std::string const& str) {
    vector temp;
    for (auto x : str)
    {
        if (x == '-')
        {
            data.set_sign(1);
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
        data.push_back(mod);
    }
    data.set_sign(normalize(data, data.sign()));
}

big_integer::~big_integer() {}

big_integer& big_integer::operator=(big_integer const& other)
{
    data = other.data;
    return *this;
}

big_integer& big_integer::operator+=(big_integer const& rhs)
{
    if (sign() == rhs.sign())
    {
        add(data, data, rhs.data);
    }
    else if (comp(*this, rhs, true) < 0)
    {
        subtract(data, rhs.data, data);
        set_sign(rhs.sign());
    }
    else
    {
        subtract(data, data, rhs.data);
    }
    set_sign(normalize(data, sign()));
    return *this;
}

big_integer& big_integer::operator-=(big_integer const& rhs)
{
    return *this += -rhs;
}

big_integer& big_integer::operator*=(big_integer const& rhs)
{
    multiply(data, data, rhs.data);
//    std::cout << signum << ' ' << rhs.sign() << "\n";
    set_sign(normalize(data, sign() ^ rhs.sign()));
    return *this;
}

big_integer& big_integer::operator/=(big_integer const& rhs)
{
    longDiv(data, data, rhs.data);
    set_sign(normalize(data, sign() ^ rhs.sign()));
    return *this;
}

big_integer& big_integer::operator%=(big_integer const& rhs)
{
    return (*this = *this - (*this / rhs) * rhs);
}

big_integer& big_integer::operator&=(big_integer const& rhs)
{
    return *this = byteFunctionBigInteger(to_byte(sign(), data), to_byte(rhs.sign(), rhs.data), AND);
}

big_integer& big_integer::operator|=(big_integer const& rhs)
{
    return (*this = byteFunctionBigInteger(to_byte(sign(), data), to_byte(rhs.sign(), rhs.data), OR));
}

big_integer& big_integer::operator^=(big_integer const& rhs)
{
    return (*this = byteFunctionBigInteger(to_byte(sign(), data), to_byte(rhs.sign(), rhs.data), XOR));
}

big_integer& big_integer::operator<<=(int rhs)
{
    return (*this = leftShift(to_byte(sign(), data), rhs));
}

big_integer& big_integer::operator>>=(int rhs)
{

    return (*this = rightShift(to_byte(sign(), data), rhs));
}

big_integer big_integer::operator+() const
{
    return *this;
}

big_integer big_integer::operator-() const
{
    return big_integer(sign() ^ 1, data);
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

bool operator==(big_integer const& a, big_integer const& b) {
    return !comp(a, b);
}

bool operator!=(big_integer const& a, big_integer const& b) {
    return comp(a, b);
}

bool operator<(big_integer const& a, big_integer const& b) {
    return comp(a, b) < 0;
}

bool operator>(big_integer const& a, big_integer const& b) {
    return comp(a, b) > 0;
}

bool operator<=(big_integer const& a, big_integer const& b) {
    return comp(a, b) <= 0;
}

bool operator>=(big_integer const& a, big_integer const& b) {
    return comp(a, b) >= 0;
}

std::string to_string(big_integer const& a) {
    string res;
    big_integer::vector v = a.data;
    unsigned mod = 0;
    while (v.size() != 1 || v[0] != 0) {
        mod = shortDivMod(BASE, 10, v, v, mod);
        res += (char)(mod + 48);
    }

    if (a.sign() == 1) {
       res += "-";
    }
    reverse(res.begin(), res.end());
    return (res.empty() ? "0" : res);
}

std::ostream& operator<<(std::ostream& s, big_integer const& a) {
    return s << to_string(a);
}
std::istream& operator>>(std::istream &s, big_integer &a) {
    std::string d;
    s >> d;
    a = big_integer(d);
    return s;
}


template <typename T>
void erase_unordered(std::vector<T>& v, typename std::vector<T>::iterator pos)
{
    std::swap(v.back(), *pos);
    v.pop_back();
}

template <typename T>
T extract_random_element(std::vector<T>& v)
{
    size_t index = rand() % v.size();
    T copy = v[index];
    erase_unordered(v, v.begin() + index);
    return copy;
}


template <typename T>
void merge_two(std::vector<T>& v)
{
    assert(v.size() >= 2);

    T a = extract_random_element(v);
    T b = extract_random_element(v);

    T ab = a * b;
    cout << a << ' ' << b << "\n";
    assert(ab / a == b);
    assert(ab / b == a);

    v.push_back(ab);
}

template <typename T>
T merge_all(std::vector<T> v)
{
    assert(!v.empty());

    while (v.size() >= 2)
        merge_two(v);

    return v[0];
}
//int main() {
////    vector<big_integer> v = {-430978730, 692328763, 590472204, 830750726, 189642432};
//    big_integer x("11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111");
//    big_integer y("22222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222");
//    cout << x << ' ' << y << "\n";
//    y /= x;
//    cout << y << "\n";
////    cout << x << "\n";
////    cout << x * y << "\n";
////    cout << 830750726 * 590472204ll << "\n";
////    big_integer x = merge_all(v);
////    big_integer y = merge_all(v);
////    for (auto x : v) {
//
////    }
//
//}
