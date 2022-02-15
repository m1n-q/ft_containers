/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:37:00 by mishin            #+#    #+#             */
/*   Updated: 2022/02/15 12:40:58 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"
# include <cstddef>
# include <stack>


namespace ft
{

template <class T, class Container = vector<T> >
class stack
{
public:
	typedef Container                                container_type;
    typedef typename container_type::value_type      value_type;
    typedef typename container_type::size_type       size_type;


};

}

#endif
