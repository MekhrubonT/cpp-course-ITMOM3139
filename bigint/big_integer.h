#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

// Список инициализации

struct big_integer {
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





private:
    size_t size() const
    {
        return v.size();
    }

    friend big_integer from_byte(std::vector<unsigned> &v);

    big_integer(int sign, const std::vector<unsigned>& other);

    friend void longDiv(std::vector<unsigned> &res, const std::vector<unsigned> a, const std::vector<unsigned> &b);

    friend big_integer from_byte(std::vector<unsigned> v);

    int sign() const { // private
        return signum;
    }

    friend int comp(big_integer const& a, big_integer const& b, bool absCompare);

    int signum; // private
    std::vector<unsigned> v; // private
};

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


std::string to_string(big_integer const& a);
std::ostream& operator<<(std::ostream& s, big_integer const& a);
#endif // BIG_INTEGER_H
