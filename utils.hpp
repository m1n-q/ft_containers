/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:39:36 by mishin            #+#    #+#             */
/*   Updated: 2022/03/21 21:43:15 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILS_HPP
# define UTILS_HPP

template <class Alloc, class T>
void construct_backward(Alloc& alloc, T* first, T* last, T* target)
{

	while (last != first)	// backward from target
	{
		alloc.construct(target, *--last);	//TODO: destroy src //NOTE:remove reference?
		--target;
	}
}

template <class Alloc, class T>
void construct_forward(Alloc& alloc, T* first, T* last, T* target)
{
	while (first != last)	// forward to target
	{
		alloc.construct(target, *first++);	//TODO: destroy src //NOTE:remove reference?
		target++;
	}
}

template <class Alloc, class T>
void destruct_backward(Alloc& alloc, T* first, T* last)
{
	while (last != first)
		alloc.destroy(--last);
}

template <class InputIterator>
bool equal(InputIterator first1, InputIterator last1, InputIterator first2)
{
	for (; first1 != last1; ++first1, (void) ++first2)
        if (*first1 != *first2)
            return false;
    return true;
}

template <class T>
T max(T a, T b)
{
	if (a < b)
		return b;
	return a;
}

template <class U>
void	__swap(U& u1, U& u2)
{
	U tmp = u1;

	u1 = u2;
	u2 = tmp;
}
#endif
