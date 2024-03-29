/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:42:34 by mishin            #+#    #+#             */
/*   Updated: 2022/04/02 22:55:57 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP
namespace ft
{
template <class T1, class T2> struct pair
{
	typedef T1	first_type;
	typedef T2	second_type;

	T1			first;
	T2			second;

/**========================================================================
* @                           Constructors
*========================================================================**/

	pair()								: first(), second() {}
    pair(const T1& t1, const T2& t2)	: first(t1), second(t2)	{}

	template <class U1, class U2>
    pair(const pair<U1, U2>& src)		: first(src.first), second(src.second) {}

/**========================================================================
* *                            operators
*========================================================================**/

	pair& operator=(pair const& src)
	{
		if (this == &src)	return (*this);

		first	= src.first;
        second	= src.second;

		return (*this);
    }
};

/**========================================================================
* *                          non-member operators
*========================================================================**/
template <class T1, class T2> bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first==rhs.first && lhs.second==rhs.second; }
template <class T1, class T2> bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs==rhs); }
template <class T1, class T2> bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }	// lhs.first == rhs.first && lhs.second < rhs.second
template <class T1, class T2> bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(rhs<lhs); }
template <class T1, class T2> bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return rhs<lhs; }
template <class T1, class T2> bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) { return !(lhs<rhs); }

/**========================================================================
* #                         non-member functions
*========================================================================**/

template <class T1,class T2>
pair<T1,T2> make_pair (T1 x, T2 y)	{ return ( pair<T1,T2>(x,y) ); }

}

// C++98 : cannot infer template arguments from the constructor.
#endif


