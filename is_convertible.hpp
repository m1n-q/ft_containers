/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_convertible.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 02:14:57 by mishin            #+#    #+#             */
/*   Updated: 2022/04/05 02:16:02 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_CONVERTIBLE_HPP
# define IS_CONVERTIBLE_HPP
# include <stddef.h>

namespace ft
{

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
