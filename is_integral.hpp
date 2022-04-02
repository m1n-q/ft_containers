/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:19:32 by mishin            #+#    #+#             */
/*   Updated: 2022/04/02 22:37:09 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

#include <stddef.h>
namespace ft
{
template <class T> struct remove_const					{typedef T type;};
template <class T> struct remove_const<const T>			{typedef T type;};

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


template <int> struct sfinaer { };
template <class From, class To> struct is_convertible
{
private:
	static From		getFromType() {From tmp; return tmp;};
	template <class T>
	static int		test(...);
	template <class T>
	static char		test(sfinaer<sizeof(static_cast<T>(getFromType()))>* = NULL);

public:
	const static bool value = (sizeof(test<To>(0)) == 1);
};
}

#endif

// ' immediate context, (즉 템플릿 | 함수의 선언부)에 유효하지 않은 (type | expression)이 필요.
// @ type conversion, static_cast<To>(From) 과 같은 expression 을 테스트할 필요가 있음.
// @ 혹은 implicit conversion

// * 1. type method			->	가능한가;?
// * 2. expression method	-> 	1) decltype(expression, return type)	... c++11
// * 							2) sizeof()...

//쉼표로 구분된 표현식 목록이며 유형은 목록의 마지막 표현식 유형과 동일합니다. 일반적으로 첫 번째 표현식이 유효한지(컴파일 가능, SFINAE 생각) 확인하는 데 사용되며, 두 번째는 decltype첫 번째 표현식이 유효한 경우 반환해야 함을 지정하는 데 사용됩니다.

