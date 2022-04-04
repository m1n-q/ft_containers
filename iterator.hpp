/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:57:52 by mishin            #+#    #+#             */
/*   Updated: 2022/04/05 02:40:30 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>
#include <memory>

#include "is_integral.hpp"
#include "is_convertible.hpp"
#include "enable_if.hpp"
#include "reverse_iterator.hpp"

 /**----------------------------------------------------------------------------
 *
 * @    template <class Iter>
 * @    struct iterator_traits
 * @    {
 * @        typedef typename Iter::difference_type      difference_type;
 * @        typedef typename Iter::value_type		    value_type;
 * @        typedef typename Iter::pointer			    pointer;
 * @        typedef typename Iter::reference		    reference;
 * @        typedef typename Iter::iterator_category    iterator_category;
 * @    };

 * @    template<
 * @               class Category,
 * @               class T,
 * @               class Distance = ptrdiff_t,
 * @               class Pointer = T*,
 * @               class Reference = T&
 * @           >
 * @    struct iterator
 * @    {
 * @        typedef T         value_type;
 * @        typedef Distance  difference_type;
 * @        typedef Pointer   pointer;
 * @        typedef Reference reference;
 * @        typedef Category  iterator_category;
 * @    };
 *
 * ---------------------------------------------------------------------------*/
namespace ft
{

struct input_iterator_tag												{};
struct output_iterator_tag												{};
struct forward_iterator_tag			: public input_iterator_tag         {};
struct bidirectional_iterator_tag	: public forward_iterator_tag       {}; //NOTE: compatible with std? (ex. vector(std::cont.begin(), std::cont.end()))
struct random_access_iterator_tag	: public bidirectional_iterator_tag {};


template <
            class Category,
            class T,
            class Distance = ptrdiff_t,
            class Pointer = T*,
            class Reference = T&
        >
struct iterator
{
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};

template <class T>
struct __void_t { typedef void type; };

template <class T>
struct has_iterator_typedefs
{
private:
    struct __two {char du; char mmy;};
    template <class U> static __two	test( ... );
    template <class U> static char	test( typename __void_t<typename U::iterator_category>::type*,
                                          typename __void_t<typename U::difference_type>::type*  ,
                                          typename __void_t<typename U::value_type>::type*       ,
                                          typename __void_t<typename U::reference>::type*        ,   // * __void_t : cannot point ref
                                          typename __void_t<typename U::pointer>::type*	        );
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


template <class InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last, input_iterator_tag)
{
    typename iterator_traits<InputIterator>::difference_type    ret(0);
    for (; first != last; ++first)
        ++ret;
    return ret;
}

template <class RandomIterator>
typename iterator_traits<RandomIterator>::difference_type
distance(RandomIterator first, RandomIterator last, random_access_iterator_tag)
{
    return last - first;
}

template <class Iterator>
typename iterator_traits<Iterator>::difference_type
distance(Iterator first, Iterator last)
{
    return distance(first, last, typename iterator_traits<Iterator>::iterator_category());
}


template <class T, class U, bool = has_iterator_category<iterator_traits<T> >::value>
struct has_iterator_category_convertible_to
: is_convertible<typename iterator_traits<T>::iterator_category, U> {};

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
