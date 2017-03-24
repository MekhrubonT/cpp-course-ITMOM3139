#include "persistent_set.h"
#include <cassert>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>

std::ofstream fout("test.out");

void test_linear_insert()
{
	persistent_set pset;
	for (int i = 0; i < 100; i++) {
//        std::cout << "i=" << i << "\n";
        try
        {
        pset.insert(i);
        } catch(int) {
            throw;
        }
    }
	int i = 0;
	for (persistent_set::iterator it = pset.begin(); it != pset.end(); it++)
	{
		assert(it.el->key == i);
		i++;
	}

	fout << "test_linear_insert == OK" << std::endl;
}

void test_random_insert()
{
	std::srand((unsigned)std::time(0));
	std::vector<int> el;
	persistent_set pset;
	for (int i = 0; i < 100; i++)
	{
		int k = rand() - RAND_MAX / 2;
		el.push_back(k);
		pset.insert(k);
	}
	sort(el.begin(), el.end());
	for (persistent_set::iterator it = pset.end(); it != pset.begin();)
	{
		assert((--it).el->key == el.back());
		el.pop_back();
	}

	fout << "test_random_insert == OK" << std::endl;
}

void test_erase()
{
	std::srand((unsigned)std::time(0));
	std::vector<int> el, el2;
	persistent_set pset;
	for (int i = 0; i < 100; i++)
	{
		int k = rand() - RAND_MAX / 2;
		if (i % 2 == 0)
			el.push_back(k);
		else
			el2.push_back(k);
		pset.insert(k);
	}

	for (int i = 0; i < 50; i++)
		pset.erase(pset.find(el2[i]));

	sort(el.begin(), el.end());
	reverse(el.begin(), el.end());
	for (persistent_set::iterator it = pset.begin(); it != pset.end(); it++)
	{
		assert(it.el->key == el.back());
		el.pop_back();
	}

	fout << "test_erase == OK" << std::endl;
}

void test_copy()
{
	std::srand((unsigned)std::time(0));
	std::vector<int> el;
	persistent_set pset1, pset2;
	for (int i = 0; i < 100; i++)
	{
		int k = rand() - RAND_MAX / 2;
		el.push_back(k);
		pset1.insert(k);
	}
	for (int i = 0; i < 100; i++)
	{
		int k = rand() - RAND_MAX / 2;
		pset2.insert(k);
	}
	pset2 = pset1;

	sort(el.begin(), el.end());
	reverse(el.begin(), el.end());
	for (persistent_set::iterator it = pset2.begin(); it != pset2.end(); it++)
	{
		assert(it.el->key == el.back());
		el.pop_back();
	}

	fout << "test_copy == OK" << std::endl;
}

void test_copy_of_deleted()
{
	std::srand((unsigned)std::time(0));
	std::vector<int> el, el2;
	persistent_set pset1, pset2;
	for (int i = 0; i < 100; i++)
	{
		int k = rand() - RAND_MAX / 2;
		el.push_back(k);
		el2.push_back(k);
		pset1.insert(k);
	}
	for (int i = 0; i < 100; i++)
	{
		int k = rand() - RAND_MAX / 2;
		pset2.insert(k);
	}
	pset2 = pset1;

	sort(el.begin(), el.end());
	reverse(el.begin(), el.end());

	for (int i = 0; i < 100; i++)
		pset1.erase(pset1.find(el[i]));
	//pset1.~persistent_set();

	for (persistent_set::iterator it = pset2.begin(); it != pset2.end(); it++)
	{
		assert(it.el->key == el.back());
		el.pop_back();
	}

	fout << "test_copy_of_deleted == OK" << std::endl;
}

int main()
{
	test_linear_insert();
	test_random_insert();
	test_erase();
	test_copy();
	test_copy_of_deleted();
}
