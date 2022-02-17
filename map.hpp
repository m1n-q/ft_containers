/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:32:48 by mishin            #+#    #+#             */
/*   Updated: 2022/02/15 16:12:40 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <map>
# include "pair.hpp"
# include "iterator.hpp"

namespace ft
{
template < class Key,												// map::key_type
           class T,													// map::mapped_type
           class Compare	= std::less<Key>,						// map::key_compare
           class Alloc		= std::allocator<pair<const Key,T> >	// map::allocator_type
           >
class map
{
public:
/**========================================================================
* '                              typedefs
*========================================================================**/
	typedef Key												key_type;
	typedef T												mapped_type;
	typedef pair<key_type, mapped_type>						value_type;
	typedef Compare											key_compare;
	typedef Alloc											allocator_type;
	typedef typename allocator_type::reference				reference;
	typedef typename allocator_type::const_reference		const_reference;
	typedef typename allocator_type::pointer				pointer;
	typedef typename allocator_type::const_pointer			const_pointer;
	typedef typename allocator_type::difference_type		difference_type;
	typedef typename allocator_type::size_type				size_type;
	typedef pointer											iterator;
	typedef const_pointer									const_iterator;
	typedef ft::reverse_iterator<iterator>					reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

	class value_compare
        : public std::binary_function<value_type, value_type, bool>
    {
        friend class map;
    protected:
        key_compare comp;

        value_compare(key_compare c);
    public:
        bool operator()(const value_type& x, const value_type& y) const;
    };


/**========================================================================
* @                           Constructors
*========================================================================**/

	explicit map (const key_compare& comp = key_compare(),
              const allocator_type& alloc = allocator_type());
	template <class InputIterator>
			 map ( InputIterator first, InputIterator last,
			       const key_compare& comp = key_compare(),
			       const allocator_type& alloc = allocator_type());
			 map (const map& x);

/**========================================================================
* *                            operators
*========================================================================**/
mapped_type& operator[] (const key_type& k);
/**========================================================================
* #                          member functions
*========================================================================**/

iterator							begin();
const_iterator						begin() const;
iterator							end();
const_iterator						end() const;
reverse_iterator					rbegin();
const_reverse_iterator				rbegin() const;
reverse_iterator					rend();
const_reverse_iterator				rend() const;
bool								empty() const;
size_type							size() const;
size_type							max_size() const;




pair<iterator,bool>					insert (const value_type& val);
iterator							insert (iterator position, const value_type& val);
template <class InputIterator>
void								insert (InputIterator first, InputIterator last);

void								erase (iterator position);
size_type							erase (const key_type& k);
void								erase (iterator first, iterator last);
void								swap (map& x);
void								clear();

key_compare							key_comp() const;
value_compare						value_comp() const;

iterator							find (const key_type& k);
const_iterator 						find (const key_type& k) const;
size_type							count (const key_type& k) const;

iterator							lower_bound (const key_type& k);
const_iterator						lower_bound (const key_type& k) const;
iterator							upper_bound (const key_type& k);
const_iterator						upper_bound (const key_type& k) const;
pair<const_iterator,const_iterator>	equal_range (const key_type& k) const;
pair<iterator,iterator>            	equal_range (const key_type& k);
allocator_type						get_allocator() const;

};

}
#endif
