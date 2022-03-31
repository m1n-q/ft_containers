#include "printer.hpp"

#include <vector>
#include "vector.hpp"

#include <map>
#include "map.hpp"

template<
			class K,
			class V,
			template <class Key = K>						class C,
			template <class Fir = const K, class Sec = V>	class Pair,
			template <
						class Key = K,
						class Mapped = V,
						class Comp = C<>,
						class Alloc = std::allocator<Pair<> >
					> 										class Map
		>
void		map_tester()
{
	// Map<>	m;

	// m.insert(Pair<>(1, 'a'));
	// m.insert(Pair<>(2, 'a'));
	// m.insert(Pair<>(3, 'a'));
	// m.insert(Pair<>(4, 'a'));
	// m.insert(Pair<>(4, 'a'));
	// m.insert(Pair<>(6, 'a'));
	// m.insert(Pair<>(7, 'a'));
	// m.insert(Pair<>(8, 'a'));

	// std::cout << m.begin()->first << std::endl;
	// std::cout << m.begin()->second << std::endl;

}

template<
			typename T,
			template <class U = T, class Alloc = std::allocator<T> > class Vec
		>
void		vector_tester()
{

	T		arr[4] = {11, 22, 33, 44};

	Vec<>	v1;
	Vec<>	v2(3, 42);
	Vec<>	v3(arr, arr + 4);

	PRINT(CYAN("v1 ( default constructed ) =>"))
	print_vector(v1);
	PRINT(YELLOW("v2 ( fill constructed ) =>"))
	print_vector(v2);
	PRINT(BLUE("v3 ( range constructed ) =>"))
	print_vector(v3);



	const Vec<> cv(v3);

	v3[0] = 1111;

	PRINT(GREEN("const cv ( copy constructed, from v3 ) "))
	print_vector(cv);
	PRINT(YELLOW("v3[0]")" changed")
	print_vector(v3);


	// begin()			// @ C
	// end()			// @ C
	// rbegin()			// @ C
	// rend()			// @ C

//' capacity
	PRINT("max size of vector =>" )
	std::cout << v1.max_size() << std::endl;
	PRINT("max size of const vector =>" )
	std::cout << cv.max_size() << std::endl;	// @ C

	std::cout << CYAN("v1") " is Empty?\t" << v1.empty() << std::endl;
	std::cout << GREEN("cv") " is Empty?\t" << cv.empty() << std::endl;	// @ C

	// size()		// @ C
	// capacity()	// @ C

	PRINT("current state of" YELLOW("v2"))
	print_vector(v2);

	PRINT("after "YELLOW("v2") ".reserve(1)")
	v2.reserve(1);
	print_vector(v2);

	PRINT("after "YELLOW("v2") ".reserve(10)")
	v2.reserve(10);
	print_vector(v2);


	//TODO:resize()

//' element

	PRINT(YELLOW("v2[0]") " => ")
	std::cout << v2[0] << std::endl;
	v2[0] = 424242;

	PRINT(YELLOW("v2[0]") " changed => ")
	print_vector(v2);

	PRINT(GREEN("const cv[0]") " => ")
	std::cout << cv[0] << std::endl;		// @ C

// {	cv[0] = 1;	// cannot assign to const iter


	PRINT("const cv.at(10) => ")
	try							{ std::cout<< cv.at(10) << std::endl; } 	// @ C
	catch (std::exception& e)	{ std::cerr << e.what() << std::endl; }


	PRINT("front() && back() of const cv")
	std::cout << cv.front() << std::endl;	// @ C
	std::cout << cv.back() << std::endl;	// @ C


	PRINT("current state of v1")
	print_vector(v1);
	for (int i = 0; i < 42; i++)
		v1.push_back(i);
	PRINT("after push_back " RED("[") "0, 42 " RED(")"))
	print_vector(v1);


	PRINT(CYAN("v1: ") "assign (fill n)")
	v1.assign(3, 99);
	print_vector(v1);

	PRINT(CYAN("v1.pop_back()"))
	v1.pop_back();	// try at empty vector
	print_vector(v1);


	PRINT(CYAN("v1: ") "assign " RED("[ ") GREEN("cv") ".begin()," GREEN("cv") ".end()" RED(" )"))
	v1.assign(cv.begin(), cv.end());
	print_vector(v1);


	PRINT("insert " PURPLE ("123456 ") "at " CYAN("v1.begin"))
	v1.insert(v1.begin(), 123456);
	print_vector(v1);


	PRINT("insert " PURPLE ("[777] * 3 ")  "at " CYAN("v1.end"))
	v1.insert(v1.end(), 3, 777);
	print_vector(v1);


	PRINT("insert " YELLOW("v2 ") "at " CYAN("v1[3]"))
	v1.insert(v1.begin() + 3, v2.begin(), v2.end());
	print_vector(v1);


	PRINT("erase " PURPLE("4th elem ")  "of " CYAN("v1"))
	v1.erase(v1.begin() + 3);
	print_vector(v1);

	PRINT("erase " RED("[ ") "2nd, 6th " RED (") ") "of " CYAN( "v1 "))
	v1.erase(v1.begin() + 1, v1.begin() + 5);
	print_vector(v1);

	PRINT(PURPLE("before ") "swap " "(" YELLOW ("v2") ", " BLUE ("v3") ")")
	PRINT("v2 =>")
	print_vector(v2);
	PRINT("v3 =>")
	print_vector(v3);

	swap(v2, v3);
	PRINT(PURPLE("after ") "swap "  "(" YELLOW ("v2") ", " BLUE ("v3") ")")

	PRINT(YELLOW("v2 =>"))
	print_vector(v2);
	PRINT(BLUE("v3 =>"))
	print_vector(v3);
	// clear()
	// get_allocator()	// @ C

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
		vector_tester<int, std::vector>();
		// map_tester<int, char, std::less, std::pair, std::map >();
	}
	else
	{
		print_header(input);
		vector_tester<int, ft::vector>();
		// map_tester<int, char, std::less, ft::pair, ft::map >();
	}
	system("leaks a.out");

}
