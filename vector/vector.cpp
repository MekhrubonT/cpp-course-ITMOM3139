#include <string>
#include "vector.h"

vector::vector(size_t capacity, size_t size) :
_capacity(capacity), _size(size),
 a(((std::string*) operator new(_capacity * sizeof(std::string)))) {}

vector::vector() : vector::vector(10, 0) {}

void swap(vector &lhs, vector &rhs)
{
    std::swap(lhs.a, rhs.a);
    std::swap(lhs._capacity, rhs._capacity);
    std::swap(lhs._size, rhs._size);
}

vector::vector(vector const& other) : vector(other.capacity(), other.size())
{
    size_t pos;
    try
    {
        for (pos = 0; pos < other.size(); pos++)
        {
            new(a + pos) std::string(other[pos]);
        }
    }
    catch (...)
    {
        _size = pos;
        throw;
    }
}

vector::~vector()
{
    for (size_t pos = 0; pos < _size; pos++)
    {
        a[pos].std::string::~string();
    }
    operator delete (a);
}

vector& vector::operator=(vector other)
{
    swap(*this, other);
    return *this;
}

void emplace_capacity(vector &a, size_t _capacity)
{
    vector buf(_capacity * 2, 0);
    for (size_t pos = 0; pos < a.size(); pos++)
    {
        buf.push_back(a[pos]);
    }
    swap(a, buf);
}

void vector::push_back(std::string const& other)
{
    if (_size == _capacity)
    {
        emplace_capacity(*this, _capacity);
        _capacity *= 2;
    }
    new(a + _size) std::string(other);
    _size++;
}

void vector::pop_back()
{
    _size--;
    a[_size].std::string::~string();
}

std::string const& vector::back() const
{
    return a[_size - 1];
}

std::string & vector::back()
{
    return a[_size - 1];
}

std::string const& vector::front() const
{
    return a[0];
}

std::string & vector::front()
{
    return a[0];
}

bool vector::empty() const
{
    return _size == 0;
}

size_t vector::size() const
{
    return _size;
}

size_t vector::capacity() const
{
    return _capacity;
}

std::string const& vector::operator[](size_t pos) const
{
    return a[pos];
}

std::string& vector::operator[](size_t pos)
{
    return a[pos];
}

std::string* vector::begin()
{
    return a;
}

std::string* vector::end()
{
    return a + _size;
}

const std::string* vector::begin() const
{
    return a;
}

const std::string* vector::end() const
{
    return a + _size;
}

void vector::erase(std::string* pos)
{
    while (pos != end())
    {
        std::string* cur = pos++;
        if (pos == end())
        {
            cur->std::string::~string();
        }
        else
        {
            swap(*cur, *pos);
        }
    }
    _size--;
}

std::string* vector::insert(std::string* pos, std::string& x)
{
    if (_size == _capacity)
    {
        emplace_capacity(*this, _capacity);
    }
    new (end()) std::string(x);
    for (auto x = end(); x > pos;)
    {
        auto prev = x--;
        swap(*prev, *x);
    }
    _size++;
    return pos;
}

void vector::erase(std::string* _begin, std::string* _end)
{
    while (_end != end())
    {
        swap(*_begin, *_end);
        _begin++;
        _end++;
    }
    size_t length = _end - _begin;
    while (_begin != _end)
    {
        _begin->std::string::~string();
        _begin++;
    }
    _size -= length;

}

void vector::clear()
{
    vector empty_vector = vector();
    swap(*this, empty_vector);
}

