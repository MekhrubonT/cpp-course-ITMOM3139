#ifndef MY_VECTOR_H
#define MY_VECTOR_H


struct vector
{
    vector();

    vector(vector const&);

    ~vector();

    vector& operator=(vector);

    void push_back(std::string const&);

    void pop_back();

    std::string const& back() const;

    std::string& back();

    std::string const& front() const;

    std::string& front();

    bool empty() const;

    size_t size() const;

    size_t capacity() const;

    std::string const& operator[](size_t) const;

    std::string& operator[](size_t);

    std::string* begin();
//
    std::string* end();

    const std::string* begin() const;

    const std::string* end() const;

    void erase(std::string*);

    std::string* insert(std::string*, std::string&);

    void erase(std::string*, std::string*);

    void clear();


private:

    friend void emplace_capacity(std::string* &a, size_t _capacity);

    friend void swap(vector &lhs, vector &rhs);

    vector(size_t cpct, size_t sz);

    size_t _capacity;
    size_t _size;
    std::string *a;
};

#endif // MY_VECTOR_H
