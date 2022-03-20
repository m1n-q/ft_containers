#include <cstddef>
#include <cstdio>
#include <exception>
#include <ios>
#include <iterator>
#include <limits>
#include <type_traits>
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <utility>
#include <vector>
#include <forward_list>
#include <functional>
#include <fstream>
#include <__tree>

#include "is_integral.hpp"
#include "tree_iter.hpp"
#include "vector.hpp"
#include "pair.hpp"
#include "algorithm.hpp"
#include "stack.hpp"
#include "tree.hpp"
#include "map.hpp"


/* !
 # iterators_traits					// TODO: wrapper for other tags, check arithmetics (opeators)
 ! reverse_iterator					// TODO: wrapper for other tags, check arithmetics (opeators)
 @ enable_if
 @ is_integral
 @ equal/lexicographical compare	//TODO: test
 @ pair
 @ make_pair

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
	cout << boolalpha;
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
	// A a = A(123);
	// A b = A(456);
	// A c = A(789);
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
			// ft::vector<A> myvector(3, a);
			// ft::vector<A>::iterator it;

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
			// myvector.insert(myvector.begin() + 1, 3, 999);

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






		// ' reverse_iterator
		{
			// std::vector<float> myvector;
			// for (int i = 1; i < 10; i++)
			// 	myvector.push_back(i);

			// typedef std::vector<float>::iterator	iter_type;
			// 													// ? 9 8 7 6 5 4 3 2 1 0 ?
			// iter_type from(myvector.begin()); 					//   ^
			// 													//         ------>
			// iter_type until(myvector.end());  					//                       ^
			// 													//
			// std::reverse_iterator<iter_type> rev_until(from); 	// ^                           											//         <------
			// std::reverse_iterator<iter_type> rev_from(until); 	//                     ^


			// // std::cout << "myvector:";
			// // while (rev_from != rev_until)
			// //   std::cout << ' ' << *rev_from++;
			// // std::cout << '\n';
			// cout << *from << endl;
			// cout << *(until-1) << endl;

			// cout << *(rev_from) << endl;		// should be rev_from
			// cout << *(rev_until-1) << endl;		// should be rev_until-1

			// cout << boolalpha << ((rev_until).base() == from) << endl;
		}


			// // ! constructible with forward-iterator, but only works with bi-directional or random-access iterator
			// std::forward_list<int> flist;
			// flist.push_front(10);
			// typedef std::forward_list<int>::iterator forward_iter;
			// forward_iter it = flist.begin();
			// std::reverse_iterator<forward_iter> rit(it);

			// rit++;
			// // rit--;



			// ' range constructor
			// A arr[] = { 1, 2, 3 };
			// ft::vector<A> vv(arr, arr+3);
			// for (unsigned i = 0; i < vv.size(); i++)
			// 	cout << vv[i] << endl;
			// cout << vv.capacity() << endl;
			// cout << "=============" << endl;

			// ft::vector<A> vv2(vv);
			// for (unsigned i = 0; i < vv2.size(); i++)
			// 	cout << vv2[i] << endl;
			// cout << vv2.capacity() << endl;
// ' assign
	// ft::vector<A> first;
	// ft::vector<A> second;
	// ft::vector<A> third;

	// first.assign (7,100);             // 7 ints with a value of 100

	// ft::vector<A>::iterator it;
	// it=first.begin()+1;

	// second.push_back(1000);
	// second.push_back(1000);
	// second.push_back(1000);
	// second.push_back(1000);
	// second.push_back(1000);
	// second.assign (it,first.end()-1); // the 5 central values of first

	// A myints[] = {1776,7,4};
	// third.assign (myints,myints+3);   // assigning from array.

	// std::cout << "Size of first: " << int (first.size()) << '\n';
	// std::cout << "Size of second: " << int (second.size()) << '\n';
	// std::cout << "Size of third: " << int (third.size()) << '\n';

	// std::cout << "Cap of first: " << int (first.capacity()) << '\n';
	// std::cout << "Cap of second: " << int (second.capacity()) << '\n';
	// std::cout << "Cap of third: " << int (third.capacity()) << '\n';

// ' stack
	// ft::stack<int> a;


	// a.push(10);
	// a.push(11);
	// a.push(12);

	// cout << a.top() <<endl;
	// cout << boolalpha<< a.empty() << endl;
	// a.pop();
	// cout << a.top() <<endl;
	// a.pop();
	// cout << a.top() <<endl;
	// a.pop();
	// cout << boolalpha<< a.empty() << endl;



// ' map
/*
	ft::map<char, int,less<char> > sm;
	ft::map<char, int>::iterator it;
	ft::pair<ft::map<char, int>::iterator, bool> ret;
	cout << boolalpha;

	ret = sm.insert(ft::pair<char, int>('a', 200));
	cout  << ret.first->first << " " << ret.second <<  endl;
	ret = sm.insert(ft::pair<char, int>('c', 200));
	cout  << ret.first->first << " " << ret.second <<  endl;
	ret = sm.insert(ft::pair<char, int>('d', 300));
	cout  << ret.first->first << " " << ret.second <<  endl;
	ret = sm.insert(ft::pair<char, int>('g', 400));
	cout  << ret.first->first << " " << ret.second <<  endl;
	ret = sm.insert(ft::pair<char, int>('b', 400));
	cout  << ret.first->first << " " << ret.second <<  endl;
	ret = sm.insert(ft::pair<char, int>('f', 400));
	cout  << ret.first->first << " " << ret.second <<  endl;
	ret = sm.insert(ft::pair<char, int>('h', 400));
	cout  << ret.first->first << " " << ret.second <<  endl;
	ret = sm.insert(ft::pair<char, int>('e', 400));
	cout  << ret.first->first << " " << ret.second <<  endl;

	for (it = sm.begin(); it != sm.end(); it++)
		cout << "(" << it->first << ", " << it->second << ") ";
	cout << endl;



	//NOTE: it++;		//ft::map : end()++ -> SEGV
	//NOTE: it--;		//ft::map : begin()-- -> SEGV

	// it--;
	// cout << it->first << endl;
	// it--;
	// cout << it->first << endl;
	// it--;
	// cout << it->first << endl;
	// it--;
	// cout << it->first << endl;


	ret = sm.insert(ft::pair<char, int>('a', 300));		// ignored

	cout << ret.first->first << " " << ret.second <<  endl;
	sm.erase(--sm.end());
	// sm.erase('c');

	// sm.tree.print_inorder(sm.tree._root);



	for (it = sm.begin(); it != sm.end(); it++)
		cout << "(" << it->first << ", " << it->second << ") ";
	cout << endl;




	it = sm.insert(sm.begin(), ft::pair<char, int>('A', 1000));

	cout << it->first << ", " << it->second << endl;

	it = sm.insert(sm.end(), ft::pair<char, int>('h', 1000));
	cout << it->first << ", " << it->second << endl;


	for (it = sm.begin(); it != sm.end(); it++)
		cout << "(" << it->first << ", " << it->second << ") ";
	cout << endl;

	it = sm.end();
	it--;
	cout << it->first << ", " << it->second << endl;

	sm.erase('A');
	for (it = sm.begin(); it != sm.end(); it++)
		cout << "(" << it->first << ", " << it->second << ") ";
	cout << endl;

*/

