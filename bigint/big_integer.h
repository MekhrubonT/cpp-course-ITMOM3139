#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

// Список инициализации

struct big_integer {
friend int main();

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

    struct vector {
        struct node {
            unsigned *s;
            unsigned capacity;
        };

        void update_capacity(unsigned, unsigned);
        void ensure_capacity(unsigned);
        const static unsigned SIGN_BIT = 30;
        const static unsigned MODE_BIT = 31;
        const static unsigned SIZE_CONST = ~0 ^ (1 << SIGN_BIT) ^ (1 << MODE_BIT);
        const static unsigned SMALL_OBJECT = 0;
        const static unsigned SMALL_OBJECT_SIZE = sizeof(node) / sizeof(unsigned);

        void flip_to_small_object();
        void flip_from_small_object(unsigned, unsigned);

        vector();
        ~vector();
        template <typename T>
        vector(const T& x);
        vector(const vector& x);


        vector(unsigned, unsigned, int sign);
        vector& operator=(vector const &other);
        union {
            node x;
            unsigned small[SMALL_OBJECT_SIZE];
        };

        void push_back(unsigned);
        void insert(unsigned*, int x);
        void resize(unsigned);
        void pop_back();
        void clear();

        unsigned size() const;
        int sign() const;
        int mode() const;

        void set_size(unsigned d);
        void set_mode(unsigned x);
        void set_sign(unsigned x);

        unsigned& back();
        const unsigned back() const;
        bool empty() const;


        unsigned* begin();
        unsigned const* begin() const;
        unsigned* end();
        unsigned const* end() const;

        unsigned& operator[](unsigned ind);
        unsigned const operator[](unsigned ind) const;
        unsigned sz;
        unsigned* def;
    } data;

    friend void swap(vector&, vector&);
    friend vector to_byte(int sign, vector v);

    int sign() const;
    unsigned size() const;
    int mode() const;
    void set_sign(unsigned);
    void set_size(unsigned);
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
    friend unsigned shortDivMod(const int64_t, const int64_t, const big_integer::vector&, big_integer::vector&, unsigned);
    friend void longDiv(big_integer::vector&, const big_integer::vector, const big_integer::vector&);


//    int signum; // private
//    std::vector<unsigned> v; // private
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
