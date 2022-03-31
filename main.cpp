#include <__iterator/iterator_traits.h>
#include <__tree>
#include <algorithm>
#include <cstddef>
#include <exception>
#include <functional>
#include <ios>
#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include <forward_list>
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "iterator.hpp"
#include "printer.hpp"
#include "tree_iter.hpp"
#include "vector.hpp"

#include <chrono>
# define START	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
# define END	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();std::cout<< "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;


#include <map>
#include "map.hpp"


template <class ForwardIterator>
bool sorted(ForwardIterator first, ForwardIterator last)
{
	ForwardIterator l = last;
	if (first != last)
	{
		ForwardIterator i = first;
		while (++i != last)
		{
			if (i->first < first->first)
				return false;
			first = i;
		}
	}
	return last == l;
}

template<typename K,
		 typename V,
		 template <typename, typename> class P,
		 template<typename, typename, typename, typename> class Map>
void	test_func()
{
	typedef P<const K, V>					PAIR;
	typedef Map<
					K,
					V,
					std::less<K>,
					std::allocator<PAIR>
				>							MAP;

	// typedef typename MAP::iterator			ITER;
	// typedef typename MAP::const_iterator	CITER;

	MAP		m;
	int	size = 20;
	std::vector<K> keys;

	START
	for (int i = 0; i < size; i++)
	{
		int key = rand();
		keys.push_back(key);
		m.insert(PAIR(key, 'a'));
	}

	// for (ITER f = m.begin(); f != m.end(); f++)
	// 	std::cout<<  f->first << std::endl;

	m.d();


	for (int i = 0; i < 5; i++)
	{
		int randidx = rand() % size;
		try
		{
			keys.at(randidx);
			std::cout << "REMOVE " << keys[randidx] << std::endl;
			m.erase(keys[randidx]);
			keys.erase(keys.begin() + randidx);
			// m.d();
		}
		catch (std::exception& e)
		{
			;
		}
	}

	// printf("\n");

	m.d();
	std::cout << std::boolalpha;
	std::cout << (
					sorted(m.begin(), m.end()) ?
					"\033[32mSORTED!" :
					"\033[30mNOT SORTED!"
				)
	<< "\033[0m" << std::endl;

	END
}



int main(int argc, char** argv)
{

	std::cout<< std::boolalpha;
	if (argc != 2)
		return -1;

	int input = atoi((argv[1]));
	if (!input)
	{
		print_header(input);
		// test_func<int, char, std::pair, std::map>();

	}
	else
	{
		print_header(input);
		test_func<int, char, ft::pair, ft::map>();
	}
	// system("leaks a.out");

}
