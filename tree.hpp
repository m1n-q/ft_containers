/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:12:17 by mishin            #+#    #+#             */
/*   Updated: 2022/04/05 18:42:25 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

# define NOT_LOST '\0'
# define LOST_L	'\1'
# define LOST_R	'\2'

# include <limits>
# include "tree_iter.hpp"
# include "utils.hpp"
# include "pair.hpp"

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
	char					bf;

	NodePtr					_link_to_end;
	NodePtr					_link_to_dummy;

/**========================================================================
* @                           Constructors
*========================================================================**/
	Node_kv()
	: parent(NULL), left(NULL), right(NULL), bf(0), _link_to_end(NULL), _link_to_dummy(NULL) {}

	Node_kv(const container_value_type& v)
	: parent(NULL), left(NULL), right(NULL), val(v), bf(0), _link_to_end(NULL), _link_to_dummy(NULL) {}

	Node_kv(const Node_kv& x)
	: parent(NULL), left(NULL), right(NULL), val(x.val), bf(0), _link_to_end(NULL), _link_to_dummy(NULL) {}

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
	NodePtr			_end_node;

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
	iterator		begin() 				{ return iterator(_begin_node); }
	const_iterator	begin() const			{ return const_iterator(_begin_node); }
	iterator		end() 					{ return iterator(_after_end); }
	const_iterator	end() const				{ return const_iterator(_after_end); }
	size_type		max_size() const		{ return min<size_type>(_node_alloc.max_size(), std::numeric_limits<difference_type>::max());}


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

	iterator find(const key_type& k)
	{
		NodePtr	result = find_key(k);
		if (!result)
			return end();
		return iterator(result);
	}

	const_iterator find(const key_type& k) const
	{
		NodePtr	result = find_key(k);
		if (!result)
			return end();
		return const_iterator(result);
	}

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

	void	adjust_beg_end_before_delete(NodePtr del)	// It 's OK to call before rebanlace, because (beg, end) are (min, max)
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

	pair<NodePtr, char> delete_by_copying(NodePtr x)
	{
		NodePtr xl = x->left;
		NodePtr xr = x->right;
		NodePtr xp = x->parent;
		NodePtr maybe_unbalanced = NULL;
		char	lost = NOT_LOST;

		NodePtr tmp = find_key(x->val.first);
		if (!tmp || tmp->val != x->val)
			return pair<NodePtr, char>(maybe_unbalanced, lost);	 // ! no such val

		//' case1: x == leaf
		if (!xl && !xr)
		{
			adjust_beg_end_before_delete(x);

			if (x == _root)
				_root = NULL;
			else
			{
				if (is_left_child(x))	{ xp->left	= NULL; lost = LOST_L; }
				else					{ xp->right	= NULL; lost = LOST_R; }
			}
			destroy_node(x);

			maybe_unbalanced = xp;	// ! can be null if x == root.
		}

		//' case2: x has 2 children
		else if (xl && xr)
		{
			//* find Max key under x->left

			NodePtr M = xl;
			while (M->right)		M = M->right;
			adjust_beg_end_before_delete(M);

			//* link M->parent with M->child

			NodePtr Mp = M->parent;
			NodePtr Ml = M->left;

			if (is_right_child(M))	{ Mp->right= Ml; lost = LOST_R; }
			else					{ Mp->left = Ml; lost = LOST_L; }	//! for case (Mp == x, M == xl)

			if (Ml)					Ml->parent = Mp;

			//*  M.val ~> x.val

			x->copy_value(M);
			destroy_node(M);

			maybe_unbalanced = Mp;
		}

		//' case3: x has 1 child
		else
		{
			adjust_beg_end_before_delete(x);
			NodePtr child = xl ? xl : xr;

			if (x == _root)
				_root = child;

			// * link x->parent with x->child
			else
			{
				if (is_left_child(x))	{ xp->left	= child; lost = LOST_L; }
				else					{ xp->right	= child; lost = LOST_R; }
			}

			child->parent = xp;
			destroy_node(x);

			maybe_unbalanced = xp;
		}

		_size--;
		return pair<NodePtr, char>(maybe_unbalanced, lost);
	}


	virtual void		dummy() = 0;

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

	NodePtr	find_location_hint(iterator hint, const key_type& k) const
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

