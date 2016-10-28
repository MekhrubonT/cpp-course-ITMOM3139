#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

#include <memory>
// Список инициализации

struct big_integer {
friend int main();
    typedef unsigned value_type;

    big_integer();

    big_integer(big_integer const& other);
    big_integer(int a);
    explicit big_integer(std::string const& str);
    ~big_integer();


    big_integer& operator=(big_integer const& other);

    big_integer& operator+=(big_integer const& rhs);
    big_integer& operator-=(big_integer const& rhs);
    big_integer& operator*=(big_integer const& rhs);
    big_integer& operator/=(big_integer const& rhs);
    big_integer& operator%=(big_integer const& rhs);

    big_integer& operator&=(big_integer const& rhs);
    big_integer& operator|=(big_integer const& rhs);
    big_integer& operator^=(big_integer const& rhs);

    big_integer& operator<<=(int rhs);
    big_integer& operator>>=(int rhs);

    big_integer operator+() const;
    big_integer operator-() const;
    big_integer operator~() const;

    big_integer& operator++();
    big_integer operator++(int);

    big_integer& operator--();
    big_integer operator--(int);

    friend bool operator==(big_integer const& a, big_integer const& b);
    friend bool operator!=(big_integer const& a, big_integer const& b);
    friend bool operator<(big_integer const& a, big_integer const& b);
    friend bool operator>(big_integer const& a, big_integer const& b);
    friend bool operator<=(big_integer const& a, big_integer const& b);
    friend bool operator>=(big_integer const& a, big_integer const& b);



    friend std::string to_string(big_integer const& a);
//private:
//
    struct vector {
        struct node {
            std::shared_ptr<value_type> s;
            value_type capacity;
        };

        void update_capacity(value_type, value_type);
        void ensure_capacity(value_type);
        const static value_type SIGN_BIT = sizeof(value_type) * 8 - 2;
        const static value_type MODE_BIT = sizeof(value_type) * 8 - 1;
        const static value_type SIZE_CONST = ~0 ^ (1 << SIGN_BIT) ^ (1 << MODE_BIT);
        const static value_type SMALL_OBJECT = 0;
        const static value_type SMALL_OBJECT_SIZE = sizeof(node) / sizeof(value_type);

        void flip_to_small_object();
        void flip_from_small_object(value_type, value_type);

        vector();
        ~vector();
        vector(const vector& x);


        vector(value_type, value_type, int sign);
        vector& operator=(vector const &other);
        union {
            value_type small[SMALL_OBJECT_SIZE];
            node x;
        };

        void push_back(value_type);
        void insert(value_type*, int x);
        void resize(value_type);
        void pop_back();
        void clear();

        value_type size() const;
        int sign() const;
        int mode() const;

        void set_size(value_type d);
        void set_mode(value_type x);
        void set_sign(value_type x);

        value_type& back();
        const value_type back() const;
        bool empty() const;


        value_type* begin();
        value_type const* begin() const;
        value_type* end();
        value_type const* end() const;

        value_type& operator[](value_type ind);
        value_type const operator[](value_type ind) const;
        value_type sz;
    };
    vector data;

    friend void swap(vector&, vector&);
    friend vector to_byte(int sign, vector v);

    int sign() const;
    value_type size() const;
    int mode() const;
    void set_sign(value_type);
    void set_size(value_type);
    void set_mode(int);

    enum operation { XOR, OR, AND };

    friend big_integer byteFunctionBigInteger(const big_integer::vector &a, const big_integer::vector &b, operation op);
    friend big_integer leftShift(const vector &a, int shift);
    friend big_integer rightShift(const vector &a, int shift);

    big_integer(int sign, const big_integer::vector &other);


    friend big_integer from_byte(vector&);
    friend int comp(const big_integer::vector& a, const big_integer::vector &b, bool absCompare);
    friend int comp(big_integer const& a, big_integer const& b, bool absCompare);
    friend int normalize(big_integer::vector&, int);
    friend void add(big_integer::vector &res, const big_integer::vector &a, const big_integer::vector &b);
    friend void subtract(big_integer::vector &res, const big_integer::vector &a, const big_integer::vector &b);
    friend void multiplyShort(big_integer::vector&, const big_integer::vector&, uint64_t);
    friend void multiply(big_integer::vector&, const big_integer::vector&, const big_integer::vector&);
    friend value_type shortDivMod(const int64_t, const int64_t, const big_integer::vector&, big_integer::vector&, value_type);
    friend void longDiv(big_integer::vector&, const big_integer::vector, const big_integer::vector&);
};

void swap(big_integer::vector& a, big_integer::vector& b);

bool operator==(big_integer const& a, big_integer const& b);

bool operator!=(big_integer const& a, big_integer const& b);

bool operator<(big_integer const& a, big_integer const& b);

bool operator>(big_integer const& a, big_integer const& b);

bool operator<=(big_integer const& a, big_integer const& b);

bool operator>=(big_integer const& a, big_integer const& b);


big_integer operator+(big_integer a, big_integer const& b);

big_integer operator-(big_integer a, big_integer const& b);

big_integer operator*(big_integer a, big_integer const& b);

big_integer operator/(big_integer a, big_integer const& b);

big_integer operator%(big_integer a, big_integer const& b);

big_integer operator&(big_integer a, big_integer const& b);

big_integer operator|(big_integer a, big_integer const& b);

big_integer operator^(big_integer a, big_integer const& b);

big_integer operator<<(big_integer a, int b);

big_integer operator>>(big_integer a, int b);

std::ostream& operator<<(std::ostream& s, big_integer const& a);
#endif // BIG_INTEGER_H
