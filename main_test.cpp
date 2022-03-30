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
	Map<>	m;

	m.insert(Pair<>(1, 'a'));

	std::cout << m.begin()->first << std::endl;
	std::cout << m.begin()->second << std::endl;

}

template<
			typename T,
			template <class U = T, class Alloc = std::allocator<T> > class Vec
		>
void		vector_tester()
{
	Vec<> v;
	v.push_back(42);

	std::cout << v[0] << std::endl;
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
		// map_tester<int, char, std::less, std::pair, std::map >();
	}
	else
	{
		print_header(input);
		// vector_tester<int, ft::vector>();
		// map_tester<int, char, std::less, ft::pair, ft::map >();
	}
	system("leaks a.out");

}
