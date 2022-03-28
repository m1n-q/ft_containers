/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:12:17 by mishin            #+#    #+#             */
/*   Updated: 2022/03/28 12:09:45 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//TODO: canonical form
#ifndef TREE_HPP
# define TREE_HPP

#include <cstddef>
#include <cstdio>
#include <string>
#include "tree_iter.hpp"
#include "utils.hpp"
#include "pair.hpp"

/**------------------------------------------------------------------------
 * 								//TODO
 * ' check NOTE: const version
 * ! time consumer : get_bf()
 * ! check leak
 *
 *------------------------------------------------------------------------**/

namespace ft
{

template <class Key, class Value>
class Node_kv
{
public:
/**========================================================================
* '                              typedefs
*========================================================================**/
	typedef Key									key_type;
	typedef Value								mapped_type;
	typedef pair<const key_type, mapped_type>	container_value_type;
	typedef size_t								size_type;

	typedef Node_kv*							NodePtr;

/**========================================================================
* .               	         Member variables
*========================================================================**/
	NodePtr					parent;
	NodePtr					left;
	NodePtr					right;
	container_value_type	val;

	NodePtr					_link_to_end;
	NodePtr					_link_to_dummy;

/**========================================================================
* @                           Constructors
*========================================================================**/
	Node_kv()
	: parent(NULL), left(NULL), right(NULL) , _link_to_end(NULL), _link_to_dummy(NULL) {}

	Node_kv(const container_value_type& v)
	: parent(NULL), left(NULL), right(NULL), val(v), _link_to_end(NULL), _link_to_dummy(NULL) {}

	Node_kv(const Node_kv& x)
	: parent(NULL), left(NULL), right(NULL), val(x.val), _link_to_end(NULL), _link_to_dummy(NULL) {}

	~Node_kv() {}

/**========================================================================
* *                            operators
*========================================================================**/
	Node_kv&	operator=(const Node_kv& x)
	{
		this->copy_value(&x);
	}

/**========================================================================
* #                          Member functions
*========================================================================**/
	void	copy_value(NodePtr src)
	{
		// dst->val = src->val;		// ! this will not work, because val.first is const key_type.
		key_type& keyref = const_cast<key_type&>(this->val.first);

					keyref	= src->val.first;
		  this->val.second	= src->val.second;
	}
};

template <class Node, class Comp, class Alloc>
class tree_base
{
/**========================================================================
* '                              typedefs
*========================================================================**/
public:
	typedef Node 												node_type;
    typedef Comp												value_compare;
    typedef Alloc												allocator_type;

	typedef typename node_type::key_type 						key_type;
	typedef typename node_type::mapped_type						mapped_type;
	typedef typename node_type::container_value_type			container_value_type;
	typedef typename allocator_type::size_type					size_type;
	typedef typename allocator_type::difference_type			difference_type;
	typedef node_type*											NodePtr;
	typedef tree_iterator<node_type, difference_type>			iterator;
	typedef tree_const_iterator<node_type, difference_type>		const_iterator;

	typedef typename allocator_type::template rebind<node_type>::other
																node_allocator;


/**========================================================================
* .               	         Member variables
*========================================================================**/
protected:
	node_allocator	_node_alloc;
	value_compare	_vc;

	size_type		_size;
	NodePtr			_root;
	NodePtr			_begin_node;	// in-order
	NodePtr			_end_node;		// in-order

	NodePtr			_after_end;		// dummy node for next(_end_node), outside of tree.


/**========================================================================
* @                             Constructors
*========================================================================**/
protected:
	tree_base()
	: _node_alloc(), _vc(), _size(0), _root(NULL), _begin_node(NULL), _end_node(NULL)
	{
		_after_end = construct_node();
		_begin_node = _after_end;
	}

	tree_base ( const value_compare& __comp,
				const allocator_type& __a)
	: _node_alloc(node_allocator(__a)) ,_vc(__comp), _size(0), _root(NULL), _begin_node(NULL), _end_node(NULL)
	{
		_after_end = construct_node();
		_begin_node = _after_end;
	}

	tree_base(const tree_base& t)
	: _node_alloc(t._node_alloc), _vc(t.value_comp()), _size(0), _root(NULL), _begin_node(NULL), _end_node(NULL)
	{
		_after_end = construct_node();
		_begin_node = _after_end;
	}

