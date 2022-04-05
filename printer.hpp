/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 20:50:52 by mishin            #+#    #+#             */
/*   Updated: 2022/04/05 18:16:21 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTER_HPP
# define PRINTER_HPP

# include <iostream>
# include <chrono>

# define RED(s) 				"\033[1;31m"s"\033[0m"
# define BLUE(s) 				"\033[1;34m"s"\033[0m"
# define GRAY(s) 				"\033[0;37m"s"\033[0m"
# define CYAN(s) 				"\033[1;36m"s"\033[0m"
# define GREEN(s)				"\033[0;32m"s"\033[0m"
# define YELLOW(s)				"\033[0;33m"s"\033[0m"
# define PURPLE(s)				"\033[0;35m"s"\033[0m"
// # define NC(s)					"\033[0m"
# define UL(s)					"\033[4m"
# define START					std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
# define END					std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();std::cout<< "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
# define PRINT(x)				std::cout<< x << std::endl;
# define SHOW(...)				std::cout << std::setw(29) << #__VA_ARGS__ << " == " << __VA_ARGS__ << '\n'

void	print_header(int input)
{
	input ? system(" artii \"FT\" | lolcat -F 0.25") : system(" artii \"STD\" | lolcat -F 0.25");
}


void	print_cheader(std::string s)
{
	system((std::string("artii ") + s + " | lolcat -F 0.25").c_str());
}

template <class Vec>
void	print_vector(const Vec& v )
{
	typename Vec::const_iterator	it;

	std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
	for (it = v.begin(); it != v.end(); it++)
		std::cout << "[" << *it << "] ";
	std::cout << std::endl;

	std::cout << "CAP	=> " << v.capacity() << std::endl;
	std::cout << "SIZE	=> " << v.size() << std::endl;

	std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl << std::endl;
}

template <class Map>
void	print_map(const Map& m )
{
	typename Map::const_iterator	it;

	std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
	for (it = m.begin(); it != m.end(); it++)
		std::cout << "[" << it->first << ", " << it->second << "] ";
	std::cout << std::endl;

	std::cout << "SIZE	=> " << m.size() << std::endl;

	std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl << std::endl;
}

#endif
