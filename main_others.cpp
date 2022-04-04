/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_others.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:47:08 by mishin            #+#    #+#             */
/*   Updated: 2022/04/05 03:00:47 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algorithm.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "iterator.hpp"
#include "pair.hpp"
#include "utils.hpp"


/**------------------------------------------------------------------------
 * #                            CHECK
 * @ iterators_traits
 * @ reverse_iterator //! derived from class iterator
 * @ enable_if
 * @ is_integral
 * @ equal and/or lexicographical_compare
 * @ std::pair
 * @ std::make_pair
 *------------------------------------------------------------------------**/
// reverse_iterator::base example
#include <iostream>     // std::cout
#include <iterator>     // std::reverse_iterator
#include <vector>       // std::vector
#include <map>       // std::vector
#include "map.hpp"       // std::vector
#include "vector.hpp"       // std::vector
#include "printer.hpp"       // std::vector

int main () {

  std::map<int, int> m;
  std::map<int, int> m2;

  m.insert(std::make_pair(1, 2));

  print_map(m);
  print_map(m2);
  std::cout << (m.begin() == m.end()) << std::endl;
  std::cout << (m2.begin() == m2.end()) << std::endl;

  m.swap(m2);

  print_map(m);
  print_map(m2);
  std::cout << (m.begin() == m.end()) << std::endl;
  std::cout << (m2.begin() == m2.end()) << std::endl;
  m2.erase(m2.begin());
  print_map(m);
  print_map(m2);

  std::cout << (m == m2) << std::endl;

}
