/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:05:57 by mishin            #+#    #+#             */
/*   Updated: 2022/04/01 22:51:04 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

/**----------------------------------------------------------------------------
 * ! check reverse_iterator
 *----------------------------------------------------------------------------*/

namespace ft
{
template <class T>
struct iterator_traits;

template <class Iter>
class reverse_iterator
{
public:
/**========================================================================
* '                              typedef
*========================================================================**/
	typedef Iter													base_type;
	typedef typename iterator_traits<base_type>::difference_type	difference_type;
    typedef typename iterator_traits<base_type>::value_type			value_type;
    typedef typename iterator_traits<base_type>::pointer			pointer;
    typedef typename iterator_traits<base_type>::reference			reference;
    typedef typename iterator_traits<base_type>::iterator_category	iterator_category;
private:
	base_type   __base;
public:
    reverse_iterator()							    : __base()				{}
    explicit reverse_iterator(base_type b)		    : __base(b)				{}

    template <class U>
    reverse_iterator(const reverse_iterator<U>& other): __base(other.base())	{}

public:
/**========================================================================
* *                            operators										//TODO: CHECK
*========================================================================**/
	// ' Internally, the function decreases a copy of its base iterator and returns the result of dereferencing it.
	reference			operator*() const						{ Iter tmp(__base); return *(--tmp); }
    pointer				operator->() const						{ return (&operator*()); }
    reverse_iterator	operator++()							{ --__base; return *this; }
    reverse_iterator	operator++(int)							{ reverse_iterator tmp(*this); --__base; return tmp; }
    reverse_iterator&	operator--()							{ ++__base; return *this; }
    reverse_iterator	operator--(int)							{ reverse_iterator tmp(*this); ++__base; return tmp; }
    reverse_iterator	operator+ (difference_type n) const		{ return reverse_iterator(__base - n); }
    reverse_iterator&	operator+=(difference_type n)			{ __base -= n; return *this; }
    reverse_iterator	operator- (difference_type n) const		{ return reverse_iterator(__base + n); }
    reverse_iterator&	operator-=(difference_type n)			{ __base += n; return *this; }
    reference			operator[](difference_type n) const		{ return *(*this + n); }


    base_type			base(void) const						{ return this->__base; }
};

template <class Iter1, class Iter2>
bool
operator==(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
{
    return x.base() == y.base();
}
template <class Iter1, class Iter2>
bool
operator!=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
{
    return x.base() != y.base();
}

template <class Iter1, class Iter2>
bool
operator<(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
{
    return x.base() > y.base();
}


template <class Iter1, class Iter2>
bool
operator>(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
{
    return x.base() < y.base();
}

template <class Iter1, class Iter2>
bool
operator>=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
{
    return x.base() <= y.base();
}

template <class Iter1, class Iter2>
bool
operator<=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
{
    return x.base() >= y.base();
}

template <class Iter1, class Iter2>
typename reverse_iterator<Iter1>::difference_type
operator-(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y)
{
    return y.base() - x.base();
}


template <class Iter>
reverse_iterator<Iter>
operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& x)
{
    return reverse_iterator<Iter>(x.base() - n);
}


}
#endif
