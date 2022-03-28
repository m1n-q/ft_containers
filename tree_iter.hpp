/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iter.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 14:11:24 by mishin            #+#    #+#             */
/*   Updated: 2022/03/28 17:46:23 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITER_HPP
# define MAP_ITER_HPP

# include "iterator.hpp"
# include "pair.hpp"


/**------------------------------------------------------------------------
 * 								//TODO
 * ' friend?
 * ' check operators
 *------------------------------------------------------------------------**/

namespace ft
{
template <class _Key, class _Value>   class Node_kv;

template <class _Node, class _DiffType>
class tree_iterator
{
private:

    typedef _Node                                       node_type;
    typedef node_type*                                  NodePtr;
    typedef typename node_type::container_value_type   	container_value_type;   // pair<const key_type, mapped_type>

public:
    NodePtr    ptr;

    typedef bidirectional_iterator_tag					iterator_category;
    typedef container_value_type                        value_type;
    typedef _DiffType									difference_type;
    typedef value_type&									reference;
    typedef value_type*					            	pointer;


	tree_iterator()                         : ptr(NULL)     {}
	tree_iterator(NodePtr nodePtr)          : ptr(nodePtr)  {}
	tree_iterator(const tree_iterator& i)   : ptr(i.ptr)    {}

    ~tree_iterator() {}

    tree_iterator&	operator=(const tree_iterator& i)
	{
		if (this == &i)		return *this;

		this->ptr = i.ptr;

		return *this;
	}

	// reference		operator*() const		{ return ptr->val; }
	// pointer			operator->() const		{ return &(ptr->val); }

    // tree_iterator&	operator++()  			{ ptr = _next(ptr); return *this; }
    // tree_iterator	operator++(int)			{ tree_iterator t(*this); ++(*this); return t;}

    // tree_iterator&	operator--()			{ ptr = _prev(ptr); return *this; }
    // tree_iterator	operator--(int)			{ tree_iterator t(*this); --(*this); return t;}
};

template <class _Node, class _DiffType>
class tree_const_iterator
{
private:

    typedef _Node                                       node_type;
    typedef node_type*                                  NodePtr;
    typedef typename node_type::container_value_type	container_value_type;   // pair<const key_type, mapped_type>

public:
    NodePtr    ptr;

    typedef bidirectional_iterator_tag					iterator_category;
    typedef container_value_type						value_type;
    typedef _DiffType									difference_type;
    typedef const value_type&							reference;
    typedef const value_type*				    		pointer;

    typedef tree_iterator<node_type, difference_type>   non_const_iterator;

public:
	tree_const_iterator()                               : ptr(NULL)     {}
	tree_const_iterator(NodePtr nodePtr)                : ptr(nodePtr)  {}
	tree_const_iterator(const tree_const_iterator& i)   : ptr(i.ptr)    {}
	tree_const_iterator(non_const_iterator i)           : ptr(i.ptr)    {}

    ~tree_const_iterator()  {}


	tree_const_iterator&	operator=(const tree_const_iterator& i)
	{
		if (this == &i)		return *this;

		this->ptr = i.ptr;

		return *this;
	}

	// reference		        operator*() const		{ return ptr->val; }
	// pointer			        operator->() const		{ return &(ptr->val); }

    // tree_const_iterator&	operator++()    		{ ptr = _next(ptr); return *this; }
    // tree_const_iterator	    operator++(int)			{ tree_const_iterator t(*this); ++(*this); return t;}

    // tree_const_iterator&	operator--()	    	{ ptr = _prev(ptr); return *this; }
    // tree_const_iterator	    operator--(int)			{ tree_const_iterator t(*this); --(*this); return t;}
};





template <class TreeIterator>
class wrapper : public TreeIterator
{
private:
	typedef TreeIterator	Base;
	using Base::ptr;		//NodePtr


public:
	typedef typename Base::iterator_category	iterator_category;
	typedef typename Base::value_type			value_type;
	typedef typename Base::difference_type		difference_type;
	typedef typename Base::reference			reference;
	typedef typename Base::pointer				pointer;


	wrapper()							: Base() 		{}
	wrapper(Base i)						: Base(i)		{}	//@ can take NodePtr as param here.
	wrapper(const wrapper& w)			: Base(w.ptr)	{}

	~wrapper() {}

	wrapper& operator=(const wrapper& w)
	{
		if (this != &w)
			Base::operator=(w);
		return *this;
	}


	reference		        operator*() const		{ return ptr->val; }
	pointer			        operator->() const		{ return &(ptr->val); }

    wrapper&				operator++()    		{ ptr = _next(ptr); return *this; }
    wrapper	    			operator++(int)			{ wrapper t(*this); ++(*this); return t;}

    wrapper&				operator--()	    	{ ptr = _prev(ptr); return *this; }
    wrapper	    			operator--(int)			{ wrapper t(*this); --(*this); return t;}

    friend bool				operator==( const wrapper& x,
										const wrapper& y)  {return x.ptr == y.ptr;}

	friend bool				operator!=( const wrapper& x,
										const wrapper& y)  {return !(x == y);}

};


template <class TreeConstIterator>
class const_wrapper : public TreeConstIterator
{
private:
	typedef TreeConstIterator	Base;
	using Base::ptr;					//NodePtr
	using typename Base::non_const_iterator;


public:
	typedef typename Base::iterator_category	iterator_category;
	typedef typename Base::value_type			value_type;
	typedef typename Base::difference_type		difference_type;
	typedef typename Base::reference			reference;
	typedef typename Base::pointer				pointer;


	const_wrapper()									: Base()	  {}
	const_wrapper(Base i)							: Base(i) 	  {}
	const_wrapper(const const_wrapper& w)			: Base(w.ptr) {}

	// conversion from iter to const_iter
	// opposite is not viable
	const_wrapper(wrapper<non_const_iterator> w)	: Base(static_cast<non_const_iterator>(w).ptr) {}		// w.ptr is private...! w::Base::ptr was pubilc
														   //* or C style cast?
	~const_wrapper() {}

	const_wrapper& operator=(const const_wrapper& w)
	{
		if (this != &w)
			Base::operator=(w);
		return *this;
	}

	reference		        operator*() const		{ return ptr->val; }
	pointer			        operator->() const		{ return &(ptr->val); }

    const_wrapper&			operator++()    		{ ptr = _next(ptr); return *this; }
    const_wrapper	    	operator++(int)			{ const_wrapper t(*this); ++(*this); return t;}

    const_wrapper&			operator--()	    	{ ptr = _prev(ptr); return *this; }
    const_wrapper	    	operator--(int)			{ const_wrapper t(*this); --(*this); return t;}

    friend bool				operator==( const const_wrapper& x,
										const const_wrapper& y)  {return x.ptr == y.ptr;}

	friend bool				operator!=( const const_wrapper& x,
										const const_wrapper& y)  {return !(x == y);}

};


}
#endif

