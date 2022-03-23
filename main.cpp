#include <__iterator/iterator_traits.h>
#include <ios>
#include <memory>
#include <ostream>
#include <vector>
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

	// * 부모 <- 자식 방향으로만 대입이 가능합니다. 자식은 부모의 정보를 모두 갖고 있지만, 반대는 아니니까.
	// ft::output_iterator_tag o;
	// ft::input_iterator_tag i;
	// ft::forward_iterator_tag f;
	// (void)static_cast<ft::input_iterator_tag>(f);
	// (void)static_cast<ft::forward_iterator_tag>(i);
	std::cout<< std::boolalpha <<
	ft::is_convertible<ft::forward_iterator_tag, ft::input_iterator_tag>::value << std::endl;


}



int main(int argc, char** argv)
{

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
