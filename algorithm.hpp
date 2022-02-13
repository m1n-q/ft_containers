/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:55:15 by mishin            #+#    #+#             */
/*   Updated: 2022/02/04 16:37:19 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft
{
	// equality (1)
	template <class InputIterator1, class InputIterator2>
  	bool equal (InputIterator1 first1, InputIterator1 last1,
	  			InputIterator2 first2)
	{
		while (first1!=last1)
		{
			if (*first1 != *first2)
				return false;
			++first1; ++first2;
		}
		return true;
	}

	// predicate (2)
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1!=last1)
		{
			if (!pred(*first1, *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}	// bool pred (double i, double j) { return (roundf(i)==roundf(j)); }



	// Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
	// default (1)
	template <class InputIterator1, class InputIterator2>
	bool
	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
							InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if		(first2 == last2)	return false;	// iter1 is longer than iter2
			else if	(*first2 < *first1)	return false;
			else if	(*first1 < *first2)	return true;
			++first1; ++first2;
		}
		return (first2 != last2);						// iter1 is shorter than iter2
	}

    // custom (2)
	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								  InputIterator2 first2, InputIterator2 last2,
								  Compare comp)
	{
		while (first1 != last1)
		{
			if		(first2 == last2)			return false;	// iter1 is longer than iter2
			else if	(!comp(*first1, *first2))	return false;
			else if	(comp(*first1, *first2))	return true;
			++first1; ++first2;
		}
		return (first2 != last2);						// iter1 is shorter than iter2
	}	// bool mycomp (char c1, char c2)	{ return std::tolower(c1)<std::tolower(c2); }
}
#endif
