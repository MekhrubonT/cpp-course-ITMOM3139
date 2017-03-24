#ifndef PERSISTENT_SET_H
#define PERSISTENT_SET_H

#include<iostream>
#include <vector>
#include <memory>

struct persistent_set
{

	// �� ������ ���������� ���� ������� �� ������ ����������.
	typedef int value_type;

	// Bidirectional iterator.
//private:
	struct node : std::enable_shared_from_this<node>
	{
		value_type key;
        std::shared_ptr<node> left, right;

		node(value_type key);//done

        ~node();

		node(std::shared_ptr<node> const &other);

		node& operator=(const node& other);

        std::shared_ptr<node> insert(value_type);//done

        std::shared_ptr<node> find(value_type);//done

        void erase(std::shared_ptr<node>, std::shared_ptr<node>);//done

        std::shared_ptr<node> next(std::shared_ptr<node> x);

        std::shared_ptr<node> prev(std::shared_ptr<node> x);

        std::shared_ptr<node> begin() const;//done

        std::shared_ptr<node> end() const;//done

	};
public:
    struct iterator
    {
        friend persistent_set;
        iterator() = delete;
        iterator(std::shared_ptr<node>, std::shared_ptr<node>);//done
        iterator(iterator const&);
        ~iterator();
        iterator& operator=(iterator const& rhs);//done

        value_type const& operator*() const;//done

        iterator& operator++();//done
        iterator operator++(int);//done

        iterator& operator--();//done
        iterator operator--(int);//done

        friend bool operator==(iterator, iterator);
        friend bool operator!=(iterator, iterator);


//    private:
        std::shared_ptr<node> el, root;
    };

	persistent_set();//done

	persistent_set(persistent_set const&);//done

	persistent_set& operator=(persistent_set const& rhs);//done

	~persistent_set();//done

    iterator find(value_type);//done

	std::pair<iterator, bool> insert(value_type);//done

	void erase(iterator);//done

	iterator begin() const;//done
	iterator end() const;//done



//private:
	std::shared_ptr<node> root;
};

bool operator==(persistent_set::iterator, persistent_set::iterator);//done
bool operator!=(persistent_set::iterator, persistent_set::iterator);//done


#endif //PERSISTENT_SET_H
