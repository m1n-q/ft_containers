/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:37:00 by mishin            #+#    #+#             */
/*   Updated: 2022/03/09 23:48:48 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"
# include <cstddef>
# include <stack>

/*
	! Your stack will use your vector class as default underlaying container,
	! it must still be compatible with others containers like the STL one
*/
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
	: _cont(cont) {}

protected:
	container_type	_cont;

public:
/**========================================================================
* #                          member functions
*========================================================================**/
	bool				empty() const					{ return _cont.empty(); }
	size_type			size() const					{ return _cont.size(); }
	value_type&			top()							{ return _cont.back(); }
	const value_type&	top() const						{ return _cont.back(); }
	void				push(const value_type& val)		{ _cont.push_back(val); }
	void				pop()							{ _cont.pop_back(); }



	template <class _T, class _Cont>
	friend bool	operator==(const stack<_T, _Cont>& __x, const stack<_T, _Cont>& __y);

	template <class _T, class _Cont>
	friend bool	operator< (const stack<_T, _Cont>& __x, const stack<_T, _Cont>& __y);
};

/**========================================================================
* *                        relational-operators
*========================================================================**/

template <class T, class Container>
bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{ return lhs._cont == rhs._cont; }
template <class T, class Container>
bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{ return lhs._cont < rhs._cont; }

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
