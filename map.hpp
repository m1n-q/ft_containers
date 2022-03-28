/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:32:48 by mishin            #+#    #+#             */
/*   Updated: 2022/03/28 12:10:17 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <map>
# include "pair.hpp"
# include "iterator.hpp"
# include "tree.hpp"
# include "tree_iter.hpp"
# include "algorithm.hpp"

/**------------------------------------------------------------------------
 * 								//TODO
 * ! impl max_size()
 *  checking CopyConstructible / DefaultConstructible ?
 *
 * ! map_iter operators
 * !!!!!!! check complexity, perfomance
 *------------------------------------------------------------------------**/


namespace ft
{


template <class _Key, class _ValueTp, class _Compare>
class compare_kv		//wraper: allow to compare not only (value, value), but { (key, value) || (value, key) }
{
    _Compare comp;

public:
    compare_kv()
        // (is_nothrow_default_constructible<_Compare>::value)
        : comp() {}
    compare_kv(_Compare comp)		//NOT USED?
        // (is_nothrow_copy_constructible<_Compare>::value)
        : comp(comp) {}
	compare_kv(const compare_kv& x)
        // (is_nothrow_copy_constructible<_Compare>::value)
        : comp(x.comp) {}

	~compare_kv() {}

	compare_kv&	operator=(const compare_kv& x)
	{
		if (this == &x)		return *this;

		this->comp = x.comp;

		return *this;
	}

    const _Compare& key_comp() const { return comp; }

    bool operator()(const _ValueTp& x, const _ValueTp& y) const
        {return comp(x.first, y.first);}
    bool operator()(const _ValueTp& x, const _Key& y) const
        {return comp(x.first, y);}
    bool operator()(const _Key& x, const _ValueTp& y) const
        {return comp(x, y.first);}
};

template < class Key,												// key_type
           class T,													// mapped_type
           class Compare	= std::less<Key>,						// key_compare
           class Alloc		= std::allocator<pair<const Key,T> >	// allocator_type
           >
class map
{
/**========================================================================
* '                              typedefs
*========================================================================**/

public:
	typedef Key														key_type;
	typedef T														mapped_type;
	typedef pair<const key_type, mapped_type>						value_type;
	typedef Compare													key_compare;
	typedef Alloc													allocator_type;
	typedef typename allocator_type::reference						reference;
	typedef typename allocator_type::const_reference				const_reference;
	typedef typename allocator_type::pointer						pointer;
	typedef typename allocator_type::const_pointer					const_pointer;
	typedef typename allocator_type::difference_type				difference_type;
	typedef typename allocator_type::size_type						size_type;

	class value_compare
        : public std::binary_function<value_type, value_type, bool>
    {
		// ! Of course, for the implementation of map::value_compare, the keyword friend is allowed.
        friend class map;	// why friends?
    protected:
        key_compare		comp;

        value_compare(key_compare c): comp(c) {}
    public:
        bool operator()(const value_type& x, const value_type& y) const
			{ return comp(x.first, y.first); }

    };

private:
	typedef Node_kv<key_type, mapped_type>					node_type;
	typedef compare_kv<key_type, value_type, key_compare>	__value_compare;
	typedef AVL<node_type,
				__value_compare,
				allocator_type > 							base;

	base tree;

public:
	typedef wrapper<typename base::iterator>						iterator;
	typedef const_wrapper<typename base::const_iterator>			const_iterator;
	typedef ft::reverse_iterator<iterator>							reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;


/**========================================================================
* @                           Constructors
*========================================================================**/
public:
	explicit
	map (const key_compare&		comp	= key_compare(),
         const allocator_type&	alloc	= allocator_type())
	:tree(__value_compare(comp), alloc)
	{}

	template <class InputIterator>
	map (InputIterator			first,
		 InputIterator			last,
		 const key_compare&		comp 	= key_compare(),
		 const allocator_type&	alloc	= allocator_type())
	:tree(__value_compare(comp), alloc)
	{
		insert(first, last);
	}

	map (const map& src)
	:tree(src.tree) {}

	~map() {}

/**========================================================================
* *                            operators
*========================================================================**/
	mapped_type&	operator[] (const key_type& k)
	{
		return insert(ft::make_pair(k, mapped_type())).first->second;

		// 	insert (key, mapped_type with default constructor);
		//@ key_type must meet the requirements of CopyConstructible.
		//@ mapped_type must meet the requirements of CopyConstructible and DefaultConstructible.
	}

	map&			operator=(const map& src)
	{
		if (this == &src)	return *this;

		this->tree = src.tree;

		return *this;
	}
/**========================================================================
* #                          member functions
*========================================================================**/

