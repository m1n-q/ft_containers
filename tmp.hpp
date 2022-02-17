/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:33:40 by mishin            #+#    #+#             */
/*   Updated: 2022/02/17 22:15:26 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cmath>
namespace ft
{
template <class T>
class Node;

template <class T>
class buf
{
public:
	Node<T>*** _buf;

	buf() : _buf(new Node<T>**[10]()) {}

	void	append(int depth, Node<T>* n)
	{
		if (_buf[depth])
		{
			int i = -1;
			while (_buf[depth][++i]);
			_buf[depth][i] = n;
		}
	}

	void	print()
	{
		int i = -1;
		int j = -1;
		while (++i < 10)
		{
			j = -1;
			while (++j < (int)pow(2,i))
			{
				if (!(_buf[i]) || !(_buf[i][j]))
					continue ;
				std::cout<<_buf[i][j] << " ";
			}
			std::cout <<std:: endl;
		}
	}
};
}
