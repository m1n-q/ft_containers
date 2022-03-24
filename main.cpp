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
	typename Vec<T, std::allocator<T> >::iterator it;
	int arr[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
	Vec<T, std::allocator<T> > myvec(arr, arr + 6);
	Vec<T, std::allocator<T> > myvec1;
	Vec<T, std::allocator<T> > myvec2(myvec.begin(), myvec.end());
	Vec<T, std::allocator<T> > myvec3(myvec2);
	Vec<T, std::allocator<T> > myvec4(4, 42);
	Vec<T, std::allocator<T> > myvec_e;

	print_vector(myvec);
	print_vector(myvec1);
	print_vector(myvec2);
	print_vector(myvec3);
	print_vector(myvec4);

	std::cout << "===========after assign=============" << std::endl;
	myvec = myvec1 = myvec2;
	myvec3 = myvec4;

	print_vector(myvec);
	print_vector(myvec1);
	print_vector(myvec2);
	print_vector(myvec3);
	print_vector(myvec4);
	print_vector(myvec_e);
	std::cout << "===========after assign2=============" << std::endl;
	myvec_e = myvec = myvec1 = myvec2 = myvec3 = myvec4;
	print_vector(myvec);
	print_vector(myvec1);
	print_vector(myvec2);
	print_vector(myvec3);
	print_vector(myvec4);
	print_vector(myvec_e);



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
