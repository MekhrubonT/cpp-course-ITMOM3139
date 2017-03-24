#include <iostream>
#include <list>
#include <cstdlib>
#include <cstdio>
#include <memory.h>
#include <cassert>
#include "list.h"





list::it_list::it_node::it_node (iterator* key) : key(key), prev(this), next(this) {}
list::it_list::it_node::it_node (iterator* key, it_node* prev, it_node* next) : key(key), prev(prev), next(next) {}
list::it_list::it_node::it_node (iterator* key, it_node const &other) : it_node(key, other.prev, other.next) {}
list::it_list::it_node::it_node (const it_node& other) : it_node(other.key, other.prev, other.next) {}
list::it_list::it_node::~it_node() {}

bool list::it_list::it_node::operator==(const it_node& b)
{
    return key == b.key && prev == b.prev && next == b.next;
}

list::it_list::it_iterator::it_iterator (iterator* key) : cur(new it_node(key)) {}
list::it_list::it_iterator::it_iterator (it_node& other) : cur(&other) {}
list::it_list::it_iterator::it_iterator (iterator* key, const it_iterator &other) : cur(new it_node(key, *other.cur)) {}
list::it_list::it_iterator::it_iterator (const it_iterator& other) : cur(other.cur) {}
list::it_list::it_iterator::it_iterator (iterator* key, const it_iterator &prev, const it_iterator &next) : cur(new it_node(key, prev.cur, next.cur)) {}
list::it_list::it_iterator::~it_iterator ()
{
}


void list::it_list::it_iterator::swap(it_iterator &b)
{
    std::swap(cur, b.cur);
}

list::it_list::it_iterator list::it_list::it_iterator::operator=(it_iterator other)
{
    this->swap(other);
    return *this;
}


bool list::it_list::it_iterator::operator==(const it_iterator &b)
{
    return cur == b.cur;
}

bool list::it_list::it_iterator::operator!=(const it_iterator &b)
{
    return cur != b.cur;
}

list::it_list::it_iterator& list::it_list::it_iterator::operator++()
{
    cur = cur->next;
    return *this;
}
list::it_list::it_iterator list::it_list::it_iterator::operator++(int)
{
    it_iterator cp = *this;
    ++*this;
    return cp;
}
list::it_list::it_iterator& list::it_list::it_iterator::operator--()
{
    cur = cur->prev;
    return *this;
}
list::it_list::it_iterator list::it_list::it_iterator::operator--(int)
{
    it_iterator cp = *this;
    --*this;
    return cp;
}
list::iterator* list::it_list::it_iterator::operator*()
{
    return cur->key;
}


list::it_list::const_it_iterator::const_it_iterator (iterator* key) : cur(new it_node(key)) {}
list::it_list::const_it_iterator::const_it_iterator (it_node& other) : cur(&other) {}
list::it_list::const_it_iterator::const_it_iterator (iterator* key, const const_it_iterator &other) : cur(new it_node(key, *other.cur)) {}
list::it_list::const_it_iterator::const_it_iterator (const const_it_iterator& other) : cur(other.cur) {}
list::it_list::const_it_iterator::const_it_iterator (iterator* key, const const_it_iterator &prev, const const_it_iterator &next) : cur(new it_node(key, prev.cur, next.cur)) {}
list::it_list::const_it_iterator::~const_it_iterator () {}


void list::it_list::const_it_iterator::swap(const_it_iterator &b)
{
    std::swap(cur, b.cur);
}

list::it_list::const_it_iterator list::it_list::const_it_iterator::operator=(const_it_iterator other)
{
    this->cur = other.cur;
    return *this;
}

bool list::it_list::const_it_iterator::operator==(const const_it_iterator &b)
{
    return cur == b.cur;
}

bool list::it_list::const_it_iterator::operator!=(const const_it_iterator &b)
{
    return cur != b.cur;
}

