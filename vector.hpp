/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:20:31 by mishin            #+#    #+#             */
/*   Updated: 2022/02/15 16:00:29 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO: ! check size_type | difference_type
//TODO: ! check leaks ( assign() not destroy??? )

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <stdexcept>
# include <memory>
# include "iterator.hpp"
# include "pair.hpp"
# include "utils.hpp"

namespace ft
{
using std::allocator;

template <typename T, class Allocator = allocator<T> >
class vector
{
/**========================================================================
* '                              typedef
*========================================================================**/
public:
	typedef T											value_type;
    typedef Allocator									allocator_type;
    typedef typename allocator_type::reference			reference;
    typedef typename allocator_type::size_type			size_type;
    typedef typename allocator_type::difference_type	difference_type;
    typedef typename allocator_type::pointer			pointer;
    typedef typename allocator_type::const_pointer		const_pointer;
    typedef typename allocator_type::const_reference	const_reference;
    typedef wrap_iter<pointer>							iterator;
    typedef wrap_iter<const_pointer>					const_iterator;
    typedef ft::reverse_iterator<iterator>				reverse_iterator;		//TODO: test
    typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;


protected:
	pointer							__begin_;
	pointer							__end_;
	pointer							__end_cap_;
	size_type						__size_;		//NOTE: no use in std?
	pair<size_type, allocator_type>	__cap_alloc_;
public:
/**========================================================================
* @                           Constructors
*========================================================================**/

	explicit vector( const allocator_type& alloc = allocator_type() )
					:__begin_		(NULL),
					 __end_			(NULL),
					 __end_cap_		(NULL),
					 __size_		(0),
					 __cap_alloc_	(0, alloc)
					 {}

	explicit vector( size_type				n,
                     const value_type&		val		= value_type(),
                     const allocator_type&	alloc	= allocator_type() )
					:__begin_		(NULL),
					 __end_			(NULL),
					 __end_cap_		(NULL),
					 __size_		(0),
					 __cap_alloc_	(0, alloc)
					 {
						if (n > 0)
						{
							vallocate(n);
							construct_at_end(n, val);
						}
					 }

	template <class InputIterator>
			 vector( typename enable_if<!is_integral<InputIterator>::value,
			 		 InputIterator>::type first,
			 		 InputIterator last,
					 const allocator_type& alloc = allocator_type() )
					:__begin_		(NULL),
					 __end_			(NULL),
					 __end_cap_		(NULL),
					 __size_		(0),
					 __cap_alloc_	(0, alloc)
					 {
						size_type n = static_cast<size_type>(distance(first, last));
						if (n > 0)
						{
							vallocate(n);
							for (;first!=last;++first)
								push_back(*first);		//or construct_at_end?
						}
					 }

			 vector( const vector& src )
					:__begin_		(NULL),
					 __end_			(NULL),
					 __end_cap_		(NULL),
					 __size_		(0),
					 __cap_alloc_	(0, src.get_allocator())	// is it copy
					{
						size_type n = src.size();
						if (n > 0)
						{
							vallocate(n);
							for (const_iterator it = src.begin();it != src.end(); ++it)
								push_back(*it);		//or construct_at_end?
						}
					}

			~vector() {
				while (__end_ != __begin_)
					__alloc().destroy(--__end_);
			}

/**========================================================================
* *                            operators
*========================================================================**/

	reference		operator[]( size_type n ) 		{ return this->__begin_[n]; }
	const_reference	operator[]( size_type n ) const	{ return this->__begin_[n]; }
	vector&			operator=( const vector& src )
	{
		if (this != &src)
    	{
        	assign(src.begin(), src.end());
    	}
    	return *this;
	}



/**========================================================================
* #                          member functions
*========================================================================**/
//' iterator
	iterator               begin()					{ return __make_iter(this->__begin_); }
	const_iterator         begin() const			{ return __make_iter(this->__begin_); }
	iterator               end()					{ return __make_iter(this->__end_); }
	const_iterator         end() const				{ return __make_iter(this->__end_); }

	reverse_iterator       rbegin()					{ return reverse_iterator(end()); }				// TODO: test. think
	const_reverse_iterator rbegin() const			{ return const_reverse_iterator(end()); }
	reverse_iterator       rend()					{ return reverse_iterator(begin()); }
	const_reverse_iterator rend() const				{ return const_reverse_iterator(begin()); }

