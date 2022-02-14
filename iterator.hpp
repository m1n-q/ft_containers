/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:57:52 by mishin            #+#    #+#             */
/*   Updated: 2022/02/14 23:18:17 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>
#include <memory>

#include "is_integral.hpp"
#include "enable_if.hpp"
namespace ft
{
	struct input_iterator_tag	{};
	struct output_iterator_tag	{};
	struct forward_iterator_tag			: public input_iterator_tag         {};
	struct bidirectional_iterator_tag	: public forward_iterator_tag       {};
	struct random_access_iterator_tag	: public bidirectional_iterator_tag {};

template <class Iter> struct iterator_traits
{
	typedef typename Iter::difference_type		difference_type;
    typedef typename Iter::value_type			value_type;
    typedef typename Iter::pointer				pointer;
    typedef typename Iter::reference			reference;
    typedef typename Iter::iterator_category	iterator_category;
};
template <class T> struct iterator_traits<T*>
{
	typedef ptrdiff_t					difference_type;
    typedef T							value_type;
    typedef T*							pointer;
    typedef T&							reference;
    typedef random_access_iterator_tag	iterator_category;
};
template <class T> struct iterator_traits<const T*>
{
	typedef ptrdiff_t					difference_type;
    typedef T							value_type;
    typedef const T*					pointer;
    typedef const T&					reference;
    typedef random_access_iterator_tag	iterator_category;
};


template <class T> struct __void_t
{ typedef void type; };

template <class T> struct has_iterator_typedefs	// check for iterator_traits<Iter>
{
// private:
public:
    struct __two {char dummy[2];};
	//There is a generic one using an ellipsis that returns the false_type and a counterpart with more specific arguments to take precedence.
    template <class U> static __two	test( ... );
    template <class U> static char	test( typename __void_t<typename U::iterator_category>::type*   ,
										  typename __void_t<typename U::difference_type>::type*     ,
										  typename __void_t<typename U::value_type>::type*          ,
										  typename __void_t<typename U::reference>::type*           ,
										  typename __void_t<typename U::pointer>::type*	            );
public:
    static const bool value = sizeof(test<T>(0,0,0,0,0)) == 1;
};


template <class T> struct has_iterator_category
{
private:
    struct __two {char __lx; char __lxx;};
    template <class U> static __two	test( ... );
    template <class U> static char	test( typename U::iterator_category* = NULL );
public:
    static const bool value = sizeof(test<T>(nullptr)) == 1;
};






template <class T> class wrap_iter	//NOTE: for vector (random_access_iterator, pointer)
{
public:
/**========================================================================
* '                              typedef
*========================================================================**/
	typedef T															iterator_type;
	typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
    typedef typename iterator_traits<iterator_type>::value_type			value_type;
    typedef typename iterator_traits<iterator_type>::pointer			pointer;
    typedef typename iterator_traits<iterator_type>::reference			reference;
    typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
private:
	iterator_type __i;

public:
/**========================================================================
* @                           Constructors
*========================================================================**/
	wrap_iter(void)					{ __i = NULL; }
	wrap_iter(iterator_type it)		{ __i = it; };
	wrap_iter(const wrap_iter& src)	{ __i = src.__i; };

	~wrap_iter()					{ };

    //TODO: copy ctor
    // template <class _Up> _LIBCPP_INLINE_VISIBILITY _LIBCPP_CONSTEXPR_IF_NODEBUG
    // __wrap_iter(const __wrap_iter<_Up>& __u,
    //     typename enable_if<is_convertible<_Up, iterator_type>::value>::type* = nullptr) _NOEXCEPT
    //     : __i(__u.base())

/**========================================================================
* *                            operators                                        //TODO: CHECK
*========================================================================**/
	reference	operator*() const						{ return *__i; }
    pointer		operator->() const						{ return __i; }     //! //TODO
    wrap_iter&	operator++()							{ ++__i; return *this; }
    wrap_iter	operator++(int)							{ wrap_iter tmp(*this); ++(*this); return tmp; }
    wrap_iter&	operator--()							{ --__i; return *this; }
    wrap_iter	operator--(int)							{ wrap_iter tmp(*this); --(*this); return tmp; }
    wrap_iter&	operator+=(difference_type n)			{  __i += n; return *this; }
    wrap_iter	operator+ (difference_type n) const		{ wrap_iter tmp(*this); tmp += n; return tmp; }
    wrap_iter&	operator-=(difference_type n)			{ *this += -n; return *this; }
    wrap_iter	operator- (difference_type n) const		{ return (*this + (-n)); }
    reference	operator[](difference_type n) const		{ return __i[n]; }
    template <class T1, class T2>
    friend bool operator==(const wrap_iter<T1>& x, const wrap_iter<T2>& y);
    template <class T1, class T2>
    friend bool operator!=(const wrap_iter<T1>& x, const wrap_iter<T2>& y);


    iterator_type base() const  {return __i;}
};

