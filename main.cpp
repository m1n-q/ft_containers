#include <ios>
#include <memory>
#include <vector>
#include "printer.hpp"
#include "vector.hpp"


template<typename T,  template<typename, typename> class Vec>
void	test_func()
{
	Vec<T, std::allocator<T> > myvec;
	typename Vec<T, std::allocator<T> >::iterator it;
	// myvec.push_back(1);
	// myvec.push_back(2);
	// myvec.push_back(3);
	// myvec.push_back(4);

	// myvec.push_back(4);
	// myvec.push_back(4);
	// myvec.push_back(4);
	// myvec.pop_back();
	// myvec.pop_back();
	// myvec.pop_back();

	print_vector(myvec);

	// myvec.pop_back();
	// myvec.pop_back();
	// print_vector(myvec);

	//' where to insert
	it = myvec.end();

	// std::cout << std::boolalpha << (it + 4 == myvec.end()) << std::endl;
	// '1 (val)
		//@ OK
	// typename Vec<T, std::allocator<T> >::iterator nit;
	// nit = myvec.insert(it  , 42);
	// print_vector(myvec);
	// std::cout << "moved		? " << std::boolalpha << !(it == myvec.begin()) << std::endl;
	// std::cout << "inserted	= " << *nit << std::endl;
	// std::cout << "next		= " << *(nit+1) << std::endl << std::endl;

	// '2 (nval)
		//@ OK
	// myvec.insert(it , 3, 99);
	// print_vector(myvec);

	// '3 (range)
		//@ OK
	Vec<T, std::allocator<T> > toInsert;
	toInsert.push_back(7);
	toInsert.push_back(77);
	toInsert.push_back(777);
	toInsert.push_back(7777);
	toInsert.push_back(77777);

	myvec.insert(it, toInsert.begin(), toInsert.end());
	print_vector(myvec);
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
