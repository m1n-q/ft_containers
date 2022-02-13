/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:39:36 by mishin            #+#    #+#             */
/*   Updated: 2022/02/09 17:55:11 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILS_HPP
# define UTILS_HPP

template <class Alloc, class T>
void construct_backward(Alloc& alloc, T* begin, T* end, T* target)
{

	while (end != begin)	// backward from target
	{
		alloc.construct(target, *--end);	//TODO: destroy src //NOTE:remove reference?
		--target;
	}
}

template <class Alloc, class T>
void construct_forward(Alloc& alloc, T* begin, T* end, T* target)
{
	while (begin != end)	// forward to target
	{
		alloc.construct(target, *begin++);	//TODO: destroy src //NOTE:remove reference?
		target++;
	}
}

template <class Alloc, class T>
void destruct_backward(Alloc& alloc, T* begin, T* end)
{
	while (end != begin)
		alloc.destroy(--end);
}
#endif