//' capacity
	size_type				size() const			{ return this->__size_; }		//Returns the number of elements in the vector. This is the number of actual objects held in the vector, which is not necessarily equal to its storage capacity.
	size_type				max_size() const		{ return std::min<size_type>(std::numeric_limits<difference_type>::max(), this->__alloc().max_size()); }	//NOTE: min OK?
	size_type				capacity() const		{ return this->__cap(); }
	bool					empty() const			{ return (this->__size_ == 0); }
	void					reserve(size_type n);

//' element access
	reference				at(size_type n)			{ if (n >= size()) std::__throw_out_of_range("vector");	return (*this)[n]; }
	const_reference			at(size_type n) const	{ if (n >= size()) std::__throw_out_of_range("vector");	return (*this)[n]; }

	reference				front()					{ return *(this->__begin_); }
	const_reference			front() const			{ return *(this->__begin_); }

	reference				back()					{ return *(this->__end_ - 1); }	// __size_ - 1 ?
	const_reference			back() const			{ return *(this->__end_ - 1); }

//' modifiers
	template <class InputIterator>
	void assign(typename enable_if<!is_integral<InputIterator>::value,
					InputIterator>::type first,
					InputIterator last)
	{
		size_type new_size = static_cast<size_type>(distance(first, last));
		if (new_size > capacity())
		{
			vdeallocate();		// end = begin
			vallocate(recommend(new_size));
			construct_at_end(first, last);
		}
		else
		{
			iterator cur(begin());

			for (;first != last && cur != end(); ++cur, ++first)
				*cur = *first;
			if (first == last)
				erase(cur, end());
			else
				insert(end(), first, last);
		}
	}

	void					assign(size_type n, const value_type& u)
	{
		if (n <= capacity())
		{
			_VSTD::fill_n(this->__begin_, _VSTD::min(n, __size_), u);	//TODO : fill_n -> assign operator loop
			if (n > __size_)
				construct_at_end(n - __size_, u);
			else
				this->destruct_at_end(this->__begin_ + n);
		}
		else
		{
			vdeallocate();		// end = begin
			vallocate(recommend(n));
			construct_at_end(n, u);
		}
	}

	void					push_back(const value_type& x)
	{
		if (this->__end_ != this->__end_cap())
			construct_at_end(1, x);
		else
			realloc_and_move(1, x);
	}

	void					pop_back(void)
	{
		// _LIBCPP_ASSERT(!empty(), "vector::pop_back called for empty vector");
    	this->destruct_at_end(this->__end_ - 1);
	}

	template <class InputIterator>
    void					insert( iterator position,
									typename enable_if<!is_integral<InputIterator>::value,
									InputIterator>::type first,
									InputIterator last)
	{
		if (first < last)
		{
			size_type		range_size		= unwrap_iter(last) - unwrap_iter(first);		//NOTE: distance
			size_type		remained_cap	= (this->__end_cap() - this->__end_);

			if (range_size <= remained_cap)
			{
				size_type	d = end() - position;
				if (range_size > d)		// why..?		//TODO: compare each if consruct order with std, consider why d.
				{
					construct_at_end(first + d, last);
					range_size = d;
				}
				if (range_size > 0)
				{
					construct_at_end(position, position + d);
					for (iterator p = position; first != last; ++p, ++first)
						*p = *first;
				}
			}
			else
				realloc_and_move(position, first, last);
		}
	}
	void					insert(iterator position, size_type n, const value_type& val)
	{
		if (n > 0)
		{
			size_type remained_cap = (this->__end_cap() - this->__end_);
			if (n <= remained_cap)
			{
				construct_at_end(position, end());
				for (iterator p = position; p != position + n; ++p)
					*p = val;
			}
			else
				realloc_and_move(position, n, val);
		}
	}

	iterator				insert(iterator position, const value_type& val)
	{
		pointer pos = this->__begin_ + (position - begin());
		if (this->__end_ < this->__end_cap())
		{
			if (position == end())
				construct_at_end(1, val);
			else
			{
				//	for expr (end()-1), there is an exception (begin==end).
				//	case (begin == end) means size==0,
				//	and it means 'position' can only be (begin | end).
				construct_at_end(1, *(end()-1));
				for (iterator p = end()-2; p != position; --p)
					*p = *(p - 1);
				*pos = val;

			}
		}
		else
			pos = realloc_and_move(position, 1, val);
		return __make_iter(pos); //

	}

	iterator				erase(iterator position)
	{
		// _LIBCPP_ASSERT(__position != end(),
        // "vector::erase(iterator) called with a non-dereferenceable iterator");
		iterator	ret = position;

		for (iterator pos = position + 1; pos != end(); ++pos, ++position)
			*position = *pos;
		destruct_at_end(position.base());

		return ret;
	}

	iterator				erase(iterator first, iterator last)		// ! erase [first, last)
	{
		// _LIBCPP_ASSERT(__first <= __last,
		// "vector::erase(first, last) called with invalid range");
		iterator	position	= first;
		iterator	ret			= position;

		if (first != last)
		{
			for (iterator pos = last; pos != end(); ++pos, ++position)
				*position = *pos;
			destruct_at_end(position.base());
		}

		return ret;
	}

	void					swap (vector& x)
	{
		__swap(this->__begin_, x.__begin_);
		__swap(this->__end_, x.__end_);
		__swap(this->__cap_alloc_, x.__cap_alloc_);
		__swap(this->__size_, x.__size_);
		__swap(this->__end_cap(), x.__end_cap());
		__swap(this->__alloc(), x.__alloc());
	}

	void					clear() { destruct_at_end(this->__begin_); __size_ = 0; };

