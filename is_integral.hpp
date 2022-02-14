/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:19:32 by mishin            #+#    #+#             */
/*   Updated: 2022/02/14 17:30:51 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace ft
{
template <class T> struct remove_const			{typedef T type;};
template <class T> struct remove_const<const T>	{typedef T type;};

template <class T> struct remove_volatile				{typedef T type;};
template <class T> struct remove_volatile<volatile T>	{typedef T type;};

template <class T> struct remove_cv
{typedef typename remove_volatile<typename remove_const<T>::type>::type type;};


template <class T, T v> struct __base_type
{
	typedef T				value_type;
	static const value_type	value = v;
};

typedef	__base_type<bool, true>		true_type;
typedef	__base_type<bool, false>	false_type;

template <class T>	struct is_integral_base						: false_type {};
template <>			struct is_integral_base<bool>				: true_type {};
template <> 		struct is_integral_base<char>				: true_type {};
template <> 		struct is_integral_base<signed char>		: true_type {};
template <> 		struct is_integral_base<unsigned char>		: true_type {};
template <> 		struct is_integral_base<wchar_t>			: true_type {};
#if _LIBCPP_STD_VER >= 11
template <> 		struct is_integral_base<char16_t>			: true_type {};
template <> 		struct is_integral_base<char32_t>			: true_type {};
#endif
template <> 		struct is_integral_base<short>				: true_type {};
template <> 		struct is_integral_base<unsigned short>		: true_type {};
template <> 		struct is_integral_base<int>				: true_type {};
template <> 		struct is_integral_base<unsigned int>		: true_type {};
template <> 		struct is_integral_base<long>				: true_type {};
template <> 		struct is_integral_base<unsigned long>		: true_type {};
template <> 		struct is_integral_base<long long>			: true_type {};	//'
template <> 		struct is_integral_base<unsigned long long>	: true_type {};	//'


template <class T>	struct is_integral
: is_integral_base<typename remove_cv<T>::type> {};

template <class T> struct is_pointer		: public false_type	{};
template <class T> struct is_pointer<T*>	: public true_type	{};
}

#endif