list::it_list::const_it_iterator& list::it_list::const_it_iterator::operator++()
{
    cur = cur->next;
    return *this;
}
list::it_list::const_it_iterator list::it_list::const_it_iterator::operator++(int)
{
    const_it_iterator cp = *this;
    ++*this;
    return cp;
}
list::it_list::const_it_iterator& list::it_list::const_it_iterator::operator--()
{
    cur = cur->prev;
    return *this;
}
list::it_list::const_it_iterator list::it_list::const_it_iterator::operator--(int)
{
    const_it_iterator cp = *this;
    --*this;
    return cp;
}
list::iterator* list::it_list::const_it_iterator::operator*()
{
    return cur->key;
}

list::it_list::it_list() : head(nullptr), tail(head) {}

list::it_list::it_list(list::it_list const &my_it_list) : list::it_list()
{
    list::it_list other;
    for (auto x : my_it_list)
        other.push_back(x);
    this->swap(other);
}

list::it_list::~it_list()
{
//    std::cout << "~list::it_list\n";
    clear();
    delete head.cur;
}

list::it_list& list::it_list::operator=(const list::it_list & s)
{
    list::it_list(s).swap(*this);
    return *this;
}


void list::it_list::swap(list::it_list &b)
{
    head.swap(b.head);
    tail.swap(b.tail);
}

list::it_list::it_iterator list::it_list::begin()
{
    return head;
}

list::it_list::const_it_iterator list::it_list::begin() const
{
    return const_it_iterator(*head.cur);
}

list::it_list::it_iterator list::it_list::end()
{
    return tail;
}

list::it_list::const_it_iterator list::it_list::end() const
{
    return list::it_list::const_it_iterator(*tail.cur);
}

list::it_list::it_iterator list::it_list::insert(it_iterator pr, iterator* s)
{
    if (empty())
    {
        head.cur = new it_node(s, tail.cur, tail.cur);
        tail.cur->prev = tail.cur->next = head.cur;
        return head;
    }
    else if (pr == begin())
    {
        it_iterator temp(s, tail, pr);
        pr.cur->prev = temp.cur;
        head.cur = temp.cur;
        return temp;
    }
    else
    {
        it_iterator pos = pr--;
        it_iterator temp(s, pr, pos);
        pos.cur->prev = pr.cur->next = temp.cur;
        return temp;
    }
}

list::it_list::it_iterator list::it_list::erase(it_iterator pos)
{
    it_iterator x = pos;
    x++;
    if (++begin() == end())
    {
        delete head.cur;
        tail.cur->next = tail.cur->prev = head.cur = tail.cur;
    }
    else
    {
        pos.cur->prev->next = pos.cur->next;
        pos.cur->next->prev = pos.cur->prev;
        if (head == pos)
        {
            head.cur = pos.cur->next;
        }
        delete pos.cur;
    }
    return x;
}

void list::it_list::push_front(iterator* s)
{
    insert(head, s);
}

void list::it_list::pop_front()
{
    assert(!empty());
    erase(head);
}

void list::it_list::push_back(iterator* s)
{
    insert(tail, s);
}

void list::it_list::pop_back()
{
    assert(!empty());
    erase(--end());
}

bool list::it_list::empty() const
{
    return (begin() == end());
}

void list::it_list::clear()
{
    while (!empty())
    {
        pop_back();
    }
}


list::constit_list::constit_node::constit_node (const_iterator* key) : key(key), prev(this), next(this) {}
list::constit_list::constit_node::constit_node (const_iterator* key, constit_node* prev, constit_node* next) : key(key), prev(prev), next(next) {}
list::constit_list::constit_node::constit_node (const_iterator* key, constit_node const &other) : constit_node(key, other.prev, other.next) {}
list::constit_list::constit_node::constit_node (const constit_node& other) : constit_node(other.key, other.prev, other.next) {}
list::constit_list::constit_node::~constit_node() {}

bool list::constit_list::constit_node::operator==(const constit_node& b)
{
    return key == b.key && prev == b.prev && next == b.next;
}

