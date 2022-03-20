
#include <cstdlib>
#include <ios>
#include <iostream>
#include <vector>
#include "vector.hpp"


template <class Container>
void	print_vector(const Container& myvector )
{
	typename Container::const_iterator	it;
	for (it = myvector.begin(); it != myvector.end(); it++)
		std::cout << "(" << *it << ")";
	std::cout << std::endl;

}

void	test_func()
{
	ft::vector<int> myvec;
	ft::vector<int>::iterator it;

	myvec.push_back(1);
	myvec.push_back(2);
	myvec.push_back(3);
	myvec.push_back(2);
	myvec.push_back(1);

	print_vector(myvec);

	myvec.pop_back();
	print_vector(myvec);

	it = myvec.begin();		// where to insert

	myvec.insert(it, 3, 99);		//BUG: when it == begin()
	print_vector(myvec);


	ft::vector<int> toInsert(3);	//BUG: when it == begin()

	it = myvec.begin();		// where to insert
	myvec.insert(it, toInsert.begin(), toInsert.end());
	print_vector(myvec);
}

void	test_func2()
{
	ft::vector<int> myvec;
	ft::vector<int>::iterator it;
	ft::vector<int>::iterator ite;



	myvec.push_back(1);
	myvec.push_back(2);
	myvec.push_back(3);
	myvec.push_back(4);
	myvec.push_back(5);
	myvec.push_back(6);
	myvec.push_back(7);
	std::cout << "size:	" << myvec.size() << std::endl;
	std::cout << "cap:	" << myvec.capacity() << std::endl;
	myvec.pop_back();
	myvec.pop_back();
	myvec.pop_back();
	myvec.pop_back();
	myvec.pop_back();
	std::cout << "size:	" << myvec.size() << std::endl;
	std::cout << "cap:	" << myvec.capacity() << std::endl;
	myvec.assign(3,1);
	myvec.assign(7,1);
	myvec.assign(9,1);
	myvec.assign(2,1);

	myvec.pop_back();
	myvec.pop_back();
	myvec.pop_back();
	myvec.pop_back();

	std::cout << std::boolalpha << myvec.empty() << std::endl;
	std::cout << "size:	" << myvec.size() << std::endl;
	std::cout << "cap:	" << myvec.capacity() << std::endl;
	std::cout << (myvec.begin() == myvec.end()) << std::endl;
	std::cout << myvec.front() << std::endl;
	std::cout << myvec.back() << std::endl;

	// print_vector(myvec);
	// size:   18446744073709551615
}

int main()
{

	test_func2();

	system("leaks a.out");
}