/*
	ft::map<int, string> m;
	ft::map<int, string>::iterator i;
	ft::map<int, string>::reverse_iterator ri;

	vector<ft::pair<int, string> > tmp;
	tmp.push_back(ft::pair<int, string>(13, "from vector"));
	tmp.push_back(ft::pair<int, string>(1, "from vector"));
	tmp.push_back(ft::pair<int, string>(15, "from vector"));
	tmp.push_back(ft::pair<int, string>(12, "from vector"));
	tmp.push_back(ft::pair<int, string>(17, "from vector"));
	tmp.push_back(ft::pair<int, string>(2, "from vector"));
	tmp.push_back(ft::pair<int, string>(4, "from vector"));
	tmp.push_back(ft::pair<int, string>(7, "from vector"));
	tmp.push_back(ft::pair<int, string>(111, "from vector"));
	tmp.push_back(ft::pair<int, string>(222, "from vector"));
	tmp.push_back(ft::pair<int, string>(333, "from vector"));



	m.insert(ft::pair<int, string>(-1, "org"));


	m.insert(ft::pair<int, string>(0, "org"));
	m.insert(ft::pair<int, string>(1, "org"));
	m.insert(ft::pair<int, string>(2, "org"));
	m.insert(ft::pair<int, string>(3, "org"));
	m.insert(ft::pair<int, string>(4, "org"));
	m.insert(ft::pair<int, string>(5, "org"));
	m.insert(ft::pair<int, string>(100, "org"));
	m.insert(ft::pair<int, string>(200, "org"));
	m.insert(ft::pair<int, string>(300, "org"));

	for (i = m.begin(); i != m.end(); i++)
		cout << "(" << i->first << ", " << i->second << ") ";
	cout << endl;
	m.insert(tmp.begin(), tmp.end());



	for (i = m.begin(); i != m.end(); i++)
		cout << "(" << i->first << ", " << i->second << ") ";
	cout << endl;


	cout << "=============================" << endl;


	for (ri = m.rbegin(); ri != m.rend(); ri++)
		cout << "(" << ri->first << ", " << ri->second << ") ";
	cout << endl;


	m[333] = "is changed";
	m[999] = "New Value inserted";


	for (ri = m.rbegin(); ri != m.rend(); ri++)
		cout << "(" << ri->first << ", " << ri->second << ") ";
	cout << endl;
	m.clear();
	cout << (m.begin() == m.end()) << endl;
	cout << "=============================" << endl;
	for (ri = m.rbegin(); ri != m.rend(); ri++)
		cout << "(" << ri->first << ", " << ri->second << ") ";
	cout << endl;

	// m.erase(m.begin(), m.end());

	// cout << "==============================================" << endl;
	// m.insert(ft::make_pair(1, "maama"));


	// for (i = m.begin(); i != m.end(); i++)
	// 	cout << "(" << i->first << ", " << i->second << ") ";
	// cout << endl;

	// i = m.begin();
	// i->first = 10;	//! cannot change key.
*/

	std::allocator<ft::pair<const char, string> > ma;
	std::less<char>	kc;
	ft::map<char, string> m1(kc, ma);
	ft::map<char, string> m2(kc, ma);
	ft::map<char, string>::iterator it;



	m1.insert(ft::make_pair('b', "beta"));
	m1.insert(ft::make_pair('c', "gamma"));
	m1.insert(ft::make_pair('a', "alpha"));



	// m2.insert(ft::make_pair('A', "ALPHA"));
	// m2.insert(ft::make_pair('B', "BETA"));
	// m2.insert(ft::make_pair('E', "EMMET"));
	// m2.insert(ft::make_pair('D', "DRAG"));
	// m2.insert(ft::make_pair('C', "HAMMER"));


	cout << "m1 contains : ";
	for (it = m1.begin(); it != m1.end(); it++)
		cout << "(" << it->first << ", " << it->second << ") ";
	cout << endl;

	cout << "m2 contains : ";
	for (it = m2.begin(); it != m2.end(); it++)
		cout << "(" << it->first << ", " << it->second << ") ";
	cout << endl;
	cout << (m1.begin() == m1.end()) << endl;
	cout << (m2.begin() == m2.end()) << endl;

	m1.swap(m2);
	cout << "AFTER SWAP: " << endl;

	cout << "m1 contains : ";
	for (it = m1.begin(); it != m1.end(); it++)
		cout << "(" << it->first << ", " << it->second << ") ";
	cout << endl;

	cout << "m2 contains : ";
	for (it = m2.begin(); it != m2.end(); it++)
		cout << "(" << it->first << ", " << it->second << ") ";
	cout << endl;

	cout << (m1.begin() == m1.end()) << endl;
	cout << (m2.begin() == m2.end()) << endl;

	m1.insert(ft::make_pair('k', "NEW"));
	m2.insert(ft::make_pair('f', "NEW"));
	cout << "m1 contains : ";
	for (it = m1.begin(); it != m1.end(); it++)
		cout << "(" << it->first << ", " << it->second << ") ";
	cout << endl;

	cout << "m2 contains : ";
	for (it = m2.begin(); it != m2.end(); it++)
		cout << "(" << it->first << ", " << it->second << ") ";
	cout << endl;

	cout << (m1.begin() == m1.end()) << endl;
	cout << (m2.begin() == m2.end()) << endl;

	m2['f'] = "ABCDE";
	cout << "m2 contains : ";
	for (it = m2.begin(); it != m2.end(); it++)
		cout << "(" << it->first << ", " << it->second << ") ";
	cout << endl;

	m1['k'] = m1['p'] = "THREE";
	cout << "m1 contains : ";
	for (it = m1.begin(); it != m1.end(); it++)
		cout << "(" << it->first << ", " << it->second << ") ";
	cout << endl;

	cout << (m1.get_allocator() == ma) << endl;

	it = m1.lower_bound('b');

	cout << it->first << endl;

	ft::map<char, string> mc(m2);

	cout << "mc contains : ";
	for (it = mc.begin(); it != mc.end(); it++)
		cout << "(" << it->first << ", " << it->second << ") ";
	cout << endl;

	mc.erase(mc.begin());


	cout << (mc.begin() == mc.end() ) << endl;

	cout << "after erase mc.begin() =========>" << endl;
	cout << "m2 contains : ";
	for (it = m2.begin(); it != m2.end(); it++)
		cout << "(" << it->first << ", " << it->second << ") ";
	cout << endl;
	cout << "mc contains : ";
	for (it = mc.begin(); it != mc.end(); it++)
		cout << "(" << it->first << ", " << it->second << ") ";
	cout << endl;
	cout << "mc contains : ";
	for (it = mc.begin(); it != mc.end(); it++)
		cout << "(" << it->first << ", " << it->second << ") ";
	cout << endl;


	ft::map<char, string> mccc;

	mccc = mc;
	cout << (mc.get_allocator() == mccc.get_allocator()) << endl;

	mccc.erase(mccc.begin());
	cout << "mc contains : ";
	for (it = mc.begin(); it != mc.end(); it++)
		cout << "(" << it->first << ", " << it->second << ") ";
	cout << endl;
	cout << "mccc contains : ";
	for (it = mccc.begin(); it != mccc.end(); it++)
		cout << "(" << it->first << ", " << it->second << ") ";
	cout << endl;
	// m1.key_comp();
	// m1.value_comp();

	ft::map<int, int>::iterator mit;
	ft::map<int, int> mi;
	ft::map<int, int> mi3;

	mi.insert(mi.end(), ft::make_pair(12, 0));
	ft::map<int, int> mi2(mi);
	mi2.insert(ft::make_pair(10, 0));
	mi.insert(mi.end(), ft::make_pair(13, 0));
	cout << "mi contains : ";
	for (mit = mi.begin(); mit != mi.end(); mit++)
		cout << "(" << mit->first << ", " << mit->second << ") ";
	cout << endl;
	cout << "mi2 contains : ";
	for (mit = mi2.begin(); mit != mi2.end(); mit++)
		cout << "(" << mit->first << ", " << mit->second << ") ";
	cout << endl;
	mi3 = mi2;
	mi3[11] = 31;

	cout << "mi contains : ";
	for (mit = mi.begin(); mit != mi.end(); mit++)
		cout << "(" << mit->first << ", " << mit->second << ") ";
	cout << endl;
	cout << "mi2 contains : ";
	for (mit = mi2.begin(); mit != mi2.end(); mit++)
		cout << "(" << mit->first << ", " << mit->second << ") ";
	cout << endl;
	cout << "mi3 contains : ";
	for (mit = mi3.begin(); mit != mi3.end(); mit++)
		cout << "(" << mit->first << ", " << mit->second << ") ";
	cout << endl;

	cout << "mi3 size : " << mi3.size() << endl;

	cout << (mi2.key_comp()(11, 10)) << endl;
	cout << (mi2.value_comp()(ft::make_pair(9, 999), ft::make_pair(10, 1))) << endl;


	// #at param

	//@ erase, erase(range)


	mi3.insert(mi3.begin(), ft::make_pair(9 , -1));
	cout << "mi3 contains : ";
	for (mit = mi3.begin(); mit != mi3.end(); mit++)
		cout << "(" << mit->first << ", " << mit->second << ") ";
	cout << endl;

	return 0;
}


// class Base
// {
// private:
// 	int	data;

// public:
// 	Base(int d): data(d) {}
// };

// class Derived: public Base
// {

// };

// int main()
// {
// 	Derived d(1);
// }