list::constit_list::constit_iterator::constit_iterator (list::constit_list* obj, const_iterator* key) : cur(new constit_node(key)), my_object(obj), flag(true)
{
}
list::constit_list::constit_iterator::constit_iterator (constit_node& other, list::constit_list* obj) : cur(&other), my_object(obj), flag(true)
{
}
list::constit_list::constit_iterator::constit_iterator (const_iterator* key, const constit_iterator &other) : cur(new constit_node(key, *other.cur)), my_object(other.my_object), flag(true)
{
}
list::constit_list::constit_iterator::constit_iterator (const constit_iterator& other) : cur(other.cur), my_object(other.my_object), flag(other.flag)
{
}
list::constit_list::constit_iterator::constit_iterator (const_iterator* key, const constit_iterator &prev, const constit_iterator &next, list::constit_list *obj) : cur(new constit_node(key, prev.cur, next.cur)), my_object(obj), flag(true)
{
}
list::constit_list::constit_iterator::~constit_iterator ()
{
}


void list::constit_list::constit_iterator::swap(constit_iterator &b)
{
    std::swap(cur, b.cur);
}

list::constit_list::constit_iterator list::constit_list::constit_iterator::operator=(constit_iterator other)
{
    this->swap(other);
    return *this;
}


bool list::constit_list::constit_iterator::operator==(const constit_iterator &b)
{
    return cur == b.cur && my_object == b.my_object && flag == b.flag;
}

bool list::constit_list::constit_iterator::operator!=(const constit_iterator &b)
{
    return cur != b.cur || my_object != b.my_object || flag != b.flag;
}

list::constit_list::constit_iterator& list::constit_list::constit_iterator::operator++()
{
    cur = cur->next;
    return *this;
}
list::constit_list::constit_iterator list::constit_list::constit_iterator::operator++(int)
{
    constit_iterator cp = *this;
    ++*this;
    return cp;
}
list::constit_list::constit_iterator& list::constit_list::constit_iterator::operator--()
{
    cur = cur->prev;
    return *this;
}
list::constit_list::constit_iterator list::constit_list::constit_iterator::operator--(int)
{
    constit_iterator cp = *this;
    --*this;
    return cp;
}
list::const_iterator* list::constit_list::constit_iterator::operator*()
{
    assert(flag && *this != my_object->end());
    return cur->key;
}


list::constit_list::const_it_iterator::const_it_iterator (const list::constit_list* obj, const_iterator* key) : cur(new constit_node(key)), my_object(obj), flag(false)
{
}
list::constit_list::const_it_iterator::const_it_iterator (constit_node& other, const list::constit_list* obj) : cur(&other), my_object(obj), flag(true)
{
}
list::constit_list::const_it_iterator::const_it_iterator (const_iterator* key, const const_it_iterator &other) : cur(new constit_node(key, *other.cur)), my_object(other.my_object), flag(false)
{
}
list::constit_list::const_it_iterator::const_it_iterator (const const_it_iterator& other) : cur(other.cur), my_object(other.my_object), flag(other.flag)
{
}
list::constit_list::const_it_iterator::const_it_iterator (const_iterator* key, const const_it_iterator &prev, const const_it_iterator &next, const list::constit_list *obj) : cur(new constit_node(key, prev.cur, next.cur)), my_object(obj), flag(false)
{
}
list::constit_list::const_it_iterator::~const_it_iterator ()
{
}


void list::constit_list::const_it_iterator::swap(const_it_iterator &b)
{
    std::swap(cur, b.cur);
}

list::constit_list::const_it_iterator list::constit_list::const_it_iterator::operator=(const_it_iterator other)
{
    this->cur = other.cur;
    return *this;
}

bool list::constit_list::const_it_iterator::operator==(const const_it_iterator &b)
{
    return cur == b.cur;
}

bool list::constit_list::const_it_iterator::operator!=(const const_it_iterator &b)
{
    return cur != b.cur;
}

list::constit_list::const_it_iterator& list::constit_list::const_it_iterator::operator++()
{
    cur = cur->next;
    return *this;
}
list::constit_list::const_it_iterator list::constit_list::const_it_iterator::operator++(int)
{
    const_it_iterator cp = *this;
    ++*this;
    return cp;
}
list::constit_list::const_it_iterator& list::constit_list::const_it_iterator::operator--()
{
    cur = cur->prev;
    return *this;
}
list::constit_list::const_it_iterator list::constit_list::const_it_iterator::operator--(int)
{
    const_it_iterator cp = *this;
    --*this;
    return cp;
}
list::const_iterator* list::constit_list::const_it_iterator::operator*()
{
    return cur->key;
}

