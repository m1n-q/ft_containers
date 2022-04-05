/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:37:00 by mishin            #+#    #+#             */
/*   Updated: 2022/04/05 17:31:42 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"
namespace ft
{

template <class T, class Container = vector<T> >
class stack
{
/**========================================================================
* '                              typedefs
*========================================================================**/
public:
	typedef Container                                container_type;
    typedef typename container_type::value_type      value_type;
    typedef typename container_type::size_type       size_type;

/**========================================================================
* @                           Constructors
*========================================================================**/
	explicit stack(const container_type& cont = container_type())
	: c(cont) {}

protected:
	container_type	c;

public:
/**========================================================================
* #                          member functions
*========================================================================**/
	bool				empty() const					{ return c.empty(); }
	size_type			size() const					{ return c.size(); }
	value_type&			top()							{ return c.back(); }
	const value_type&	top() const						{ return c.back(); }
	void				push(const value_type& val)		{ c.push_back(val); }
	void				pop()							{ c.pop_back(); }



	template <class _T, class _Cont>
	friend bool	operator==(const stack<_T, _Cont>& __x, const stack<_T, _Cont>& __y);

	template <class _T, class _Cont>
	friend bool	operator< (const stack<_T, _Cont>& __x, const stack<_T, _Cont>& __y);
};

/**========================================================================
* *                        relational-operators
*========================================================================**/

template <class T, class Container>
bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{ return lhs.c == rhs.c; }
template <class T, class Container>
bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{ return lhs.c < rhs.c; }

template <class T, class Container>
bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{ return !(lhs == rhs); }
template <class T, class Container>
bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{ return rhs < lhs; }
template <class T, class Container>
bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{ return !(lhs < rhs); }
template <class T, class Container>
bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{ return !(lhs > rhs); }

}

#endif
