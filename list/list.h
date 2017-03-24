#ifndef LIST_H
#define LIST_H
#include <vector>
#include <string>


struct list
{
struct iterator;
struct const_iterator;
    struct it_list
    {
    private:
        struct it_node
        {
            it_node (iterator* key);
            it_node (iterator* key, it_node const &other);
            it_node (iterator* key, it_node *prev, it_node *next);
        //    it_node (const iterator* &key, it_node const *prev, it_node const *next);
            it_node (const it_node& other);
            ~it_node();

            bool operator==(const it_node& b);
            iterator* key;
            it_node *prev, *next;
        };



    public:
        struct it_iterator
        {
            friend struct list;
            it_iterator (iterator* key);
            it_iterator (it_node& other);
            it_iterator (iterator* key, const it_iterator &other);
            it_iterator (iterator* key, const it_iterator &prev, const it_iterator &next);
            it_iterator (const it_iterator& other);
            ~it_iterator ();
            it_iterator operator=(it_iterator other);

            iterator* operator*();
            it_iterator& operator++();
            it_iterator operator++(int);
            it_iterator& operator--();
            it_iterator operator--(int);


            void swap(it_iterator &b);

            bool operator==(const it_iterator &b);
            bool operator!=(const it_iterator &b);
            friend void swap(it_iterator &a, it_iterator &b);
        private:
            it_node *cur;
        };

        struct const_it_iterator
        {
            const_it_iterator (iterator* key);
            const_it_iterator (it_node& other);
            const_it_iterator (iterator* key, const const_it_iterator &other);
            const_it_iterator (iterator* key, const const_it_iterator &prev, const const_it_iterator &next);
            const_it_iterator (const const_it_iterator& other);
            ~const_it_iterator ();
            const_it_iterator operator=(const_it_iterator other);

            iterator* operator*();
            const_it_iterator& operator++();
            const_it_iterator operator++(int);
            const_it_iterator& operator--();
            const_it_iterator operator--(int);


            bool operator==(const const_it_iterator &b);
            bool operator!=(const const_it_iterator &b);

            void swap(const_it_iterator &b);


            friend bool operator==(const it_iterator &a, const it_iterator &b);
            friend bool operator!=(const it_iterator &a, const it_iterator &b);
            friend void swap(const_it_iterator &a, const_it_iterator &b);

        private:
            it_node *cur;
        };
        it_list();

        it_list(const it_list &my_it_list);

        ~it_list();

        it_list & operator = (const it_list & s);

        it_iterator begin();

        it_iterator end();

        const_it_iterator begin() const;

        const_it_iterator end() const;

        it_iterator erase (it_iterator pos);

        it_iterator insert(it_iterator pos, iterator* s);

        void push_front(iterator* s);

        void pop_front();

        void push_back(iterator* s);

        void pop_back();

        bool empty() const;

        void swap(it_list &b);

        void clear();

    private:
        it_iterator head, tail;
    };

    struct constit_list
    {
    private:
        struct constit_node
        {
            constit_node (const_iterator* key);
            constit_node (const_iterator* key, constit_node const &other);
            constit_node (const_iterator* key, constit_node *prev, constit_node *next);
        //    constit_node (const const_iterator* &key, constit_node const *prev, constit_node const *next);
            constit_node (const constit_node& other);
            ~constit_node();

            bool operator==(const constit_node& b);
            const_iterator* key;
            constit_node *prev, *next;
        };



    public:
        struct constit_iterator
        {
            friend struct list;
            constit_iterator (constit_list* obj, const_iterator* key);
            constit_iterator (constit_node& other, constit_list* obj);
            constit_iterator (const_iterator* key, const constit_iterator &other);
            constit_iterator (const_iterator* key, const constit_iterator &prev, const constit_iterator &next, constit_list* obj);
            constit_iterator (const constit_iterator& other);
            ~constit_iterator ();
            constit_iterator operator=(constit_iterator other);

            const_iterator* operator*();
            constit_iterator& operator++();
            constit_iterator operator++(int);
            constit_iterator& operator--();
            constit_iterator operator--(int);


            void swap(constit_iterator &b);

            bool operator==(const constit_iterator &b);
            bool operator!=(const constit_iterator &b);
            friend void swap(constit_iterator &a, constit_iterator &b);
        private:
            constit_node *cur;
            constit_list *my_object;
            bool flag;
        };