	virtual ~tree_base()
	{
		destroy_recursive(_root);
		destroy_node(_after_end);
	}

/**========================================================================
* *                            operators
*========================================================================**/
	tree_base&			operator=(const tree_base& t)
	{
		if (this != &t)
		{
			clear();			// _begin_node = _after_end
			this->value_comp()	= t.value_comp();
			this->_node_alloc	= t._node_alloc;
		}

		return *this;
	}

/**========================================================================
* #                          Member functions
*========================================================================**/
public:
	allocator_type	get_allocator() const	{ return allocator_type(_node_alloc); }
	size_type		size() const			{ return _size; }
	size_type		max_size() const		{ return std::min<size_type>(_node_alloc.max_size(), std::numeric_limits<difference_type>::max());}
											//NOTE: min OK?

	iterator		begin() 				{ return iterator(_begin_node); }
	const_iterator	begin() const			{ return const_iterator(_begin_node); }
	iterator		end() 					{ return iterator(_after_end); }
	const_iterator	end() const				{ return const_iterator(_after_end); }


	void	swap(tree_base& t)
	{
		__swap(_node_alloc, t._node_alloc);
		__swap(_size, t._size);
		__swap(_root, t._root);
		__swap(_begin_node, t._begin_node);
		__swap(_end_node, t._end_node);
		__swap(_after_end, t._after_end);
		__swap(_vc, t._vc);
	}

	//NOTE: only const ver is OK?
	// NodePtr find_key(const key_type& k)
	// {
	// 	NodePtr p = find_location(k);

	// 	if (p == NULL || p->val.first != k)
	// 		return NULL;
	// 	else
	// 		return p;
	// }

	NodePtr find_key(const key_type& k) const
	{
		NodePtr p = find_location(k);

		if (p == NULL || p->val.first != k)
			return NULL;
		else
			return p;
	}

	void	clear()
	{
		destroy_recursive(_root);
		_root = NULL;
		_size = 0;
		_after_end->_link_to_end = NULL;
		_begin_node = _after_end;
	}


	//NOTE: only const version? return NodePtr and construct iterator outside?
	iterator	lower_bound(const key_type& k)
	{
		NodePtr	v		= _root;
		NodePtr	result	= _after_end;

		while (v != NULL)
		{

			if (!value_comp()(v->val, k))	// v >= k
			{
				result = v;
				v = v->left;
			}
			else							// v < k
				v = v->right;
		}
		return iterator(result);
	}

	const_iterator	lower_bound(const key_type& k) const
	{
		NodePtr	v		= _root;
		NodePtr	result	= _after_end;

		while (v != NULL)
		{

			if (!value_comp()(v->val, k))	// v >= k
			{
				result = v;
				v = v->left;
			}
			else							// v < k
				v = v->right;
		}
		return const_iterator(result);
	}


	//NOTE: only const version? return NodePtr and construct iterator outside?
	iterator	upper_bound(const key_type& k)
	{
		NodePtr	v		= _root;
		NodePtr	result	= _after_end;

		while (v != NULL)
		{
			if (value_comp()(k, v->val))	// v > k
			{
				result = v;
				v = v->left;
			}
			else							// v <= k
				v = v->right;
		}
		return iterator(result);
	}

	const_iterator	upper_bound(const key_type& k) const
	{
		NodePtr	v		= _root;
		NodePtr	result	= _after_end;

		while (v != NULL)
		{
			if (value_comp()(k, v->val))	// v > k
			{
				result = v;
				v = v->left;
			}
			else							// v <= k
				v = v->right;
		}
		return const_iterator(result);
	}

	value_compare& value_comp() 			{ return _vc; }
	const value_compare& value_comp() const	{ return _vc; }



// ! internal (base) functions
protected:
	pair<iterator, bool> insert(const container_value_type& val)
	{
		NodePtr p = find_location(val.first);
		if (p == NULL || p->val.first != val.first)
		{
			NodePtr v = construct_node(val);
			if (p == NULL)
			{
				_root = v;
				_begin_node = _end_node = v;

				_end_node->_link_to_dummy	= _after_end;
				_after_end->_link_to_end	= _end_node;
			}
			else
			{
				v->parent = p;

				if (value_comp()(val, p->val))		p->left	= v;
				else								p->right = v;
			}

			_size++;
			adjust_beg_end_after_insert();
			return pair<iterator, bool>(v, true);
		}
		return pair<iterator, bool>(p, false);
	}

