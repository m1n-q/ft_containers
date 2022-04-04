/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrap_iter.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 02:32:58 by mishin            #+#    #+#             */
/*   Updated: 2022/04/05 02:36:44 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAP_ITER_HPP
# define WRAP_ITER_HPP
# include "iterator.hpp"

namespace ft
{
//NOTE: for vector (random_access_iterator, pointer)
template <class T> class wrap_iter
{
public:
/**========================================================================
* '                              typedef
*========================================================================**/
	typedef T														base_type;
	typedef typename iterator_traits<base_type>::difference_type	difference_type;
    typedef typename iterator_traits<base_type>::value_type			value_type;
    typedef typename iterator_traits<base_type>::pointer			pointer;
    typedef typename iterator_traits<base_type>::reference			reference;
    typedef typename iterator_traits<base_type>::iterator_category	iterator_category;
private:
	base_type __base;

public:
/**========================================================================
* @                           Constructors
*========================================================================**/
	wrap_iter()                         : __base()				{}
	wrap_iter(base_type b)			    : __base(b)				{};
	wrap_iter(const wrap_iter& src)     : __base(src.base())    {};
    template <typename U>
	wrap_iter(const wrap_iter<U>& src,
              typename enable_if<is_convertible<U, base_type>::value, U>::type* = 0)
                                        : __base(src.base())	{};
	~wrap_iter() {};

    wrap_iter&  operator=(const wrap_iter& src)
    {
        if (this == &src)       return *this;

        this->__base    = src.base();

        return *this;
    }

/**========================================================================
* *                            operators
*========================================================================**/
	reference	operator*() const						{ return *__base; }
    pointer		operator->() const						{ return __base; }     //' (C->m) is interpreted as (C.operator->())->m
    wrap_iter&	operator++()							{ ++__base; return *this; }
    wrap_iter	operator++(int)							{ wrap_iter tmp(*this); ++(*this); return tmp; }
    wrap_iter&	operator--()							{ --__base; return *this; }
    wrap_iter	operator--(int)							{ wrap_iter tmp(*this); --(*this); return tmp; }
    wrap_iter&	operator+=(difference_type n)			{  __base += n; return *this; }
    wrap_iter	operator+ (difference_type n) const		{ wrap_iter tmp(*this); tmp += n; return tmp; }
    wrap_iter&	operator-=(difference_type n)			{ *this += -n; return *this; }
    wrap_iter	operator- (difference_type n) const		{ return (*this + (-n)); }
    reference	operator[](difference_type n) const		{ return __base[n]; }

    base_type base() const  {return __base;}
};

/**========================================================================
* *                        non-member operators
*========================================================================**/
// @ T1 or T2 can be cv-qualified
template <class T1, class T2>
bool operator==(const wrap_iter<T1>& x, const wrap_iter<T2>& y) { return x.base() == y.base(); }
template <class T1, class T2>
bool operator!=(const wrap_iter<T1>& x, const wrap_iter<T2>& y) { return x.base() != y.base(); }
template <class T1, class T2>
bool operator<(const wrap_iter<T1>& x, const wrap_iter<T2>& y)  { return x.base() < y.base(); }
template <class T1, class T2>
bool operator>(const wrap_iter<T1>& x, const wrap_iter<T2>& y)  { return x.base() > y.base(); }
template <class T1, class T2>
bool operator<=(const wrap_iter<T1>& x, const wrap_iter<T2>& y) { return x.base() <= y.base(); }
template <class T1, class T2>
bool operator>=(const wrap_iter<T1>& x, const wrap_iter<T2>& y) { return x.base() >= y.base(); }

/**========================================================================
 * @ According to the resolution of DR179 not only the various comparison
 * @ operators but also operator- must accept mixed iterator/const_iterator
 * @ parameters.
 *=========================================================================*/
template <class T1, class T2>
typename wrap_iter<T1>::difference_type
operator-(const wrap_iter<T1>& x, const wrap_iter<T2>& y)       { return x.base() - y.base(); }

template <class T1>
wrap_iter<T1>
operator+(typename wrap_iter<T1>::difference_type n, wrap_iter<T1> x)
{
    x += n;
    return x;
}

template <class T>  T unwrap_iter(T type)											{ return type; }
template <class T>	typename wrap_iter<T>::base_type unwrap_iter(wrap_iter<T> it)	{ return it.base(); }
}
#endif
