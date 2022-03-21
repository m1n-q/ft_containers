/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:50:52 by mishin            #+#    #+#             */
/*   Updated: 2022/03/21 21:15:31 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTER_HPP
# define PRINTER_HPP
# include <iostream>

void	print_header(int input)
{
	input ? system(" artii \"FT\" | lolcat -F 0.25") : system(" artii \"STD\" | lolcat -F 0.25");
}

template <class Container>
void	print_vector(const Container& myvector )
{
	typename Container::const_iterator	it;

	std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
	for (it = myvector.begin(); it != myvector.end(); it++)
		std::cout << "[" << *it << "] ";
	std::cout << std::endl;

	std::cout << "SIZE	=> " << myvector.size() << std::endl;
	std::cout << "CAP	=> " << myvector.capacity() << std::endl;

	std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl << std::endl;
}

#endif