	pair<iterator, bool> insert_with_hint(iterator hint, const container_value_type& val)
	{
		NodePtr p = find_location_hint(hint, val.first);
		if (p == NULL || p->val.first != val.first)
		{
			NodePtr v = construct_node(val);
			if (p == NULL)
			{
				_root = v;
				_begin_node = _end_node = v;

				_end_node->_link_to_dummy	= _after_end;
				_after_end->_link_to_end	= _end_node;
			}
			else
			{
				v->parent = p;

				if (value_comp()(val, p->val))		p->left	= v;
				else								p->right = v;
			}

			_size++;
			adjust_beg_end_after_insert();
			return pair<iterator, bool>(v, true);
		}
		return pair<iterator, bool>(p, false);
	}

	void	adjust_beg_end_after_insert()
	{
		if (_begin_node->left != NULL)
			_begin_node = _begin_node->left;
		if (_end_node->right != NULL)
		{
			_end_node->_link_to_dummy = NULL;
			_end_node = _end_node->right;
			_end_node->_link_to_dummy = _after_end;
			_after_end->_link_to_end = _end_node;
		}
	}

	void	adjust_beg_end_before_delete(NodePtr del)	// It 's OK to call before rebalace because (beg, end) are (min, max)
	{
		if (_begin_node == del)
		{
			if (_begin_node == _end_node)
				_begin_node = _after_end;
			else
				_begin_node = _next(del);
		}
		else if (_end_node == del)
		{
			_end_node = _prev(del);
			_end_node->_link_to_dummy = _after_end;
			_after_end->_link_to_end = _end_node;
		}
	}

	NodePtr delete_by_copying(NodePtr x)
	{
		NodePtr xl = x->left;
		NodePtr xr = x->right;
		NodePtr xp = x->parent;
		NodePtr maybe_unbalanced = NULL;


		NodePtr tmp = find_key(x->val.first);
		if (!tmp || tmp->val != x->val)
			return NULL;				// no such val

		//' case1: x == leaf
		if (!xl && !xr)
		{
			adjust_beg_end_before_delete(x);

			if (x == _root)
				_root = NULL;
			else
			{
				if (xp->left == x)		xp->left = NULL;
				else					xp->right = NULL;
			}
			destroy_node(x);


			maybe_unbalanced = xp;	// can be null if x == root.
		}

		//' case2: x has 2 children
		else if (xl && xr)
		{
			NodePtr M = xl;
			while (M->right)		M = M->right;
			adjust_beg_end_before_delete(M);

			NodePtr Mp = M->parent;
			NodePtr Ml = M->left;

			if (M == Mp->right)		Mp->right = Ml;
			else					Mp->left = Ml;				//! for case (M == xl)

			if (Ml)					Ml->parent = Mp;

			// x->val = M->val;									// copying value of M. it's OK even if x was _root.
			x->copy_value(M);
			destroy_node(M);


			if (Ml)					maybe_unbalanced = Ml;		// new node in M's position
			else					maybe_unbalanced = Mp;
		}

		//' case3: x has 1 child
		else
		{
			adjust_beg_end_before_delete(x);
			NodePtr child = xl ? xl : xr;

			if (x == _root)
				_root = child;
			else
			{
				if (xp->left == x)		xp->left = child;
				else					xp->right = child;
			}

			child->parent = xp;
			destroy_node(x);

			maybe_unbalanced = child;
		}

		_size--;
		return maybe_unbalanced;
	}

	void rotate_left(NodePtr z)
	{
		if (!z || !z->right)
			return ;
		NodePtr x  = z->right;
		NodePtr xl = x->left;

		x->parent = z->parent;
		if (z->parent)
		{
			if (is_left_child(z))
				z->parent->left = x;
			else
				z->parent->right = x;
		}

		x->left = z;
		z->parent = x;

		z->right = xl;
		if (xl)
			xl->parent = z;

		if (this->_root == z)
			this->_root = x;

	}

	void rotate_right(NodePtr z)
	{
		if (!z || !z->left)
			return ;
		NodePtr x  = z->left;
		NodePtr xr = x->right;


		x->parent = z->parent;
		if (z->parent)
		{
			if (is_left_child(z))
				z->parent->left = x;
			else
				z->parent->right = x;
		}

		x->right = z;
		z->parent = x;

		z->left = xr;
		if (xr)
			xr->parent = z;

		if (this->_root == z)
			this->_root = x;

	}

