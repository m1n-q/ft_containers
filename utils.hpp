/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:39:36 by mishin            #+#    #+#             */
/*   Updated: 2022/04/05 03:10:53 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILS_HPP
# define UTILS_HPP

template <class Alloc, class T>
void construct_backward(Alloc& alloc, T* first, T* last, T* target)
{

	while (last != first)	// backward from target
	{
		alloc.construct(target, *--last);
		--target;
	}
}

template <class Alloc, class T>
void construct_forward(Alloc& alloc, T* first, T* last, T* target)
{
	while (first != last)	// forward from target
	{
		alloc.construct(target, *first++);
		target++;
	}
}

template <class Alloc, class T>
void destruct_backward(Alloc& alloc, T* first, T* last)
{
	while (last != first)
		alloc.destroy(--last);
}

template <class T>
T max(T a, T b)
{
	if (a < b)
		return b;
	return a;
}

template <class T>
T min(T a, T b)
{
	if (a < b)
		return a;
	return b;
}

template <class U>
void	__swap(U& u1, U& u2)
{
	U tmp = u1;

	u1 = u2;
	u2 = tmp;
}
#endif