//' allocator
	allocator_type			get_allocator() const		{ return this->__alloc(); }


/**========================================================================
* %                              private
*========================================================================**/
private:
	size_type&				__cap()							{ return this->__cap_alloc_.first; }		// const overloading?
	const size_type&		__cap() const					{ return this->__cap_alloc_.first; }		// const overloading?
	allocator_type&			__alloc()						{ return this->__cap_alloc_.second; }		// const overloading?
	const allocator_type&	__alloc() const					{ return this->__cap_alloc_.second; }		// const overloading?
    pointer&				__end_cap()						{ return this->__end_cap_; }
    const pointer&			__end_cap() const				{ return this->__end_cap_; }
	const_iterator			__make_iter(const_pointer p) const	{ return const_iterator(p); }
	iterator				__make_iter(pointer p) 			{ return iterator(p); }


	void			vallocate(size_type n)	// initial allocate for now
	{
		if (n > max_size())
			std::__throw_length_error("vector");
		this->__begin_		= this->__alloc().allocate(n);
		this->__cap()		= n;
		this->__end_cap()	= this->__begin_ + n;
		this->__size_		= 0;				// will be set at construct_at_end()
		this->__end_		= this->__begin_;	// will be set at construct_at_end()
	}

	void			vdeallocate(void)	// initial allocate for now
	{
		if (this->__begin_ != NULL)
		{
			clear();
			__alloc().deallocate(this->__begin_, capacity());
			this->__begin_ = this->__end_ = this->__end_cap() = NULL;
		}
	}

	size_type		recommend(size_type new_size)	//TODO
	{
		const size_type	ms	= max_size();
		const size_type	cap	= capacity();
		if (new_size > ms)	std::__throw_length_error("vector");
		if (cap >= ms / 2)	return ms;

		return std::max(2 * cap, new_size);
	}

	void			construct_at_end(size_type n)	//NOTE: unused?
	{
		pointer	__pos_ 		= this->__end_;
		pointer	__new_end_	= this->__end_ + n;

		for (; __pos_ != __new_end_; ++__pos_)
			this->__alloc().construct(__pos_);

		this->__size_	+= n;
		this->__end_	= __new_end_;
	}

	void			construct_at_end(size_type n, const value_type& x)
	{
		pointer	__pos_ 		= this->__end_;
		pointer	__new_end_	= this->__end_ + n;

		for (; __pos_ != __new_end_; __pos_++)
			this->__alloc().construct(__pos_, x);

		this->__size_	+= n;
		this->__end_	= __new_end_;
	}

	void			construct_at_end(iterator first, iterator last)
	{
		difference_type		__range_size_	= unwrap_iter(last) - unwrap_iter(first);		//NOTE: distance
		pointer				__pos_ 			= this->__end_;
		pointer				__new_end_		= this->__end_ + __range_size_;
		pointer				__first_		= unwrap_iter(first);

		for (; __pos_ != __new_end_; __pos_++, __first_++)
			this->__alloc().construct(__pos_, *__first_);

		this->__size_	+= __range_size_;
		this->__end_	= __new_end_;
	}

	void			destruct_at_end(pointer new_last)
	{
		// pointer	soon_to_be_end = __end_;

		while (/*soon to be*/__end_ != new_last)
		{
			this->__alloc().destroy(--/*soon to be*/__end_);
			--__size_;
		}
		// __end_ = new_last;
	}

	void			realloc_and_move(size_type n, const value_type& x)
	{

		size_type	new_cap		= recommend(size() + n);
		pointer		new_begin	= __alloc().allocate(new_cap); //LEAKS
		pointer		pos			= new_begin + size();

		for (size_type i = 0; i < n; i++)
			this->__alloc().construct(pos + i, x);
		--pos;
		construct_backward(__alloc(), this->__begin_, this->__end_, pos);	//TODO: destroy src //NOTE:remove reference?
		destruct_backward(__alloc(), this->__begin_, this->__end_);

		this->__begin_		= new_begin;
		this->__size_		= size() + n;
		this->__end_		= new_begin + size();
		this->__cap()		= new_cap;
		this->__end_cap()	= __begin_ + __cap();
	}