	virtual void		dummy() = 0;
	static size_type	get_height(const NodePtr x)
	{
		size_type	lh, rh;

		if (!x)
			return 0;
		lh = get_height(x->left);
		rh = get_height(x->right);

		return max(lh, rh) + 1;
	}


// ! internal (not used in Derived class)
private:
	NodePtr	construct_node()
	{
		NodePtr nd = _node_alloc.allocate(1);
		_node_alloc.construct(nd);
		return nd;
	}

	NodePtr	construct_node(const container_value_type& v)
	{
		NodePtr nd = _node_alloc.allocate(1);
		_node_alloc.construct(nd, v);
		return nd;
	}

	void	destroy_node(NodePtr nd)
	{
		_node_alloc.destroy(nd);
		_node_alloc.deallocate(nd, 1);
	}

	void	destroy_recursive(NodePtr nd)
	{
		if (nd != NULL)
		{
			destroy_recursive(nd->left);
			destroy_recursive(nd->right);
			destroy_node(nd);
		}
	}


	//NOTE: only const version?
	NodePtr	find_location(const key_type& k)
	{
		if (this->_size == 0)			{ return NULL; }

		NodePtr p = NULL;
		NodePtr v = _root;

		while (v != NULL)
		{
			if			(value_comp()(k, v->val)) 		{ p = v; v = v->left; }
			else if		(value_comp()(v->val, k))		{ p = v; v = v->right; }
			else										{ return v; }
		}
		return p;			// where val to be inserted (parent)
	}

	NodePtr	find_location(const key_type& k) const
	{
		if (this->_size == 0)			{ return NULL; }

		NodePtr p = NULL;
		NodePtr v = _root;

		while (v != NULL)
		{
			if			(value_comp()(k, v->val)) 		{ p = v; v = v->left; }
			else if		(value_comp()(v->val, k))		{ p = v; v = v->right; }
			else										{ return v; }
		}
		return p;			// where val to be inserted (parent)
	}


	//NOTE: need const version?
	NodePtr	find_location_hint(iterator hint, const key_type& k)
	{
		if (this->_size == 0)			{ return NULL; }

		NodePtr h = hint.ptr;

		if (h == _after_end || value_comp()(k, h->val))			//@ k < hint
		{
			if (h == _begin_node ||
				value_comp()(_prev(h)->val, k))					//@ prev(hint) < k < hint
			{
				if (h->left == NULL &&
					h != _after_end)	return h;
				else					return (_prev(h));
			}
			return find_location(k);
		}
		else if (value_comp()(h->val, k))						//@ hint < k
		{
			NodePtr __next = _next(h);
			if (h == _end_node ||
				value_comp()(k, __next->val))					//@ hint < k < next(hint)
			{
				if (h->right == NULL)	return h;				//. if h == _end_node (next(h) == end()), h is deepest right.
				else					return (__next);
			}
			return find_location(k);
		}

		return h;	//! hint == k
	}


};



template <class Node, class Comp, class Alloc>
class AVL : public tree_base<Node, Comp, Alloc>
{
/**========================================================================
* '                              typedefs
*========================================================================**/
public:
	typedef tree_base<Node, Comp, Alloc>		base;
	typedef typename base::node_type 			node_type;
	typedef typename base::value_compare 		value_compare;
	typedef typename base::allocator_type 		allocator_type;
	typedef typename base::key_type 			key_type;
	typedef typename base::mapped_type			mapped_type;
	typedef typename base::container_value_type	container_value_type;
	typedef typename base::size_type			size_type;
	typedef typename base::iterator				iterator;
	typedef typename base::const_iterator		const_iterator;
	typedef typename base::NodePtr				NodePtr;

/**========================================================================
* @                            Constructors
*========================================================================**/

	AVL()
		: base() {}

	AVL(const value_compare& __comp,
		const allocator_type& __a)
		: base(__comp, __a) {}

	AVL(const AVL& t)
		: base(t)
	{
		const_iterator	first	= t.begin();
		const_iterator	last	= t.end();
		iterator		e		= this->end();
		for (; first != last; first++)
			insert_with_hint(e, *first);
	}
	~AVL() {}

/**========================================================================
* *                               operators
*========================================================================**/

