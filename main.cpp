#include <cstddef>
#include <cstdio>
#include <exception>
#include <ios>
#include <iterator>
#include <limits>
#include <type_traits>
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <forward_list>
#include <filesystem>

#include "is_integral.hpp"
#include "vector.hpp"
#include "pair.hpp"
#include "algorithm.hpp"


/* !
 # iterators_traits					//NOTE: void_t, = NULL// TODO: wrapper for other tags, check arithmetics
 ! reverse_iterator
 @ enable_if
 @ is_integral
 @ equal/lexicographical compare	//TODO: test
 @ std::pair
 @ std::make_pair

 ' must be reimplemented.

 ! check operators for wrap_iter, reverse_iterator, vector, pair
 */

using namespace std;
class A
{
public:
	int n;
	A()					: n(42)		{ cout << "<A> default ctor\n"; }
	A( const A& src )	: n(src.n)	{ cout << "<A> copy constructor, " << n << "  " << this << "(from " << &src << ")" << endl; }
	A( int _n )			: n(_n) 	{ cout << "<A> num constructor, " << n << "  " << this << endl; }
	~A()			 				{ cout << "<A> destroy, " << n << "  " << this << endl; }

	A& operator=(const A& src) { cout << "assign called, from A(" << &src << ")\n"; ; this->n = src.n; return *this;}

};
	std::ostream& 	operator<<(std::ostream& o, const A& a)
	{
		return (o << a.n);
	}