        struct const_it_iterator
        {
            const_it_iterator (const constit_list* obj, const_iterator* key);
            const_it_iterator (constit_node& other, const constit_list* obj);
            const_it_iterator (const_iterator* key, const const_it_iterator &other);
            const_it_iterator (const_iterator* key, const const_it_iterator &prev, const const_it_iterator &next, const constit_list* obj);
            const_it_iterator (const const_it_iterator& other);
            ~const_it_iterator ();
            const_it_iterator operator=(const_it_iterator other);

            const_iterator* operator*();
            const_it_iterator& operator++();
            const_it_iterator operator++(int);
            const_it_iterator& operator--();
            const_it_iterator operator--(int);


            bool operator==(const const_it_iterator &b);
            bool operator!=(const const_it_iterator &b);

            void swap(const_it_iterator &b);


            friend bool operator==(const constit_iterator &a, const constit_iterator &b);
            friend bool operator!=(const constit_iterator &a, const constit_iterator &b);
            friend void swap(const_it_iterator &a, const_it_iterator &b);

        private:
            constit_node *cur;
            const constit_list* my_object;
            bool flag;
        };
        constit_list();

        constit_list(const constit_list &my_it_list);

        ~constit_list();

        constit_list & operator = (const constit_list & s);

        constit_iterator begin();

        constit_iterator end();

        const_it_iterator begin() const;

        const_it_iterator end() const;

        constit_iterator erase (constit_iterator pos);

        constit_iterator insert(constit_iterator pos, const_iterator* s);

        void push_front(const_iterator* s);

        void pop_front();

        void push_back(const_iterator* s);

        void pop_back();


        bool empty() const;

        void swap(constit_list &b);

        void clear();

    private:
        constit_iterator head, tail;
    };


private:
    struct node
    {
        node (const std::string &key);
        node (const std::string &key, node const &other);
        node (const std::string &key, node *prev, node *next);
    //    node (const std::string &key, node const *prev, node const *next);
        node (const node& other);
        ~node();

        bool operator==(const node& b);
        std::string key;
        node *prev, *next;
    };



public:
    struct iterator
    {
        friend struct list;
        iterator (list* obj, const std::string &key);
        iterator (node& other, list* obj);
        iterator (const std::string &key, const iterator &other);
        iterator (const std::string &key, const iterator &prev, const iterator &next, list* obj);
        iterator (const iterator& other);
        ~iterator ();
        iterator operator=(iterator other);

        std::string& operator*();
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);


        void swap(iterator &b);

        bool operator==(const iterator &b);
        bool operator!=(const iterator &b);
        friend void swap(iterator &a, iterator &b);
//    private:
        node *cur;
        list* my_object;
        bool flag;
    };

    struct const_iterator
    {
        friend struct list;
        const_iterator (const list* obj, const std::string &key);
        const_iterator (node& other, const list* obj);
        const_iterator (const std::string &key, const const_iterator &other);
        const_iterator (const std::string &key, const const_iterator &prev, const const_iterator &next, const list* obj);
        const_iterator (const const_iterator& other);
        ~const_iterator ();
        const_iterator operator=(const_iterator other);

        const std::string& operator*();
        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);


        bool operator==(const const_iterator &b);
        bool operator!=(const const_iterator &b);

        void swap(const_iterator &b);


        friend bool operator==(const iterator &a, const iterator &b);
        friend bool operator!=(const iterator &a, const iterator &b);
        friend void swap(const_iterator &a, const_iterator &b);

    private:
        node *cur;
        list const * my_object;
        bool flag;
    };
    list();

    list(const list &my_list);

    ~list();

    list & operator = (const list & s);

    iterator begin();

    iterator end();

    const_iterator begin() const;

    const_iterator end() const;

    iterator erase (iterator pos);

    iterator insert(iterator pos, std::string const & s);

    void push_front(std::string const & s);

    void pop_front();

    std::string const& front() const;

    std::string front();

    void push_back(std::string const & s);

    void pop_back();

    std::string const& back() const;

    std::string back();

    bool empty() const;

    void splice(iterator pos, list & other, iterator first, iterator last);

    void swap(list &b);

    void clear();

private:

    mutable it_list v;
    mutable constit_list cv;
    iterator head, tail;
};




#endif // LIST_H