	AVL&	operator=(const AVL& t)
	{
		if (this == &t)		return *this;

		base::operator=(t);		// clear and copy node_allocator, value_comp()
		const_iterator	first	= t.begin();
		const_iterator	last	= t.end();
		iterator		e		= this->end();
		for (; first != last; first++)
			insert_with_hint(e, *first);

		return *this;
	}

	pair<iterator,bool> insert(const container_value_type& val)
	{
		pair<iterator, bool> result;
		NodePtr x, y, z;
		x = y = z = NULL;
		result = base::insert(val);
		if (result.second == false)
			return result;

		z = result.first.ptr;
		while (z)
		{
			x = y;
			y = z;
			z = z->parent;

			if (x && y && z)
			{
				if (!is_balanced(z))
					break ;
			}
		}
		rebalance(x, y, z);
		return result;
	}

	iterator	insert_with_hint(iterator hint, const container_value_type& val)
	{
		pair<iterator, bool> result;
		NodePtr x, y, z;
		x = y = z = NULL;
		result = base::insert_with_hint(hint, val);
		if (result.second == false)
			return (result.first);

		z = result.first.ptr;
		while (z)
		{
			x = y;
			y = z;
			z = z->parent;

			if (x && y && z)
			{
				if (!is_balanced(z))
					break ;
			}
		}
		rebalance(x, y, z);
		return (result.first);
	}

	void remove(iterator i)
	{
		remove(i.ptr);
	}

	void remove(NodePtr u)
	{
		NodePtr x, y, z, w;
		x = y = z = w = NULL;

		NodePtr v = base::delete_by_copying(u);		// return possible deepest unbalanced node.

		while (v != NULL)
		{
			if (!is_balanced(v))
			{
				z = v;
				y = get_heavier_subtree(z);
				x = get_heavier_subtree(y);

				v = rebalance(x, y, z);
			}
			if (v)
			{
				w = v;
				v = v->parent;
			}
		}
		if (w)
			this->_root = w;
	}

	size_type	remove_key(const key_type& k)
	{
		NodePtr x = base::find_key(k);
    	if (x == NULL)
        	return 0;
    	remove(x);
    	return 1;
	}


// ! internal tools
private:
	void	dummy() {}

	NodePtr rebalance(NodePtr x, NodePtr y, NodePtr z)
	{
		NodePtr	newz = z;

		if (!(x && y && z))								return newz;
		else if	(z->left == y && y->left == x)			{ base::rotate_right(z); newz = y ; }
		else if	(z->right == y && y->right == x)		{ base::rotate_left(z); newz = y; }
		else if	(z->left == y && y->right == x) 		{ base::rotate_left(y); base::rotate_right(z); newz = x; }
		else if	(z->right == y && y->left == x)			{ base::rotate_right(y); base::rotate_left(z); newz = x; }

		return newz;
	}

	size_type	get_bf(NodePtr z)
	{
		size_type	lh, rh, diff;

		lh = base::get_height(z->left);
		rh = base::get_height(z->right);

		diff =  (lh > rh) ? (lh - rh) : (rh - lh);
		return diff;
	}

	bool		is_balanced(NodePtr z)
	{
		if (get_bf(z) >=2)
			return false;
		return true;
	}

	NodePtr		get_heavier_subtree(NodePtr x)
	{
		return (base::get_height(x->left) > base::get_height(x->right)) ?		// select heavier subtree
				x->left : x->right;
	}


};



template <class NodePtr>
NodePtr	deepest_left(NodePtr x)
{
	while (x->left != NULL)
		x = x->left;
	return x;
}
template <class NodePtr>
NodePtr	deepest_right(NodePtr x)
{
	while (x->right != NULL)
		x = x->right;
	return x;
}

//precondition: x != NULL
template <class NodePtr>
bool	is_left_child(NodePtr x)	{ return (x == x->parent->left); }

template <class NodePtr>
bool	is_right_child(NodePtr x)	{ return (x == x->parent->right); }

template <class NodePtr>
NodePtr	_next(NodePtr x)
{
	if (x->_link_to_dummy)	return (x->_link_to_dummy);
	if (x->right != NULL)	return (deepest_left(x->right));

	while (!is_left_child(x))
		x = x->parent;

	return (x->parent);
}

template <class NodePtr>
NodePtr	_prev(NodePtr x)
{
	if (x->_link_to_end)	return (x->_link_to_end);
	if (x->left != NULL)	return deepest_right(x->left);

	while (is_left_child(x))
    	x = x->parent;

	return (x->parent);
}

}

#endif
