#include <__iterator/iterator_traits.h>
#include <ios>
#include <memory>
#include <ostream>
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
class P {};
class D : public P {};

struct FI {
	typedef ptrdiff_t					difference_type;
    typedef int							value_type;
    typedef int*						pointer;
    typedef int&						reference;
    typedef ft::output_iterator_tag	iterator_category;
};




template<typename T,  template<typename, typename> class Vec>
void	test_func()
{
	std::cout << std::boolalpha;
	typedef	Vec<T, std::allocator<T> >							vector;
	typedef	typename Vec<T, std::allocator<T> >::iterator		iterator;
	// typedef	typename Vec<T, std::allocator<T> >::const_iterator	const_iterator;

	std::cout << typeid(vector).name() << std::endl << std::endl;

	iterator it;
	vector	myvec;
	const vector empty;



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
		test_func<int, std::vector>();

	}
	else
	{
		print_header(input);
		test_func<int, ft::vector>();
	}

	system("leaks a.out");

}