// public:
	void			realloc_and_move(iterator position, iterator first, iterator last)	//check
	{
		difference_type		range_size	= unwrap_iter(last) - unwrap_iter(first);	//NOTE: distance
		size_type			new_cap		= recommend(size() + range_size);
		pointer				new_begin	= __alloc().allocate(new_cap); //LEAKS
		pointer				pos			= new_begin + (unwrap_iter(position) - unwrap_iter(begin()));

		for (size_type i = 0; first != last; i++, first++)
			this->__alloc().construct(pos + i, *first);
		--pos;
		construct_backward(__alloc(), this->__begin_, unwrap_iter(position), pos++);
		construct_forward(__alloc(), unwrap_iter(position), this->__end_, pos + range_size);
		//destruct_backward(Alloc &alloc, T *begin, T *end);

		this->__begin_		= new_begin;
		this->__size_		= size() + range_size;
		this->__end_		= new_begin + size();
		this->__cap()		= new_cap;
		this->__end_cap()	= __begin_ + __cap();
	}

	pointer		realloc_and_move(iterator position, size_type n, const value_type& val)	//check
	{
		size_type	new_cap		= recommend(size() + n);
		pointer		new_begin	= __alloc().allocate(new_cap); //LEAKS
		pointer		pos			= new_begin + (unwrap_iter(position) - unwrap_iter(begin()));


		for (size_type i = 0; i < n; i++)
			this->__alloc().construct(pos + i, val);
		--pos;
		construct_backward(__alloc(), this->__begin_, unwrap_iter(position), pos++);
		construct_forward(__alloc(), unwrap_iter(position), this->__end_, pos + n);
		destruct_backward(__alloc(), this->__begin_, this->__end_);

		this->__begin_		= new_begin;
		this->__size_		= size() + n;
		this->__end_		= new_begin + size();
		this->__cap()		= new_cap;
		this->__end_cap()	= __begin_ + __cap();

		return pos;
	}

	template <class U>
	void	__swap(U& u1, U& u2)
	{
		U tmp = u1;

		u1 = u2;
		u2 = tmp;
	}
};

/**========================================================================
* *                        relational-operators
*========================================================================**/
template <class T, class Alloc> bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return	lhs.size() == rhs.size() &&
			equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <class T, class Alloc> bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return lexicographical_compare( lhs.begin(), lhs.end(),
									rhs.begin(), rhs.end() );
}

template <class T, class Alloc> bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)	{ return !(lhs == rhs); }
template <class T, class Alloc> bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)	{ return rhs < lhs; }
template <class T, class Alloc> bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)	{ return !(lhs > rhs); }
template <class T, class Alloc> bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)	{ return !(lhs < rhs); }

/**========================================================================
* #                         non-member functions
*========================================================================**/
template <class T, class Alloc> void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)	{ x.swap(y); }

// ! SFIANE => 함수의 "선언부" 에 올바르지 않은 타입을 넣어서 타입 치환 오류를 발생시켜야 합니다.
// '                 ^^^^^

}
#endif