list::constit_list::constit_list() : head(this, nullptr), tail(head) {
}

list::constit_list::constit_list(list::constit_list const &my_it_list) : list::constit_list()
{
    list::constit_list other;
    for (auto x : my_it_list)
        other.push_back(x);
    this->swap(other);
}

list::constit_list::~constit_list()
{
//    std::cout << "~list::constit_list\n";
    clear();
    delete head.cur;
}

list::constit_list& list::constit_list::operator=(const list::constit_list & s)
{
    list::constit_list(s).swap(*this);
    return *this;
}


void list::constit_list::swap(list::constit_list &b)
{
    head.swap(b.head);
    tail.swap(b.tail);
}

list::constit_list::constit_iterator list::constit_list::begin()
{
    return head;
}

list::constit_list::const_it_iterator list::constit_list::begin() const
{
    return const_it_iterator(*head.cur, this);
}

list::constit_list::constit_iterator list::constit_list::end()
{
    return tail;
}

list::constit_list::const_it_iterator list::constit_list::end() const
{
    return list::constit_list::const_it_iterator(*tail.cur, this);
}

list::constit_list::constit_iterator list::constit_list::insert(constit_iterator pr, const_iterator* s)
{
    assert(pr.flag && pr.my_object == this);
    if (empty())
    {
        head.cur = new constit_node(s, tail.cur, tail.cur);
        tail.cur->prev = tail.cur->next = head.cur;
        return head;
    }
    else if (pr == begin())
    {
        constit_iterator temp(s, tail, pr, this);
        pr.cur->prev = temp.cur;
        head.cur = temp.cur;
        return temp;
    }
    else
    {
        constit_iterator pos = pr--;
        constit_iterator temp(s, pr, pos, this);
        pos.cur->prev = pr.cur->next = temp.cur;
        return temp;
    }
}

list::constit_list::constit_iterator list::constit_list::erase(constit_iterator pos)
{
    constit_iterator x = pos;
    x++;
    if (++begin() == end())
    {
        delete head.cur;
        tail.cur->next = tail.cur->prev = head.cur = tail.cur;
    }
    else
    {
        pos.cur->prev->next = pos.cur->next;
        pos.cur->next->prev = pos.cur->prev;
        if (head == pos)
        {
            head.cur = pos.cur->next;
        }
        delete pos.cur;
    }
    return x;
}

void list::constit_list::push_front(const_iterator* s)
{
    insert(head, s);
}

void list::constit_list::pop_front()
{
    assert(!empty());
    erase(head);
}

void list::constit_list::push_back(const_iterator* s)
{
    insert(tail, s);
}

void list::constit_list::pop_back()
{
    assert(!empty());
    erase(--end());
}

bool list::constit_list::empty() const
{
    return (begin() == end());
}


void list::constit_list::clear()
{
    while (!empty())
    {
        pop_back();
    }
}



list::node::node (const std::string &key) : key(key), prev(this), next(this) {}
list::node::node (const std::string &key, node* prev, node* next) : key(key), prev(prev), next(next) {}
list::node::node (const std::string &key, node const &other) : node(key, other.prev, other.next) {}
list::node::node (const node& other) : node(other.key, other.prev, other.next) {}
list::node::~node() {}

bool list::node::operator==(const node& b)
{
    return key == b.key && prev == b.prev && next == b.next;
}

list::iterator::iterator (list* obj, const std::string &key) : cur(new node(key)), my_object(obj), flag(true)
{
    my_object->v.push_back(this);
}
list::iterator::iterator (node& other, list* obj) : cur(&other), my_object(obj), flag(true)
{
    my_object->v.push_back(this);
}
list::iterator::iterator (const std::string &key, const iterator &other) : cur(new node(key, *other.cur)), my_object(other.my_object), flag(true)
{
    my_object->v.push_back(this);
}
list::iterator::iterator (const iterator& other) : cur(other.cur), my_object(other.my_object), flag(other.flag)
{
    my_object->v.push_back(this);
}
list::iterator::iterator (const std::string &key, const iterator &prev, const iterator &next, list *obj) : cur(new node(key, prev.cur, next.cur)), my_object(obj), flag(true)
{
    my_object->v.push_back(this);
}
list::iterator::~iterator ()
{
    for (auto it = my_object->v.begin(); it != my_object->v.end();)
    {
        auto cur = it++;
        if (*cur == this)
        {
            my_object->v.erase(cur);
        }
    }
}


