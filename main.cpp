#include <__iterator/iterator_traits.h>
#include <__tree>
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
#include "vector.hpp"

#include <chrono>
# define START	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
# define END	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();std::cout<< "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;


#include <map>
#include "map.hpp"


class P {};
class D : public P {};

struct FI {
	typedef ptrdiff_t					difference_type;
    typedef int							value_type;
    typedef int*						pointer;
    typedef int&						reference;
    typedef ft::output_iterator_tag	iterator_category;
};




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

	typedef typename MAP::iterator			ITER;
	typedef typename MAP::const_iterator	CITER;

	MAP		m;
	ITER	tmp1;
	CITER	tmp2;

	(void)tmp1; (void)tmp2;

	m.insert(PAIR('a', 42));
	m.insert(PAIR('b', 42));
	m.insert(PAIR('c', 42));
	ITER	it(m.begin());
	CITER	cit(it);
	// ITER	it2(cit);

	std::cout << (*it++).first << std::endl;
	std::cout << (*it).first << std::endl;
	std::cout << (*--it).first << std::endl;



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
		test_func<char, int, std::pair, std::map>();

	}
	else
	{
		print_header(input);
		test_func<char, int, ft::pair, ft::map>();
	}
	system("leaks a.out");

}
