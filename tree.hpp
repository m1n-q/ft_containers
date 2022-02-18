/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:12:17 by mishin            #+#    #+#             */
/*   Updated: 2022/02/18 16:20:49 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//TODO: canonical form
#ifndef TREE_HPP
# define TREE_HPP

#include <cstddef>
#include <string>
#include "tmp.hpp"
#include "utils.hpp"

/**------------------------------------------------------------------------
 * 								//TODO
 * * check _begin_node for iterator (in-order)
 * * _Compare to template param (test with less, greater...)
 * ' now watching _begin_node...
 *
 *------------------------------------------------------------------------**/
namespace ft
{

template <class T> // class Comp, class Alloc>
class Node
{
public:
	typedef T						value_type;
	typedef size_t					size_type;

	Node*		parent;
	Node*		left;
	Node*		right;
	value_type	val;
	bool		empty;		//FIXME : tmp for print
	// size_type	height;

	Node(bool e)			: parent(NULL), left(NULL), right(NULL), val(0), empty(e) {}
	Node(value_type v)			: parent(NULL), left(NULL), right(NULL), val(v), empty(false) {}
	Node(Node* p, value_type v)	: parent(	p), left(NULL), right(NULL), val(v), empty(false) {}
};

template <class T>
class AVL;

template <class T>
std::ostream& 	operator<<(std::ostream& o, const Node<T>* n)
{
	char	c;
	size_t	h  = AVL<T>::get_height(n);

	if (!n->parent)					c = '0';
	else if (n->parent->left == n)	c = 'l';
	else							c = 'r';
	for (size_t i = 0; i < h; i++)
		o << "\t";


	if (n->empty)
		return (o << "");
	return (o << n->val << "(" << h << ", " <<  c << ")");
}

template <class T>
class BST
{
public:
	typedef T						value_type;
	typedef size_t					size_type;
	typedef Node<value_type>		node;


// protected:
public:
	node*		_root;
	node*		_begin_node;	// in-order
	node*		_end_node;	// in-order
	size_type	_size;

public:
	BST() : _root(NULL), _begin_node(NULL), _end_node(NULL), _size(0) {}

	node* insert(value_type val)
	{
		node* p = find_location(val);
		if (p == NULL || p->val != val)
		{
			node* v = new node(val);
			if (p == NULL)
			{
				this->_root = v;
				this->_begin_node = v;
			}
			else
			{
				v->parent = p;

				if (p->val > val)		p->left	= v;
				else					p->right = v;
			}

			_size++;
			if (_begin_node->left != NULL)
				_begin_node = _begin_node->left;

			return v;
		}
		// std::cout << "value [" << val << "] is already exists." << std::endl;
		return NULL;
	}

	node* delete_by_copying(node* x)
	{
		node* xl = x->left;
		node* xr = x->right;
		node* xp = x->parent;
		node* maybe_unbalanced = NULL;

		node* tmp = search(x->val);
		if (!tmp || tmp->val != x->val)
			return NULL;		// no such val

		//' case1: x == leaf
		if (!xl && !xr)
		{
			if (x == _root)
				_root = NULL;
			else
			{
				if (xp->left == x)	xp->left = NULL;
				else				xp->right = NULL;
			}
			delete x;

			maybe_unbalanced = xp;	// can be null if x == root.
		}

		//' case2: x has 2 children
		else if (xl && xr)
		{
			node* M = xl;
			while (M->right)	M = M->right;

			node* Mp = M->parent;
			node* Ml = M->left;

			if (M == Mp->right)	Mp->right = Ml;
			else				Mp->left = Ml;		//! for case (M == xl)

			if (Ml)				Ml->parent = Mp;

			x->val = M->val;						// copying value. it's OK even if x was _root.
			delete M;

			if (Ml)				maybe_unbalanced = Ml;		// new node in M's position
			else				maybe_unbalanced = Mp;
		}

		//' case3: x has 1 child
		else
		{
			node* child = xl ? xl : xr;

			if (x == _root)
				_root = child;
			else
			{
				if (xp->left == x)	xp->left = child;
				else				xp->right = child;
			}
			delete x;

			maybe_unbalanced = child;
		}

		_size--;
		return maybe_unbalanced;
	}