void list::iterator::swap(iterator &b)
{
    std::swap(cur, b.cur);
    std::swap(my_object, b.my_object);
    std::swap(flag, b.flag);
}

list::iterator list::iterator::operator=(iterator other)
{
    this->swap(other);
    return *this;
}


bool list::iterator::operator==(const iterator &b)
{
    return cur == b.cur && my_object == b.my_object && flag == b.flag;
}

bool list::iterator::operator!=(const iterator &b)
{
    return cur != b.cur || my_object != b.my_object || flag != b.flag;
}

list::iterator& list::iterator::operator++()
{
    assert(flag && *this != my_object->end() && "Operator ++");
    cur = cur->next;
    return *this;
}
list::iterator list::iterator::operator++(int)
{
    iterator cp = *this;
    ++*this;
    return cp;
}
list::iterator& list::iterator::operator--()
{
    assert(flag && *this != my_object->begin() && "Operator --");
    cur = cur->prev;
    return *this;
}
list::iterator list::iterator::operator--(int)
{
    iterator cp = *this;
    --*this;
    return cp;
}
std::string& list::iterator::operator*()
{
    assert(flag && *this != my_object->end());
    return cur->key;
}


list::const_iterator::const_iterator (const list* obj, const std::string &key) : cur(new node(key)), my_object(obj), flag(false)
{
    my_object->cv.push_back(this);
}
list::const_iterator::const_iterator (node& other, const list* obj) : cur(&other), my_object(obj), flag(true)
{
    my_object->cv.push_back(this);
}
list::const_iterator::const_iterator (const std::string &key, const const_iterator &other) : cur(new node(key, *other.cur)), my_object(other.my_object), flag(false)
{
    my_object->cv.push_back(this);
}
list::const_iterator::const_iterator (const const_iterator& other) : cur(other.cur), my_object(other.my_object), flag(other.flag)
{
    my_object->cv.push_back(this);
}
list::const_iterator::const_iterator (const std::string &key, const const_iterator &prev, const const_iterator &next, const list *obj) : cur(new node(key, prev.cur, next.cur)), my_object(obj), flag(false)
{
    my_object->cv.push_back(this);
}
list::const_iterator::~const_iterator ()
{
    for (auto it = my_object->cv.begin(); it != my_object->cv.end();)
    {
        auto cur = it++;
        if (*cur == this)
        {
            my_object->cv.erase(cur);
        }
    }
}


void list::const_iterator::swap(const_iterator &b)
{
    std::swap(cur, b.cur);
}

list::const_iterator list::const_iterator::operator=(const_iterator other)
{
    this->cur = other.cur;
    return *this;
}

bool list::const_iterator::operator==(const const_iterator &b)
{
    return cur == b.cur;
}

bool list::const_iterator::operator!=(const const_iterator &b)
{
    return cur != b.cur;
}

list::const_iterator& list::const_iterator::operator++()
{
    cur = cur->next;
    return *this;
}
list::const_iterator list::const_iterator::operator++(int)
{
    const_iterator cp = *this;
    ++*this;
    return cp;
}
list::const_iterator& list::const_iterator::operator--()
{
    cur = cur->prev;
    return *this;
}
list::const_iterator list::const_iterator::operator--(int)
{
    const_iterator cp = *this;
    --*this;
    return cp;
}
const std::string& list::const_iterator::operator*()
{
    assert(flag && *this != my_object->end());
    return cur->key;
}

list::list() : head(this, std::string()), tail(head) {
}

list::list(list const &my_list) : list()
{
    list other;
    for (auto x : my_list)
        other.push_back(x);
    this->swap(other);
}

list::~list()
{
//    std::cout << "~list\n";
//    clear();
//    delete head.cur;
}

list& list::operator=(const list & s)
{
    list(s).swap(*this);
    return *this;
}


void list::swap(list &b)
{
    head.swap(b.head);
    tail.swap(b.tail);
}

