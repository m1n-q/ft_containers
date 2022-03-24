#include <__iterator/iterator_traits.h>
#include <ios>
#include <memory>
#include <ostream>
#include <vector>
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "iterator.hpp"
#include "printer.hpp"
#include "vector.hpp"

class P {};
class D : public P {};



template<typename T,  template<typename, typename> class Vec>
void	test_func()
{
	int arr[3] = { 1, 2, 3};
	Vec<T, std::allocator<T> > myvec(arr, arr+3);
	typename Vec<T, std::allocator<T> >::iterator it;

	print_vector(myvec);



	// std:: cout << ft::has_iterator_typedefs<ft::iterator_traits<int> >::value << std::endl;



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
