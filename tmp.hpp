/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 17:33:40 by mishin            #+#    #+#             */
/*   Updated: 2022/02/22 14:25:46 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cmath>
namespace ft
{
template <class T>
class Node;

template <class T>
class buf
{
public:
	Node<T>*** _buf;

	buf() : _buf(new Node<T>**[10]()) {}

	void	append(int depth, Node<T>* n)
	{
		if (_buf[depth])
		{
			int i = -1;
			while (_buf[depth][++i]);
			_buf[depth][i] = n;
		}
	}

	void	print()
	{
		int i = -1;
		int j = -1;
		while (++i < 10)
		{
			j = -1;
			while (++j < (int)pow(2,i))
			{
				if (!(_buf[i]) || !(_buf[i][j]))
					continue ;
				std::cout<<_buf[i][j] << " ";
			}
			std::cout <<std:: endl;
		}
	}
};



// template <class Node, class Alloc>
// class AVL;

// template <class T>
// std::ostream& 	operator<<(std::ostream& o, const Node<T>* n)
// {
// 	char	c;
// 	size_t	h  = AVL<T>::get_height(n);

// 	if (!n->parent)					c = '0';
// 	else if (n->parent->left == n)	c = 'l';
// 	else							c = 'r';
// 	for (size_t i = 0; i < h; i++)
// 		o << "\t";


// 	if (n->empty)
// 		return (o << "");
// 	return (o << n->val << "(" << h << ", " <<  c << ")");
// }




// void print(NodePtr x, int depth, buf<T>& _);
	// NodePtr emptyNode() { return new node_type<T>(true); }








// template <class T>
// void BST<T>::print(NodePtr x, int depth, buf<T>& _)
// {
// 	if (!_._buf[depth])
// 		_._buf[depth] = new NodePtr[(int)std::pow(2, depth)]();
// 	if (!x)
// 	{
// 		_.append(depth, emptyNode());
// 		return ;
// 	}

// 	_.append(depth, x);

// 	print(x->left, depth + 1, _);
// 	print(x->right, depth + 1, _);

// 	if (depth == 0)
// 		_.print();
// }
}



// if (__hint == end() || value_comp()(__v, *__hint))  // check before
//     {
//         // __v < *__hint
//         const_iterator __prior = __hint;
//         if (__prior == begin() || value_comp()(*--__prior, __v))
//         {
//             // *prev(__hint) < __v < *__hint
//             if (__hint.__ptr_->__left_ == nullptr)
//             {
//                 __parent = static_cast<__parent_pointer>(__hint.__ptr_);
//                 return __parent->__left_;
//             }
//             else
//             {
//                 __parent = static_cast<__parent_pointer>(__prior.__ptr_);
//                 return static_cast<__node_base_pointer>(__prior.__ptr_)->__right_;
//             }
//         }
//         // __v <= *prev(__hint)
//         return __find_equal(__parent, __v);
//     }
//     else if (value_comp()(*__hint, __v))  // check after
//     {
//         // *__hint < __v
//         const_iterator __next = _VSTD::next(__hint);
//         if (__next == end() || value_comp()(__v, *__next))
//         {
//             // *__hint < __v < *_VSTD::next(__hint)
//             if (__hint.__get_np()->__right_ == nullptr)
//             {
//                 __parent = static_cast<__parent_pointer>(__hint.__ptr_);
//                 return static_cast<__node_base_pointer>(__hint.__ptr_)->__right_;
//             }
//             else
//             {
//                 __parent = static_cast<__parent_pointer>(__next.__ptr_);
//                 return __parent->__left_;
//             }
//         }
//         // *next(__hint) <= __v
//         return __find_equal(__parent, __v);
//     }
//     // else __v == *__hint
//     __parent = static_cast<__parent_pointer>(__hint.__ptr_);
//     __dummy = static_cast<__node_base_pointer>(__hint.__ptr_);
//     return __dummy;
// }