list::iterator list::begin()
{
    return head;
}

list::const_iterator list::begin() const
{
    return const_iterator(*head.cur, this);
}

list::iterator list::end()
{
    return tail;
}

list::const_iterator list::end() const
{
    return list::const_iterator(*tail.cur, this);
}

list::iterator list::insert(iterator pr, std::string const &s)
{
    assert(pr.flag && pr.my_object == this);
    if (empty())
    {
        head.cur = new node(s, tail.cur, tail.cur);
        tail.cur->prev = tail.cur->next = head.cur;
        return head;
    }
    else if (pr == begin())
    {
        iterator temp(s, tail, pr, this);
        pr.cur->prev = temp.cur;
        head.cur = temp.cur;
        return temp;
    }
    else
    {
        iterator pos = pr--;
        iterator temp(s, pr, pos, this);
        pos.cur->prev = pr.cur->next = temp.cur;
        return temp;
    }
}

list::iterator list::erase(iterator pos)
{
    assert(pos.flag && pos.my_object == this && pos != end());
    std::vector<iterator*> vv;
    std::vector<const_iterator*> cc;
    for (auto x = v.begin(); x != v.end(); x++)
    {
        if ((*x)->cur == pos.cur)
        {
            vv.push_back(*x);
        }
    }
    for (auto x = cv.begin(); x != cv.end(); x++)
    {
        if ((*x)->cur == pos.cur)
        {
            cc.push_back(*x);
        }
    }
    iterator x = pos;
    x++;
    assert(!empty());
    if (++begin() == end())
    {
        delete head.cur;
        tail.cur->next = tail.cur->prev = head.cur = tail.cur;
    }
    else
    {
        pos.cur->prev->next = pos.cur->next;
        pos.cur->next->prev = pos.cur->prev;
        if (head == pos)
        {
            head.cur = pos.cur->next;
        }
        delete pos.cur;
    }
    for (auto x : vv) {
        x->flag = false;
    }
    for (auto x : cc) {
        x->flag = false;
    }
//    std::cout << "Here\n";
    return x;
}

void list::push_front(std::string const & s)
{
    insert(head, s);
}

void list::pop_front()
{
    assert(!empty());
    erase(head);
}

void list::push_back(std::string const & s)
{
    insert(tail, s);
}

void list::pop_back()
{
    assert(!empty());
    erase(--end());
}

std::string list::front()
{
    assert(!empty());
    return *begin();
}
std::string const & list::front() const
{
    assert(!empty());
    return *begin();
}

std::string list::back()
{
    assert(!empty());
    return *(--end());
}
std::string const& list::back() const
{
    assert(!empty());
    return *(--end());
}

bool list::empty() const
{
    return (begin() == end());
}

void list::splice(iterator pos, list &other, iterator first, iterator last)
{
    assert(pos.flag && first.flag && last.flag);
    assert(pos.my_object == this);
    assert(first.my_object == &other);
    assert(last.my_object == &other);
    if (first == last)
    {
        return;
    }
    bool order = false;
    for (auto x = other.begin(); x != other.end();)
    {
        auto xx = x++;
        if (xx == first)
        {
            order = true;
        }
        if (xx == last)
        {
            assert(order);
            order = false;
        }
        if (&other == this && order)
        {
            assert(pos != xx);
        }
    }

    for (auto x = first; x != last;)
    {
        auto xx = x++;
        for (auto y = other.v.begin(); y != other.v.end();)
        {
            auto q = y++;
            if ((*q)->cur == xx.cur)
            {
                (*q)->flag = false;
            }
        }
        for (auto y = other.cv.begin(); y != other.cv.end();)
        {
            auto q = y++;
            if ((*q)->cur == xx.cur)
            {
                (*q)->flag = false;
            }
        }
    }
 auto y = last;
    last.cur = last.cur->prev;
    if (first == other.begin() && y == other.end())
    {
        other.head = other.tail;
        other.head.cur->next = other.head.cur->prev = other.head.cur;
    }
    else if (first == other.begin())
    {
        other.head = y;
//        head.flag = true;
    }
    else
    {
        iterator x = first;
        x.flag = true;
        x--;
        x.cur->next = y.cur;
        y.cur->prev = x.cur;
    }
//exit(0);
    first.flag = last.flag = true;
    first.my_object = last.my_object = this;
    if (empty())
    {
        head = first;
        tail.cur->prev = last.cur;
        last.cur->next = tail.cur;
    }
    else if (pos == begin())
    {
        head.cur->prev = last.cur;
        last.cur->next = head.cur;
        head = first;
    }
    else
    {
        auto q = pos--;
        pos.cur->next = first.cur;
        first.cur->prev = pos.cur;
        q.cur->prev = last.cur;
        last.cur->next = q.cur;
    }

//    exit(0);
}

