/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:57:52 by mishin            #+#    #+#             */
/*   Updated: 2022/03/28 15:54:29 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>
#include <memory>

#include "is_integral.hpp"
#include "enable_if.hpp"
#include "reverse_iterator.hpp"

/**----------------------------------------------------------------------------
 * # => iterator_traits 어떤 구현으로 할지 고민중..
 * # => is_input_iterator 등을 구현하는데에,
 * # => iterator_traits<Iter> 는 사실 기본형이어도 괜찮긴함..
 * # =>	cppreference 보면 no-members가 되도록 구현하는게 맞긴한듯 ㅎㅎ OK
 *
 * @ wrap_iter check done!
 *----------------------------------------------------------------------------*/

 /**----------------------------------------------------------------------------
 *
 * @  template <class Iter>
 * @  struct iterator_traits
 * @  {
 * @      typedef typename Iter::difference_type	difference_type;
 * @      typedef typename Iter::value_type			value_type;
 * @      typedef typename Iter::pointer			pointer;
 * @      typedef typename Iter::reference			reference;
 * @      typedef typename Iter::iterator_category	iterator_category;
 * @  };
 *
 * ---------------------------------------------------------------------------*/
namespace ft
{
	struct input_iterator_tag												{};
	struct output_iterator_tag												{};
	struct forward_iterator_tag			: public input_iterator_tag         {};
	struct bidirectional_iterator_tag	: public forward_iterator_tag       {}; //NOTE: compatible with std? (ex. vector(std::cont.begin(), std::cont.end()))
	struct random_access_iterator_tag	: public bidirectional_iterator_tag {};

	template <class T>
	struct __void_t { typedef void type; };

	template <class T>
	struct has_iterator_typedefs
	{
	private:
	    struct __two {char du; char mmy;};
	    template <class U> static __two	test( ... );
	    template <class U> static char	test( typename __void_t<typename U::iterator_category>::type*   ,
											  typename __void_t<typename U::difference_type>::type*     ,
											  typename __void_t<typename U::value_type>::type*          ,
											  typename __void_t<typename U::reference>::type*           ,   // * cannot point ref
											  typename __void_t<typename U::pointer>::type*	            );
	public:
	    static const bool value = sizeof(test<T>(0,0,0,0,0)) == 1;
	};

template <class T>
struct has_iterator_category
{
private:
    struct __two {char du; char mmy;};
    template <class U> static __two __test(...);
    template <class U> static char  __test(typename U::iterator_category*);
public:
    static const bool value = sizeof(__test<T>(0)) == 1;
};


// ! fallbacks
template <class Iter, bool> struct iterator_traits_convertible_checker {};
template <class Iter, bool> struct iterator_traits_typedefs_checker    {};

// @ impl
template <class Iter>       struct iterator_traits_convertible_checker<Iter, true>
{
    typedef typename Iter::difference_type		difference_type;
    typedef typename Iter::value_type			value_type;
    typedef typename Iter::pointer				pointer;
    typedef typename Iter::reference			reference;
    typedef typename Iter::iterator_category	iterator_category;
};

// ' check
template <class Iter>
struct iterator_traits_typedefs_checker<Iter, true>
: iterator_traits_convertible_checker
    <
        Iter,
        is_convertible<typename Iter::iterator_category, input_iterator_tag>::value ||
        is_convertible<typename Iter::iterator_category, output_iterator_tag>::value
    >
{};

template <class Iter>
struct  iterator_traits
: iterator_traits_typedefs_checker
    <
        Iter,
        has_iterator_typedefs<Iter>::value  // check for "typename Iter::"
    >
{};

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










template <class InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance(InputIterator __first, InputIterator __last, input_iterator_tag)                 //NOTE: add randIter?
{
    typename iterator_traits<InputIterator>::difference_type __r(0);
    for (; __first != __last; ++__first)
        ++__r;
    return __r;
}

template <class RandomIterator>
typename iterator_traits<RandomIterator>::difference_type
distance(RandomIterator __first, RandomIterator __last, random_access_iterator_tag)                 //NOTE: add randIter?
{
    return __last-__first;
}

template <class Iterator>
typename iterator_traits<Iterator>::difference_type
distance(Iterator __first, Iterator __last)
{
    return distance(__first, __last, typename iterator_traits<Iterator>::iterator_category());
}

template <class InputIterator>
void __advance(InputIterator& __i,
             typename iterator_traits<InputIterator>::difference_type __n)//, input_iterator_tag)
{
    for (; __n > 0; --__n)
        ++__i;
}



template <class T, class U, bool = has_iterator_category<iterator_traits<T> >::value> // 여기서 has_iterator_category 검사를 해주면 , iterator_traits<Iter> 에서 has_typdefs 해줘야하남..
struct has_iterator_category_convertible_to
: is_convertible<typename iterator_traits<T>::iterator_category, U>
{};

template <class T, class U>
struct has_iterator_category_convertible_to<T, U, false> : false_type {};

template <class T>
struct is_input_iterator
: public has_iterator_category_convertible_to<T, input_iterator_tag> {};

template <class T>
struct is_forward_iterator
: public has_iterator_category_convertible_to<T, forward_iterator_tag> {};

template <class T>
struct is_bidirectional_iterator
: public has_iterator_category_convertible_to<T, bidirectional_iterator_tag> {};

template <class T>
struct is_random_access_iterator
: public has_iterator_category_convertible_to<T, random_access_iterator_tag> {};


template <class T>  T unwrap_iter(T type)											{ return type; }
template <class T>	typename wrap_iter<T>::base_type unwrap_iter(wrap_iter<T> it)	{ return it.base(); }
}



#endif


// In C++, this form is allowed even though the arguments passed to such function are not accessible,
// and is commonly used as the fallback overload in SFINAE,
// exploiting the lowest priority of the ellipsis conversion in overload resolution.
// This syntax for variadic arguments was introduced in 1987 C++ without the comma before the ellipsis.


// * 부모 <- 자식 방향으로만 대입이 가능합니다. 자식은 부모의 정보를 모두 갖고 있지만, 반대는 아니니까.
// ft::output_iterator_tag o;
// ft::input_iterator_tag i;
// ft::forward_iterator_tag f;
// (void)static_cast<ft::input_iterator_tag>(f);
// (void)static_cast<ft::forward_iterator_tag>(i);
