/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_others.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 21:47:08 by mishin            #+#    #+#             */
/*   Updated: 2022/04/02 23:40:04 by mishin           ###   ########.fr       */
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
 * ' iterators_traits
 * @ reverse_iterator
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
#include "vector.hpp"       // std::vector

int main () {
  ft::vector<int> myvector;
  for (int i=0; i<10; i++) myvector.push_back(i);

  typedef ft::vector<int>::iterator iter_type;

  ft::reverse_iterator<iter_type> rev_end (myvector.begin());
  ft::reverse_iterator<iter_type> rev_begin (myvector.end());

  std::cout << "myvector:";
  for (iter_type it = rev_end.base(); it != rev_begin.base(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