void list::clear()
{
    v.clear();
    cv.clear();
    while (!empty())
    {
        pop_back();
    }
}

int main()
{
{
    list a;
    a.push_back("1");
    a.push_back("2");
    a.push_back("3");
    list b;
    b.splice(b.begin(), a, a.begin(), a.end());
    for (auto x : a)
    {
        std::cout << x << " ";
    }
    std::cout << "\n";
    for (auto x : b)
    {
        std::cout << x << " ";
    }
    std::cout << "\n";
}
return 0;
//{
//    list b;
//
//    b.insert(b.begin(), "1");
//    b.insert(b.begin(), "2");
//    b.insert(b.begin(), "3");
//    b.insert(b.begin(), "4");
//    b.insert(b.begin(), "5");
//    b.insert(b.begin(), "6");
//    list::iterator first = b.begin();
//    for ( int i =0; i < 3; i++) {
//    first++;
//    }
//    for (auto xx : b) {
//        std::cout << xx << " ";
//    }
//    std::cout << "\n";
//
//    b.splice(b.begin(), b, first, b.end());
//    for (auto xx : b)
//    {
//        std::cout << xx << " ";
//    }
//    std::cout << "\n\n\n";
//}
//return 0;
    {
    list a;
    a.push_back("3");
    a.push_front("1");
    a.insert(a.begin()++, "2");
    for ( auto aa :a)
    {
        std::cout << aa << " ";
    }
    std::cout << "\n";
    list b;
    b.splice(b.begin(), a, a.begin(), a.end());
    for (auto aa : a)
    {
        std::cout << aa << " ";
    }
    std::cout << "\n";
    for (auto aa : b)
    {
        std::cout << aa << " ";
    }
    std::cout << "finished\n";
    }

return 0;
    {
//        std::list a;
        list b;
//        a.insert(a.begin(), "1");
//        a.insert(a.begin(), "2");
        *b.end();
    }
    return 0;
    {
        std::list<std::string> a;
        list b;
        for (int i = 0; i < 100; i++)
        {
            std::string d;
            d += i + 48;
            a.insert(a.end(), d);
            b.insert(b.end(), d);
        }
        auto aa = a.begin();
        auto bb = b.begin();
        while (aa != a.end() && bb != b.end())
        {
            assert(*aa == *bb);
            aa++;
            bb++;
        }
        assert(aa == a.end() && bb == b.end());
        a.clear();
        b.clear();
        assert(b.empty());
    }
}


//
//void list::splice(iterator pos, list& other, iterator first, iterator last) {
//    assert(pos.is_valid() && first.is_valid() && last.is_valid());
//    assert(first.owner == last.owner);
//    assert(first.owner == &other);
//    assert(pos.owner == this);
//
//    for (auto i = first; i != last; ) {
//        if (first.owner == pos.owner)
//            assert(i != pos);
//        auto temp = i;
//        ++i;
//        other.iterators.make_invalid(temp.pos);
//    }
//
//    node* f = first.pos;
//    node* l = last.pos;
//    node* real_l = l->prev;
//    if (!f->prev) {
//        other.first = l;
//        other.first->prev = nullptr;
//    } else {
//        f->prev->next = l;
//        l->prev = f->prev;
//    }
//
//    if (!pos.pos->prev) {
//        this->first = f;
//        this->first->prev = nullptr;
//    } else {
//        pos.pos->prev->next = f;
//        f->prev = pos.pos->prev;
//    }
//    pos.pos->prev = real_l;
//    real_l->next = pos.pos;
//}
