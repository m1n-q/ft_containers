#include "map.hpp"
#include <cstdlib>
#include <ios>
#include <iostream>
#include <vector>
#include <map>

template <class T1, class T2>
void	print_map(const ft::map<T1, T2>& mymap )
{
	typename ft::map<T1, T2>::const_iterator	it;
	for (it = mymap.begin(); it != mymap.end(); it++)
		std::cout << "(" << it->first << ", " << it->second << ")";
	std::cout << std::endl;

}

void	test_func()
{
	std::vector<ft::pair<int, int> > myvector;

	myvector.push_back(ft::make_pair(-1,-1));
	myvector.push_back(ft::make_pair(-3,-1));
	myvector.push_back(ft::make_pair(-2,-1));

	ft::map<int, int>* mymap = new ft::map<int, int>;
	ft::map<int, int>::iterator it;

	mymap->insert(ft::make_pair(1, 0));
	mymap->insert(ft::make_pair(1, 0));
	mymap->insert(ft::make_pair(4, 0));
	mymap->insert(ft::make_pair(3, 0));
	mymap->insert(ft::make_pair(1, 0));
	mymap->insert(ft::make_pair(1, 1));
	mymap->insert(ft::make_pair(1, 2));
	mymap->insert(ft::make_pair(1, 3));

	ft::pair<ft::map<int, int>::iterator,bool> pp =
				mymap->insert(ft::make_pair(1, 99));
	ft::map<int, int>::iterator hint = pp.first;
	std::cout << "HINT => (" << hint->first << ", " << hint->second << ")" << std::endl;

	print_map(*mymap);

	mymap->insert(myvector.begin(), myvector.end());
	print_map(*mymap);

	mymap->insert(hint, ft::make_pair(2, 99));
	print_map(*mymap);

	mymap->erase(hint);
	print_map(*mymap);

	mymap->erase(-2);
	print_map(*mymap);

	mymap->insert(ft::make_pair(-2, 99));
	print_map(*mymap);

	std::cout << "UPPER BOUND => (" << mymap->upper_bound(3)->first << ", " << mymap->upper_bound(3)->second << ")" << std::endl;

	mymap->erase(mymap->lower_bound(-1), mymap->upper_bound(3));
	print_map(*mymap);

	mymap->clear();
	print_map(*mymap);		//EMPTY LINE

	mymap->insert(myvector.begin(), myvector.end());
	print_map(*mymap);

	std::cout << std::boolalpha;
	std::cout << mymap->value_comp()(mymap->begin().operator*(), mymap->end().operator*()) << std::endl;
	std::cout << mymap->key_comp()(mymap->begin().operator*().first, mymap->end().operator*().first) << std::endl;


	std::cout << mymap->count(0) << std::endl;
	std::cout << mymap->count(-1) << std::endl;
	std::cout << mymap->find(-1).operator*().first << std::endl;
	std::cout << (mymap->find(41) == NULL) << std::endl;

	ft::map<int, int> cpymap(*mymap);

	delete mymap;

	std::cout << "COPIED MAP AFTER DELETE MYMAP:" << std::endl;
	print_map(cpymap);

	mymap = new ft::map<int, int>;

	*mymap = cpymap;

	std::cout << "NEW MY MAP, ASSIGNED FROM CPYMAP" << std::endl;
	print_map(*mymap);

	mymap->insert(ft::make_pair(100, 0));
	mymap->insert(ft::make_pair(200, 0));

	cpymap[-1] = 99999;
	cpymap[-2] = 8888;
	cpymap[-3] = 777;
	std::cout << "NEW MYMAP AFTER INSERT: " << std::endl;
	print_map(*mymap);
	std::cout << "CPYMAP: " << std::endl;
	print_map(cpymap);

	delete mymap;

}

int main()
{

	test_func();

	system("leaks a.out");
}