template <class T1, class T2>
bool operator==(const wrap_iter<T1>& x, const wrap_iter<T2>& y) { return (x.base() == y.base()); }
template <class T1, class T2>
bool operator!=(const wrap_iter<T1>& x, const wrap_iter<T2>& y) { return !(x == y); }

//! tmp
template <class T1, class T2>
bool operator<(const wrap_iter<T1>& x, const wrap_iter<T2>& y) { return (x.base() < y.base()); }
template <class T1, class T2>
bool operator>(const wrap_iter<T1>& x, const wrap_iter<T2>& y) { return (x.base() > y.base()); }
template <class _Iter1, class _Iter2>
typename wrap_iter<_Iter1>::difference_type
operator-(const wrap_iter<_Iter1>& __x, const wrap_iter<_Iter2>& __y) _NOEXCEPT
{ return __x.base() - __y.base(); }


template <class T>  T unwrap_iter(T type)                                               { return type; }
template <class T> typename wrap_iter<T>::iterator_type unwrap_iter(wrap_iter<T> it)    { return it.base(); }




//# Requires:    A bidirectional iterator type.
// #             Or a random-access iterator, if an operator that requires such a category of iterators is used.


// template <class _Tp, class = void>
// struct __is_stashing_iterator : false_type {};

// template <class _Tp>
// struct __is_stashing_iterator<_Tp, typename __void_t<typename _Tp::__stashing_iterator_tag>::type>
//   : true_type {};



template <class Iter>
class reverse_iterator
{
public:
/**========================================================================
* '                              typedef
*========================================================================**/
	typedef Iter														iterator_type;
	typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
    typedef typename iterator_traits<iterator_type>::value_type			value_type;
    typedef typename iterator_traits<iterator_type>::pointer			pointer;
    typedef typename iterator_traits<iterator_type>::reference			reference;
    typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
private:
	iterator_type   __i;
public:
    reverse_iterator() : __i() {}
    explicit reverse_iterator(iterator_type __base) : __i(__base) {}
    template <class U>	// copy, type-cast constructor
    reverse_iterator(reverse_iterator<U>& other) : __i(other.base()) {}	//NOTE: why template?

public:
/**========================================================================
* *                            operators										//TODO: CHECK
*========================================================================**/
	reference	        operator*() const						{ Iter tmp(__i); return *(--tmp); }	// ' Internally, the function decreases a copy of its base iterator and returns the result of dereferencing it.
    //! pointer		        operator->() const						{ return (&operator*()); }
    reverse_iterator&	operator++()							{ --__i; return *this; }
    reverse_iterator	operator++(int)							{ reverse_iterator tmp(*this); --__i; return tmp; } // !
    reverse_iterator&	operator--()							{ ++__i; return *this; }
    reverse_iterator	operator--(int)							{ reverse_iterator tmp(*this); ++__i; return tmp; }	// !
    reverse_iterator	operator+ (difference_type n) const		{ return reverse_iterator(__i - n); }
    reverse_iterator&	operator+=(difference_type n)			{ __i -= n; return *this; }
    reverse_iterator	operator- (difference_type n) const		{ return reverse_iterator(__i + n); }
    reverse_iterator&	operator-=(difference_type n)			{ __i += n; return *this; }
    reference	        operator[](difference_type n) const		{ return *(*this + n); }


    iterator_type   base(void) const { return this->__i; }
};

template <class _Iter1, class _Iter2>
bool
operator!=(const reverse_iterator<_Iter1>& __x, const reverse_iterator<_Iter2>& __y)
{
    return __x.base() != __y.base();
}
template <class _InputIter>
typename iterator_traits<_InputIter>::difference_type
distance(_InputIter __first, _InputIter __last)                 //NOTE: add randIter?
{
    typename iterator_traits<_InputIter>::difference_type __r(0);
    for (; __first != __last; ++__first)
        ++__r;
    return __r;
}


template <class _InputIter>
void __advance(_InputIter& __i,
             typename iterator_traits<_InputIter>::difference_type __n)//, input_iterator_tag)
{
    for (; __n > 0; --__n)
        ++__i;
}

// template <class _BiDirIter>
// void __advance(_BiDirIter& __i,
//              typename iterator_traits<_BiDirIter>::difference_type __n, bidirectional_iterator_tag)
// {
//     if (__n >= 0)
//         for (; __n > 0; --__n)
//             ++__i;
//     else
//         for (; __n < 0; ++__n)
//             --__i;
// }

// template <class _RandIter>
// void __advance(_RandIter& __i,
//              typename iterator_traits<_RandIter>::difference_type __n, random_access_iterator_tag)
// {
//    __i += __n;
// }




}



#endif


// In C++, this form is allowed even though the arguments passed to such function are not accessible,
// and is commonly used as the fallback overload in SFINAE,
// exploiting the lowest priority of the ellipsis conversion in overload resolution.
// This syntax for variadic arguments was introduced in 1987 C++ without the comma before the ellipsis.