	node* search(value_type val)
	{
		node* p = find_location(val);

		if (p == NULL || p->val != val)
			return NULL;
		else
			return p;
	}
	void print(node* x, int depth, buf<T>& _);
	node* emptyNode() { return new Node<T>(true); }
	void rotate_left(node* z)
	{
		if (!z || !z->right)
			return ;
		node* x  = z->right;
		node* xl = x->left;

		x->parent = z->parent;
		if (z->parent)
		{
			if (z->parent->left == z)
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

	void rotate_right(node* z)
	{
		if (!z || !z->left)
			return ;
		node* x  = z->left;
		node* xr = x->right;

		x->parent = z->parent;
		if (z->parent)
		{
			if (z->parent->left == z)
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

public:	static size_type	get_height(const node* x)
{
	size_type	lh, rh;

	if (!x)
		return 0;
	lh = get_height(x->left);
	rh = get_height(x->right);

	return max(lh, rh) + 1;
}
private:
	node*	find_location(value_type val)
	{
		if (this->_size == 0)			{ return NULL; }

		node* p = NULL;
		node* v = this->_root;

		while (v != NULL)
		{
			if			(v->val == val)	{ return v; }
			else if		(v->val < val)	{ p = v; v = v->right; }
			else						{ p = v; v = v->left; }
		}
		return p;			// where val to be inserted
	}
};



template <class T>
void BST<T>::print(node* x, int depth, buf<T>& _)
{
	if (!_._buf[depth])
		_._buf[depth] = new node*[(int)std::pow(2, depth)]();
	if (!x)
	{
		_.append(depth, emptyNode());
		return ;
	}

	_.append(depth, x);

	print(x->left, depth + 1, _);
	print(x->right, depth + 1, _);

	if (depth == 0)
		_.print();
}

template <class T>
class AVL : public BST<T>
{
public:
	typedef T						value_type;
	typedef size_t					size_type;
	typedef Node<value_type>		node;
	typedef BST<value_type>			bst;

	node* insert(value_type val)
	{
		node* x, *y, *z;
		x = y = z = NULL;
		node* v = bst::insert(val);

		z = v;
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
		return (v);
	}
	void remove(node* u)
	{
		node* x, *y, *z, *w;
		x = y = z = w = NULL;


		node* v = bst::delete_by_copying(u);		// return possible deepest unbalanced node.

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

	void find();

	node* rebalance(node* x, node* y, node* z)
	{
		node*	newz = z;

		if (!(x && y && z))								return newz;
		else if	(z->left == y && y->left == x)			{ bst::rotate_right(z); newz = y ; }
		else if	(z->right == y && y->right == x)		{ bst::rotate_left(z); newz = y; }
		else if	(z->left == y && y->right == x) 		{ bst::rotate_left(y); bst::rotate_right(z); newz = x; }
		else if	(z->right == y && y->left == x)			{ bst::rotate_right(y); bst::rotate_left(z); newz = x; }

		return newz;
	}

	void	print_inorder(node* x)
	{
		if (!x)	return;
		print_inorder(x->left);
		std::cout << x->val << " ";
		print_inorder(x->right);
	}
private:

	size_type	get_bf(node* z)
	{
		size_type	lh, rh, diff;

		lh = bst::get_height(z->left);
		rh = bst::get_height(z->right);

		diff =  (lh > rh) ? (lh - rh) : (rh - lh);
		return diff;
	}
	bool		is_balanced(node* z)
	{
		if (get_bf(z) >=2)
			return false;
		return true;
	}
	node*		get_heavier_subtree(node* x)
	{
		return (bst::get_height(x->left) > bst::get_height(x->right)) ?		// select heavier subtree
				x->left : x->right;
	}
};






}

#endif
