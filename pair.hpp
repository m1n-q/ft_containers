/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:42:34 by mishin            #+#    #+#             */
/*   Updated: 2022/03/05 23:45:26 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP
# include <typeinfo> // DELETE
namespace ft
{
	template <class T1, class T2> struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;
		T1	first;
		T2	second;

/**========================================================================
* @                           Constructors
*========================================================================**/

		pair() : first(), second() {}
    	pair(T1 const& __t1, T2 const& __t2) : first(__t1), second(__t2)
		{ }
    	template <class U1, class U2>
    	pair(const pair<U1, U2>& src) : first(src.first), second(src.second) {}

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
pair<T1,T2> make_pair (T1 x, T2 y)
{
	return ( pair<T1,T2>(x,y) );
}

}
#endif


