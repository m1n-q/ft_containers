/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:50:52 by mishin            #+#    #+#             */
/*   Updated: 2022/03/27 22:44:42 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTER_HPP
# define PRINTER_HPP
# include <iostream>
#include <chrono>
# define START	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
# define END	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();std::cout<< "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

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