bool mycomp (char c1, char c2) { return std::tolower(c1)<std::tolower(c2); }
int main()
{

// ' is_integral
	// cout << ft::is_integral<int>::value << endl;
	// cout << ft::is_integral<const int>::value << endl;
	// cout << ft::is_integral<volatile int>::value << endl;
	// cout << ft::is_integral<const volatile int>::value << endl;
	// cout << ft::is_integral<char>::value << endl;
	// cout << ft::is_integral<signed char>::value << endl;
	// cout << ft::is_integral<string>::value << endl;


// ' iteratror_traits
	// cout << "int " << sizeof(ft::vector<int>::iterator::value_type) << endl;
	// cout << "float " << sizeof(ft::vector<float>::iterator::value_type) << endl;
	// cout << "long double " << sizeof(ft::vector<long double>::iterator::value_type) << endl;
	// cout << "void* " << sizeof(ft::vector<void*>::iterator::value_type) << endl;

// ' pair, make_pair
	// A a = A(123);
	// string s("123132");
	// ft::pair<A, string> p = ft::make_pair(a, s);
	// cout << p.first.n << endl;
	// cout << p.second << endl;

// ' vector
	A a = A(123);
	A b = A(456);
	A c = A(789);
	// cout << a.n << endl;

	// ft::vector<A> va;		//TODO: test const, if size == 0
	// cout << (va.empty() ? "empty" : "filled") << endl;
	// // va.pop_back();
	// cout<< "size: " << va.size()	 << endl;
	// cout<< "cap : " << va.capacity() << endl;
	// // std::vector<A>::iterator it	= va.begin();
	// // std::vector<A>::iterator ite	= va.end();
	// // va[5] = 10;
	// // for (int i = 0; it != ite; ++it)
	// // 	cout << "[" << i++ << "] " << it->n << endl;
	// // cout << va.at(5).n << endl;

// ' has_iterator_typedef

	// cout << ft::has_iterator_typedefs<int>::value << endl;
	// cout << ft::has_iterator_typedefs<ft::wrap_iter<int*> >::value << endl;

// ' lexicographical_compare

	// char foo[]="Apple";
	// char bar[]="apple";

	// cout << boolalpha;

	// cout << "Comparing foo and bar lexicographically (foo<bar):\n";

	// cout << "Using default comparison (operator<): ";
	// cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9);
	// cout << '\n';

	// cout << "Using mycomp as comparison object: ";
	// cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9,mycomp);
	// cout << '\n';


	// for (int i=0; i<100; i++) { myvector.push_back(i);  std::cout << "capacity: " << myvector.capacity() << "\n";}

	// std::cout << "size: " << fvector.size() << "\n";
	// std::cout << "capacity: " << fvector.capacity() << "\n";		// == 128
	// {
	// 	cout << "===========standard===========" << endl;
	// 	ft::vector<A> v;
	// 	std::cout << "max_size: " << v.max_size() << "\n";
	// 	std::cout << "size: " << v.size() << "\n";
	// 	std::cout << "capacity: " << v.capacity() << "\n";

	// 	v.push_back(a);
	// 	v.push_back(b);
	// 	v.push_back(c);
	// 	v.push_back(c);
	// 	v.push_back(c);
	// 	cout << "[0]" << v[0].n << endl;
	// 	cout << "[1]" << v[1].n << endl;
	// 	cout << "[2]" << v[2].n << endl;
	// 	cout << "[3]" << v[3].n << endl;
	// 	cout << "[4]" << v[4].n << endl;
	// 	std::cout << "size: " << v.size() << "\n";
	// 	std::cout << "capacity: " << v.capacity() << "\n";
	// 	v.assign(7, c);
	// 	cout << "[0]" << v[0].n << endl;
	// 	cout << "[1]" << v[1].n << endl;
	// 	cout << "[2]" << v[2].n << endl;
	// 	cout << "[3]" << v[3].n << endl;
	// 	cout << "[4]" << v[4].n << endl;
	// 	cout << "[5]" << v[5].n << endl;
	// 	cout << "[6]" << v[6].n << endl;
	// 	// cout << "[7]" << v[7].n << endl;
	// 	// cout << "[8]" << v[8].n << endl;
	// 	// cout << "[9]" << v[9].n << endl;
	// 	std::cout << "size: " << v.size() << "\n";
	// 	std::cout << "capacity: " << v.capacity() << "\n";
	// 	v.assign(3, b);
	// 	cout << "[0]" << v[0].n << endl;
	// 	cout << "[1]" << v[1].n << endl;
	// 	cout << "[2]" << v[2].n << endl;
	// 	// cout << "[3]" << v[3].n << endl;	//! destroyed!
	// 	// cout << "[4]" << v[4].n << endl;
	// 	// cout << "[5]" << v[5].n << endl;
	// 	// cout << "[6]" << v[6].n << endl;
	// 	// cout << "[7]" << v[7].n << endl;
	// 	// cout << "[8]" << v[8].n << endl;
	// 	// cout << "[9]" << v[9].n << endl;
	// 	std::cout << "size: " << v.size() << "\n";
	// 	std::cout << "capacity: " << v.capacity() << "\n";
	// }
	// 	cout << "==============================" << endl;

	// {
	// 	cout << "==============ft==============" << endl;
	// 	ft::vector<A> v;
	// 	std::cout << "max_size: " << v.max_size() << "\n";
	// 	std::cout << "size: " << v.size() << "\n";
	// 	std::cout << "capacity: " << v.capacity() << "\n";

	// 	v.push_back(a);
	// 	v.push_back(b);
	// 	v.push_back(c);
	// 	v.push_back(c);
	// 	v.push_back(c);
	// 	cout << "[0]" << v[0].n << endl;
	// 	cout << "[1]" << v[1].n << endl;
	// 	cout << "[2]" << v[2].n << endl;
	// 	cout << "[3]" << v[3].n << endl;
	// 	cout << "[4]" << v[4].n << endl;
	// 	std::cout << "size: " << v.size() << "\n";
	// 	std::cout << "capacity: " << v.capacity() << "\n";
	// 	v.assign(7, c);
	// 	cout << "[0]" << v[0].n << endl;
	// 	cout << "[1]" << v[1].n << endl;
	// 	cout << "[2]" << v[2].n << endl;
	// 	cout << "[3]" << v[3].n << endl;
	// 	cout << "[4]" << v[4].n << endl;
	// 	cout << "[5]" << v[5].n << endl;
	// 	cout << "[6]" << v[6].n << endl;
	// 	// cout << "[7]" << v[7].n << endl;
	// 	// cout << "[8]" << v[8].n << endl;
	// 	// cout << "[9]" << v[9].n << endl;
	// 	std::cout << "size: " << v.size() << "\n";
	// 	std::cout << "capacity: " << v.capacity() << "\n";
	// 	v.assign(3, b);
	// 	cout << "[0]" << v[0].n << endl;
	// 	cout << "[1]" << v[1].n << endl;
	// 	cout << "[2]" << v[2].n << endl;
	// 	// cout << "[3]" << v[3].n << endl;	//! destroyed!
	// 	// cout << "[4]" << v[4].n << endl;
	// 	// cout << "[5]" << v[5].n << endl;
	// 	// cout << "[6]" << v[6].n << endl;
	// 	// cout << "[7]" << v[7].n << endl;
	// 	// cout << "[8]" << v[8].n << endl;
	// 	// cout << "[9]" << v[9].n << endl;
	// 	std::cout << "size: " << v.size() << "\n";
	// 	std::cout << "capacity: " << v.capacity() << "\n";

	// 	std::cout << "size: " << v.size() << "\n";
	// 	std::cout << "capacity: " << v.capacity() << "\n";

	// }
	// 	cout << "==============================" << endl;


	// ' erase

        {
            // ft::vector<A> myvector;

            // // set some values (from 1 to 10)
            // for (int i=1; i<=10; i++) myvector.push_back(i);
            // 	std::cout << "myvector contains:";
            // for (unsigned i=0; i<myvector.size(); ++i)
            // 	std::cout << ' ' << myvector[i].n;
            // std::cout << '\n';

            // ft::vector<A>::iterator it;
            // cout << "erase the 6th element\n";
            // it = myvector.erase (myvector.begin()+5);
            // std::cout << "myvector contains:";
            // 	for (unsigned i=0; i<myvector.size(); ++i)
            // std::cout << ' ' << myvector[i].n;
            // std::cout << '\n';
            // cout << "return val is : " << it->n << endl;
            // cout << "new end is : " << (myvector.end() - 1)->n << endl;

            // cout <<  "erase the first 3 elements:\n";
            // it = myvector.erase (myvector.begin(),myvector.begin()+3);
            // std::cout << "myvector contains:";
            // for (unsigned i=0; i<myvector.size(); ++i)
            // 	std::cout << ' ' << myvector[i].n;
            // std::cout << '\n';
            // cout << "return val is : " << it->n << endl;
            // cout << "new end is : " << (myvector.end() - 1)->n << endl;

            // cout <<  "erase the last 3 elements:\n";
            // it = myvector.erase (myvector.end() - 4,myvector.end());
            // std::cout << "myvector contains:";
            // for (unsigned i=0; i<myvector.size(); ++i)
            // 	std::cout << ' ' << myvector[i].n;
            // std::cout << '\n';
            // if (myvector.end() == it )
            // cout << "ERASED LAST\n";
            // cout << "new end is : " << (myvector.end() - 1)->n << endl;
        }

        // ' insert
        {
			// A a(100);
			// std::vector<A> myvector(3, a);
			// std::vector<A>::iterator it;

			// it = myvector.begin();
			// std::cout << "myvector contains:";
			// for (it = myvector.begin(); it < myvector.end(); it++)
			// 	std::cout << ' ' << *it;
			// std::cout << '\n';

			// std::cout << "size		: " << myvector.size() << "\n";
			// std::cout << "capacity	: " << myvector.capacity() << "\n";
			// it = myvector.begin();
			// it = myvector.insert(it, 200);

			// std::cout << "myvector contains:";
			// for (it = myvector.begin(); it < myvector.end(); it++)
			// 	std::cout << ' ' << *it;
			// std::cout << '\n';


			// myvector.insert(it, 2, 300);
			// std::cout << "myvector contains:";
			// for (it = myvector.begin(); it < myvector.end(); it++)
			// 	std::cout << ' ' << *it;
			// std::cout << '\n';

			// std::vector<A> anothervector(2, 400);
			// // "it" no longer valid, get a new one:
			// it = myvector.begin();

			// myvector.insert(it + 2, anothervector.begin(), anothervector.end());
			// std::cout << "myvector contains:";
			// for (it = myvector.begin(); it < myvector.end(); it++)
			// 	std::cout << ' ' << *it;
			// std::cout << '\n';

			// A myarray[] = {501, 502, 503};
			// myvector.insert(myvector.begin(), myarray, myarray + 3);

			// std::cout << "myvector contains:";
			// for (it = myvector.begin(); it < myvector.end(); it++)
			// 	std::cout << ' ' << *it;
			// std::cout << '\n';
        }

		// std::vector<A> myvector(3, A(10));
		// std::vector<A>::iterator it;
		// std::vector<A>::iterator it2;
		// std::cout << "myvector contains:";
		// for (it = myvector.begin(); it < myvector.end(); it++)
		// 	std::cout << ' ' << "["<< *it << "]";
		// std::cout << '\n';

		// A arr[] = { 1, 2, 3 };
		// it = myvector.begin();
		// // myvector.realloc_and_move(it + 1, arr, arr + 2);
		// it2 = myvector.insert(it + 1, 999);
		// std::cout << "myvector contains:";
		// for (it = myvector.begin(); it < myvector.end(); it++)
		// 	std::cout << ' ' << "["<< *it << "]";
		// std::cout << '\n';
		// 	std::cout << "size: " << myvector.size() << "\n";
		// std::cout << "capacity: " << myvector.capacity() << "\n";
		// std::cout << "return: " << it2->n << "\n";

		// it = myvector.begin();
		// it2 = myvector.insert(it + 1, 111);
		// std::cout << "myvector contains:";
		// for (it = myvector.begin(); it < myvector.end(); it++)
		// {
		// 	std::cout << ' ' << "["<< *it << "]";
		// }
		// std::cout << '\n';
		// for (it = myvector.begin(); it < myvector.end(); it++)
		// {
		// 	std::cout << ' ' << "["<< &*it << "]";

		// }
		// std::cout << '\n';
		// std::cout << "return: " << it2->n << "\n";

		// std::vector<A>				myvector;
		// std::vector<A>::iterator	it;
		// std::vector<A>::iterator	ite;
		// myvector.push_back(0);
		// myvector.push_back(0);

		// // myvector.push_back(0);
		// // myvector.push_back(0);
		// // myvector.push_back(0);
		// // myvector.push_back(0);
		// // myvector.clear();

		// // myvector.push_back(10);
		// // myvector.push_back(20);
		// // myvector.push_back(30);
		// // myvector.push_back(40);
		// A arr[] = { 1, 2, 3, 4 };

		// cout << "size = " << myvector.size() << endl
		// 	<<  "capa = " << myvector.capacity() << endl;
		// // myvector.insert(myvector.begin() + 1, myvector.begin(), myvector.end());
		// myvector.insert(myvector.begin() + 2, arr, arr+4);

		// std::cout << "myvector contains:";
		// for (it = myvector.begin(); it < myvector.end(); it++)
		// 	std::cout << ' ' << "["<< *it << "]";
		// std::cout << '\n';

		// cout << "size = " << myvector.size() << endl
		// 	<<  "capa = " << myvector.capacity() << endl;
		// myvector.clear();
		// cout << std::boolalpha ;
		// myvector.push_back(a);
		// myvector.push_back(a);
		// myvector.push_back(a);
		// myvector.push_back(a);
		// cout << "size = " << myvector.size() << endl
		// 	<<  "capa = " << myvector.capacity() << endl;
		// cout << (myvector.begin() == myvector.end()) << endl;


		// it = myvector.begin();
		// // ite = myvector.end();
		// // cout << it->n <<endl;
		// // cout << ite->n <<endl;
		// cout << "~~~~~~~~~~~~~~~~~\n";

		// // myvector.insert(it + 1, arr, arr + 3);

		// std::cout << "myvector contains:";
		// for (it = myvector.begin(); it < myvector.end(); it++)
		// 	std::cout << ' ' << "["<< *it << "]";
		// std::cout << '\n';

		//' swap
		{
			// ft::vector<int> foo (3,100);   // three ints with a value of 100
			// ft::vector<int> bar (5,200);   // five ints with a value of 200

			// foo.swap(bar);

			// std::cout << "foo contains:";
			// for (unsigned i=0; i<foo.size(); i++)
			// 	std::cout << ' ' << foo[i];
			// // std::allocator<int> a1 = foo.get_allocator();
			// std::cout << " | foo.cap : " << foo.capacity() << " foo.size : " << foo.size();
			// std::cout << '\n';

			// std::cout << "bar contains:";
			// for (unsigned i=0; i<bar.size(); i++)
			// 	std::cout << ' ' << bar[i];
			// std::cout << " | bar.cap : " << bar.capacity() << " bar.size : " << bar.size();
			// std::cout << '\n';
		}

                std::vector<float> myvector;
                for (int i = 1; i < 10; i++)
                  myvector.push_back(i);

                typedef std::vector<float>::iterator	iter_type;
                													// ? 9 8 7 6 5 4 3 2 1 0 ?
                iter_type from(myvector.begin()); 					//   ^
                                                  					//         ------>
                iter_type until(myvector.end());  					//                       ^
                                                  					//
                std::reverse_iterator<iter_type> rev_until(from); 	// ^                           											//         <------
                std::reverse_iterator<iter_type> rev_from(until); 	//                     ^


                // std::cout << "myvector:";
                // while (rev_from != rev_until)
                //   std::cout << ' ' << *rev_from++;
                // std::cout << '\n';
				cout << *from << endl;
				cout << *(until-1) << endl;

				cout << *(rev_from) << endl;		// should be rev_from
				cout << *(rev_until-1) << endl;		// should be rev_until-1

				cout << boolalpha << ((rev_until).base() == from) << endl;


				// ! constructible with forward-iterator, but only works with bi-directional or random-access iterator
				std::forward_list<int> flist;
				flist.push_front(10);
				typedef std::forward_list<int>::iterator forward_iter;
				forward_iter it = flist.begin();
				std::reverse_iterator<forward_iter> rit(it);

				rit++;
				// rit--;

}


/* alloc strategy


template <class _Tp, class _Allocator>
typename vector<_Tp, _Allocator>::size_type
vector<_Tp, _Allocator>::max_size() const _NOEXCEPT
{
    return _VSTD::min<size_type>(__alloc_traits::max_size(this->__alloc()),
                                 numeric_limits<difference_type>::max());

vector<_Tp, _Allocator>::__recommend(size_type __new_size) const
{
    const size_type __ms = max_size();
    if (__new_size > __ms)
        this->__throw_length_error();
    const size_type __cap = capacity();
    if (__cap >= __ms / 2)
        return __ms;
    return _VSTD::max<size_type>(2*__cap, __new_size);
}



}


*/