	iterator							begin()				{ return tree.begin(); }
	const_iterator						begin() const		{ return tree.begin(); }
	iterator							end()				{ return tree.end(); }
	const_iterator						end() const			{ return tree.end(); }
	reverse_iterator					rbegin()			{ return reverse_iterator(end());}
	const_reverse_iterator				rbegin() const		{ return reverse_iterator(end());}
	reverse_iterator					rend()				{ return reverse_iterator(begin());}
	const_reverse_iterator				rend() const		{ return reverse_iterator(begin());}
	bool								empty() const		{ return (tree.size() == 0); }
	size_type							size() const		{ return tree.size(); }
	size_type							max_size() const	{ return tree.max_size(); }


	pair<iterator,bool>					insert (const value_type& val)
	{ return tree.insert(val); }

	iterator							insert (iterator hint, const value_type& val)
	{ return tree.insert_with_hint(hint, val); }

	template <class InputIterator>
	void								insert (InputIterator first, InputIterator last)
	{
		for (iterator e = end(); first != last; first++)
			insert(e, *first);
	}

	void								erase (iterator position) 					{ tree.remove(position); }
	size_type							erase (const key_type& k) 					{ return tree.remove_key(k); }	// return #erased
	void								erase (iterator first, iterator last)		{ while (first != last) erase(first++); }
	void								swap (map& x)								{ return tree.swap(x.tree); }
	void								clear()										{ return tree.clear(); }

	key_compare							key_comp() const							{ return tree.value_comp().key_comp(); }
	value_compare						value_comp() const							{ return value_compare(tree.value_comp().key_comp()); }

	iterator							find (const key_type& k)					{ return iterator(tree.find_key(k)); }
	const_iterator 						find (const key_type& k) const				{ return const_iterator(tree.find_key(k)); }
	size_type							count (const key_type& k) const				{ if (tree.find_key(k)) return 1; return 0;}

	iterator							lower_bound (const key_type& k)				{ return tree.lower_bound(k); }
	const_iterator						lower_bound (const key_type& k) const		{ return tree.lower_bound(k); }
	iterator							upper_bound (const key_type& k)				{ return tree.upper_bound(k); }
	const_iterator						upper_bound (const key_type& k) const		{ return tree.upper_bound(k); }
	pair<iterator,iterator>            	equal_range (const key_type& k)
	{
		pair<iterator, iterator>	tmp(tree.__lower_bound(k),
										tree.__upper_bound(k));
		return tmp;
	}

	pair<const_iterator, const_iterator>		equal_range(const key_type& k) const
	{
		pair<const_iterator, const_iterator>	tmp(tree.lower_bound(k),
													tree.upper_bound(k));
		return tmp;
	}

	allocator_type						get_allocator() const						{ return tree.get_allocator(); };

};

/**========================================================================
* *                        relational-operators
*========================================================================**/
template <class Key, class T, class Compare, class Alloc>
bool operator== (const map<Key, T, Compare, Alloc>& lhs,
				 const map<Key, T, Compare, Alloc>& rhs)
{
	return	lhs.size() == rhs.size() &&
			equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class Key, class T, class Compare, class Alloc>
bool operator<  (const map<Key, T, Compare, Alloc>& lhs,
				 const map<Key, T, Compare, Alloc>& rhs)
{
	return lexicographical_compare( lhs.begin(), lhs.end(),
									rhs.begin(), rhs.end() );
}

template <class Key, class T, class Compare, class Alloc>
bool operator!= (const map<Key, T, Compare, Alloc>& lhs,
				 const map<Key, T, Compare, Alloc>& rhs)	{ return !(lhs == rhs); }

template <class Key, class T, class Compare, class Alloc>
bool operator>  (const map<Key, T, Compare, Alloc>& lhs,
				 const map<Key, T, Compare, Alloc>& rhs)	{ return rhs < lhs; }

template <class Key, class T, class Compare, class Alloc>
bool operator<= (const map<Key, T, Compare, Alloc>& lhs,
				 const map<Key, T, Compare, Alloc>& rhs)	{ return !(lhs > rhs); }

template <class Key, class T, class Compare, class Alloc>
bool operator>= (const map<Key, T, Compare, Alloc>& lhs,
				 const map<Key, T, Compare, Alloc>& rhs)	{ return !(lhs < rhs); }
/**========================================================================
* #                         non-member functions
*========================================================================**/
template <class Key, class T, class Compare, class Alloc>
void	swap(map<Key, T, Compare, Alloc>& x,
			 map<Key, T, Compare, Alloc>& y)				{ x.swap(y); }

}
#endif
