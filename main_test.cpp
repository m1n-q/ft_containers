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
	typedef typename Map<>::iterator				Iter;
	typedef typename Map<>::const_iterator			CIter;
	// typedef typename Map<>::reverse_iterator		RIter;
	typedef typename Map<>::const_reverse_iterator	CRIter;

	Pair<>		arr[] = { Pair<>(100, 'a'), Pair<>(42, 'b'), Pair<>(777, 'c') };
	Map<>		m1;
	Map<>		m2(arr, arr + 3);
	const Map<>	cm(m2);

	PRINT(CYAN("m1") " ~ default constructed")
	print_map(m1);
	PRINT(YELLOW("m2") " ~ range constructed")
	print_map(m2);
	PRINT(GREEN("cm") " ~ copy constructed from " YELLOW("m2"))
	print_map(cm);


	PRINT(CYAN("m1") " is empty?")	std::cout << m1.empty() << std::endl;
	PRINT(GREEN("cm") " is empty?") std::cout << cm.empty() << std::endl;

	PRINT(CYAN("m1") ": INSERT")
	m1.insert( Pair<>(666, 'X') );
	print_map(m1);
	PRINT(CYAN("m1") " is empty?")	std::cout << m1.empty() <<std::endl;

	PRINT(YELLOW("m2") " = "  CYAN("m1") " (assign)")
	m2 = m1;

	PRINT(CYAN("m1"))
	print_map(m1);
	PRINT(YELLOW("m2"))
	print_map(m2);
	PRINT(GREEN("cm"))
	print_map(cm);

	Pair<Iter, bool>	result;

	for (int i = 0; i < 5; i++)
	{
		result = m1.insert(Pair<>(rand() % 1024, 'z'));
		if (result.second == true)
			std::cout << result.first->first << BLUE(" inserted!") << std::endl;
		else
			std::cout << result.first->first << RED(" already exists!") << std::endl;
	}
	print_map(m1);
	result = m1.insert(Pair<>(666, 'T'));
	if (result.second == true)
		std::cout << result.first->first << BLUE(" is inserted") << std::endl;
	else
		std::cout << result.first->first << RED(" already exists") << std::endl;

	PRINT("insert 667 to " CYAN("m1") ", near 666 ");
	m1.insert(m1.find(666), Pair<>(667, 'N'));
	print_map(m1);

	PRINT(GREEN("cm"))
	print_map(cm);

	PRINT("insert " RED("[ ") GREEN("cm") ".begin(), " GREEN("cm") ".end()" RED(" )") " to " CYAN("m1: ") )
	m1.insert(cm.begin(), cm.end());
	print_map(m1);

	PRINT("erase 666 (iter) from " CYAN("m1"))
	m1.erase(m1.find(666));
	print_map(m1);

	// PRINT("erase 666 (iter) from " CYAN("m1"))
	// m1.erase(m1.find(666));	//! segfault
	// print_map(m1);

	typedef typename Map<>::size_type	Size;
	Size s;

	PRINT("erase 666 (key) from " CYAN("m1"))
	s = m1.erase(666);
	std::cout << PURPLE("total erased: ") << s << std::endl;


	PRINT("erase 667 (key) from " CYAN("m1"))
	s = m1.erase(667);
	std::cout << PURPLE("total erased: ") << s << std::endl;
	print_map(m1);


	PRINT("erase " RED("[ ") "2nd, 6th " RED (") ") "of " CYAN( "v1 "))
	Iter it = m1.begin(), ite = m1.begin();
	it++;
	ite++;
	ite++;
	ite++;
	ite++;
	ite++;
    m1.erase(it, ite);
	print_map(m1);

	PRINT(PURPLE("before ") "swap " "(" CYAN("m1") ", " YELLOW("m2") ")")
	PRINT(CYAN("m1"))
	print_map(m1);
	PRINT(YELLOW("m2"))
	print_map(m2);

	m1.swap(m2);

	PRINT(PURPLE("after ") "swap "  "(" CYAN("m1") ", " YELLOW("m2") ")")
	PRINT(CYAN("m1"))
	print_map(m1);
	PRINT(YELLOW("m2"))
	print_map(m2);


	PRINT(PURPLE("before clear, ") CYAN("m1") " is empty?")	std::cout << m1.empty() << std::endl;
	m1.clear();
	PRINT(PURPLE("after clear, ") CYAN("m1") " is empty?")	std::cout << m1.empty() << std::endl;


	std::cout << cm.key_comp()(1, 2) << std::endl;								//@ C
	std::cout << cm.value_comp()( Pair<>(1,'z'), Pair<>(2,'a') ) << std::endl;	//@ C


	PRINT(GREEN("cm"))
	print_map(cm);
	CIter r = cm.find(42);
	if (r != cm.end())
		std::cout << BLUE("Found ") << r->first << std::endl;
	else
		std::cout << RED("Cannot found") << std::endl;

	r = cm.find(43);
	if (r != cm.end())
		std::cout << BLUE("Found ") << r->first << std::endl;
	else
		std::cout << RED("Cannot found") << std::endl;

	std::cout << PURPLE("Count 42: ")  << cm.count(42) << std::endl;
	std::cout << PURPLE("Count 43: ")  << cm.count(43) << std::endl;


	std::cout << cm.lower_bound(100)->first << std::endl;	//@ C
	std::cout << cm.upper_bound(100)->first << std::endl;	//@ C
	Pair<CIter, CIter> range = cm.equal_range(100);


	for (CIter f = range.first; f != range.second; f++)
		std::cout << f->first << " ";
	std::cout << std::endl;

	Map<> m3;
	PRINT(PURPLE("Insert" ) " to " BLUE("m3")  " by operator" PURPLE("[]"))

	m3[0] = 'A';
	m3[10] = 'B';
	m3[100] = 'C';
	m3[-1] = 'X';

	print_map(m3);

	PRINT(PURPLE("Modify" ) " mapped values of " BLUE("m3")  " by operator" PURPLE("[]"))

	m3[0] = 'x';
	m3[10] = 'y';
	m3[100] = 'z';
	m3[-1] = 'a';

	print_map(m3);

	for (CRIter f = m3.rbegin(); f != m3.rend(); f++)
		std::cout << f->first << " ";
	std::cout << std::endl;

	for (CRIter f = cm.rbegin(); f != cm.rend(); f++)
		std::cout << f->first << " ";
	std::cout << std::endl;

	// max_size	//@ C
	// get_allocator //@ C
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
		// vector_tester<int, std::vector>();
		map_tester<int, char, std::less, std::pair, std::map >();
	}
	else
	{
		print_header(input);
		// vector_tester<int, ft::vector>();
		map_tester<int, char, std::less, ft::pair, ft::map >();
	}
	system("leaks a.out");

}