/**========================================================================
* #                          Member functions
*========================================================================**/

	//* In order to decide BF(X), checking if height(X->subtree) was changed.
	//* increment of height(subtree) can affects height(Parent), in SOME cases.
	//'															 ^^^^^^^^^^^^^

	//! rebalancing reduces height.
	//! In case of Insert(), rebalancing doesn't affects height(Parent) because it is reducing after insertion.
	pair<iterator,bool> insert(const container_value_type& val)
	{
		pair<iterator, bool> result;
		NodePtr x, y, z;
		x = y = z = NULL;
		result = base::insert(val);
		if (result.second == false)
			return result;

		z = result.first.ptr;
		bool subtree_height_increased = false;

		if (z->parent)
		{
			if (z->parent->bf == 0)
				subtree_height_increased = true;
			else
				is_left_child(z) ? z->parent->bf-- : z->parent->bf++;
		}

		while (z)
		{
			y = z;
			z = z->parent;

			if (z && subtree_height_increased)	// * height(Y) increased
			{
				if (is_left_child(y))
				{
					if (z->bf == 1)				// * if Z is right-biased, increment of height(Z->left) cannot affects height(Z)
						subtree_height_increased = false;
					z->bf--;
				}
				else if (is_right_child(y))
				{
					if (z->bf == -1)
						subtree_height_increased = false;
					z->bf++;
				}
			}
			else
				subtree_height_increased = false;

			if (!is_balanced(z))
					break ;
		}
		rebalance(z);
		return result;
	}

	iterator	insert_with_hint(iterator hint, const container_value_type& val)
	{
		pair<iterator, bool> result;
		NodePtr x, y, z;
		x = y = z = NULL;
		result = base::insert_with_hint(hint, val);
		if (result.second == false)
			return result.first;

		z = result.first.ptr;
		bool subtree_height_increased = false;

		if (z->parent)
		{
			if (z->parent->bf == 0)
				subtree_height_increased = true;
			else
				is_left_child(z) ? z->parent->bf-- : z->parent->bf++;
		}

		while (z)
		{
			y = z;
			z = z->parent;

			if (z && subtree_height_increased)
			{
				if (is_left_child(y))
				{
					if (z->bf == 1)
						subtree_height_increased = false;
					z->bf--;
				}
				else if (is_right_child(y))
				{
					if (z->bf == -1)
						subtree_height_increased = false;
					z->bf++;
				}
			}
			else
				subtree_height_increased = false;

			if (!is_balanced(z))
					break ;
		}
		rebalance(z);
		return result.first;
	}

	void remove(iterator i)
	{
		remove(i.ptr);
	}

	size_type	remove_key(const key_type& k)
	{
		NodePtr x = base::find_key(k);
    	if (x == NULL)
        	return 0;
    	remove(x);
    	return 1;
	}

	//* In order to decide BF(X), checking if height(X->subtree) was changed.
	//* decrement of height(subtree) can affects height(Parent), in SOME cases.
	//'															 ^^^^^^^^^^^^^
	//! rebalancing reduces height.
	//! But in case of remove(), it can affects height(Parent) because it is reducing after some removal.
	void remove(NodePtr u)
	{
		NodePtr y = NULL;

		pair<NodePtr, char> result	= base::delete_by_copying(u);	// * return possible deepest unbalanced node.
		NodePtr				z		= result.first;
		char				lost	= result.second;
		bool				subtree_height_decreased;

		subtree_height_decreased = false;
		if (z)
		{
			if (lost == LOST_L)
			{
				if (z->bf < 0)
					subtree_height_decreased = true;
				z->bf++;
			}
			else
			{
				if (z->bf > 0)
					subtree_height_decreased = true;
				z->bf--;
			}


			if (!is_balanced(z))
			{
				NodePtr child = z->bf < 0 ? z->left : z->right;;
				if (child->bf != 0)
						subtree_height_decreased = true;
				z = rebalance(z);
			}
		}

		while (z != NULL)
		{
			y = z;
			z = z->parent;
			if (z && subtree_height_decreased)	// * height(Y) height decreased
			{
				if (is_left_child(y))			// * left-child height changed
				{
					if (z->bf >= 0)				// * if Z is right-biased or flat, decrement of height(z->left) cannot affects height(Z).
						subtree_height_decreased = false;
					z->bf++;
				}
				else
				{
					if (z->bf <= 0)
						subtree_height_decreased = false;
					z->bf--;
				}
			}
			else
				subtree_height_decreased = false;

			if (!is_balanced(z))
			{
				NodePtr child = z->bf < 0 ? z->left : z->right;
				if (child->bf != 0)				// ! check if rebalnce(Z) affects height(Z)
					subtree_height_decreased = true;
				z = rebalance(z);
			}
		}
		if (y)
			this->_root = y;
	}


// ! internal tools
private:
	void	dummy() {}

	void	rotate_left(NodePtr z)
	{
		if (!z || !z->right)		return ;

									NodePtr x  = z->right;
									NodePtr xl = x->left;

									x->parent = z->parent;
		if (z->parent)
		{
			if (is_left_child(z))	z->parent->left = x;
			else					z->parent->right = x;
		}

									x->left = z;
									z->parent = x;

									z->right = xl;
		if (xl)						xl->parent = z;

		if (this->_root == z)		this->_root = x;

									z->bf = z->bf - 1 - max(x->bf, '\0');
									x->bf = x->bf - 1 + min(z->bf, '\0');
	}

	void	rotate_right(NodePtr z)
	{
		if (!z || !z->left)			return ;

									NodePtr x  = z->left;
									NodePtr xr = x->right;

									x->parent = z->parent;
		if (z->parent)
		{
			if (is_left_child(z))	z->parent->left = x;
			else					z->parent->right = x;
		}

									x->right = z;
									z->parent = x;

									z->left = xr;
		if (xr)						xr->parent = z;

		if (this->_root == z)		this->_root = x;

									z->bf = z->bf + 1 - min(x->bf, '\0');
									x->bf = x->bf + 1 + max(z->bf, '\0');
	}

	NodePtr rebalance(NodePtr z)
	{
		NodePtr	newz = z;

		if (z)
		{
			if (z->bf == -2)
			{
				if (z->left->bf == +1)
					rotate_left(z->left);
				rotate_right(z);
			}
			else if (z->bf == +2)
			{
				if (z->right->bf == -1)
					rotate_right(z->right);
				rotate_left(z);
			}
			newz = z->parent;
		}
		return newz;
	}

	bool		is_balanced(NodePtr z)
	{
		if (!z)
			return true;
		if (z->bf < -1 || z->bf > 1)
			return false;
		return true;
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
	if (x->_link_to_dummy)		return (x->_link_to_dummy);
	if (x->right != NULL)		return (deepest_left(x->right));

	while (!is_left_child(x))	x = x->parent;

	return (x->parent);
}

template <class NodePtr>
NodePtr	_prev(NodePtr x)
{
	if (x->_link_to_end)		return (x->_link_to_end);
	if (x->left != NULL)		return deepest_right(x->left);

	while (is_left_child(x))	x = x->parent;

	return (x->parent);
}

}

#endif
