#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

struct big_integer {
    big_integer();

    big_integer(int sign, const std::vector<int> &other);
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

    size_t size() const {
        return v.size();
    }

    int sign() const {
        return signum;
    }

    int bucket(int pos) const {
        return v[pos];
    }


private:
    std::vector<int> v;
    int signum;
    friend int comp(big_integer const& a, big_integer const& b, bool absCompare);
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
