/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:20:31 by mishin            #+#    #+#             */
/*   Updated: 2022/03/25 02:16:28 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



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

/**-----------------------------------------------------------------------------
 *
 *	@ ISO/IEC 14882:1998
 *
 * * [Note: This follows directly from the requirements in the Iterator Requirements Table.
 * * Integral types cannot be iterators, so, if n1 and n2 are values of an integral type N,
 * * the expression X(n1, n2) cannot possibly be interpreted as construction from a range of iterators.
 * !                          ^^^^^^                   						        ^^^^^^^^^^^^^^^^^^^
 * * It must be taken to mean the first constructor in the Iterator Requirements Table, not the second one.
 * * If there is no conversion from N to X::value_type, then this is not a valid expression at all.
 *
 * * One way that sequence implementors can satisfy this requirement is to specialize the member template for every integral type.
 * * Less cumbersome implementation techniques also exist. —end note]
 *
 *--------------------------------------------------------------------------**/



/**------------------------------------------------------------------------
 * 								//TODO
 *
 * ! const testcase
 *
 * * LEAK => check done!
 * * swap() => check done!
 * * operator=() => check done!
 * * enable_if<is_input_iterator> => recovery done!
 * * constructors => check done!
 * * impl reserve()	=> check done!
 * * insert(pos, first, last) => check done!
 * * insert(pos, val) => check done!
 * * insert(pos, n, val) => check done!
 * * pop_back() => check done!
 * * empty, size => check done!
 * * [], at, front, back => check done!
 * * push_back() => check done!
 * * assign() => check done!
 * * erase() => check done!
 * * clear() => check done!
 *
 *------------------------------------------------------------------------**/
namespace ft
{

template <typename T, class Allocator = std::allocator<T> >
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
    typedef ft::reverse_iterator<iterator>				reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;


protected:
	pointer							__begin_;
	pointer							__end_;
	pointer							__end_cap_;
	size_type						__size_;		//NOTE: no use in std?
	allocator_type					__alloc_;
/**========================================================================
* @                           Constructors
*========================================================================**/
public:
	explicit vector( const allocator_type& alloc = allocator_type() )
					:__begin_		(NULL),
					 __end_			(NULL),
					 __end_cap_		(NULL),
					 __size_		(0),
					 __alloc_		(alloc)
					 {}

	explicit vector( size_type				n,
                     const value_type&		val		= value_type(),
                     const allocator_type&	alloc	= allocator_type() )
					:__begin_		(NULL),
					 __end_			(NULL),
					 __end_cap_		(NULL),
					 __size_		(0),
					 __alloc_		(alloc)
					 {
						if (n > 0)
						{
							vallocate(n);
							construct_at_end(n, val);
						}
					 }

	template <class InputIterator>
	 vector( typename enable_if<is_input_iterator<InputIterator>::value,
	 		 InputIterator>::type first,
	 		 InputIterator last,
			 const allocator_type& alloc = allocator_type() )
			//  vector( InputIterator			first,
			//  		InputIterator			last,
			// 			const allocator_type&	alloc = allocator_type() )
					:__begin_		(NULL),
					 __end_			(NULL),
					 __end_cap_		(NULL),
					 __size_		(0),
					 __alloc_		(alloc)
					 {
						size_type n = static_cast<size_type>(distance(first, last));
						if (n > 0)
						{
							vallocate(n);
							for (;first!=last;++first)
								push_back(*first);
						}
					 }

			 vector( const vector& src )
					:__begin_		(NULL),
					 __end_			(NULL),
					 __end_cap_		(NULL),
					 __size_		(0),
					 __alloc_		(src.get_allocator())
					{
						size_type n = src.size();
						if (n > 0)
						{
							vallocate(n);
							for (const_iterator it = src.begin();it != src.end(); ++it)
								push_back(*it);
						}
					}

			~vector()
					{
						vdeallocate();
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

	reverse_iterator       rbegin()					{ return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const			{ return const_reverse_iterator(end()); }
	reverse_iterator       rend()					{ return reverse_iterator(begin()); }
	const_reverse_iterator rend() const				{ return const_reverse_iterator(begin()); }

//' capacity
	size_type				size() const			{ return this->__size_; }
	size_type				max_size() const		{ return std::min<size_type>(std::numeric_limits<difference_type>::max(), this->__alloc().max_size()); }	//NOTE: min OK?
	size_type				capacity() const		{ return static_cast<size_type>(__end_cap() - __begin_); }
	bool					empty() const			{ return (this->__size_ == 0); }
	void					reserve(size_type n)	{ if (n > capacity()) reserve_impl(n); }

//' element access
	reference				at(size_type n)			{ if (n >= size()) std::__throw_out_of_range("vector");	return (*this)[n]; }
	const_reference			at(size_type n) const	{ if (n >= size()) std::__throw_out_of_range("vector");	return (*this)[n]; }

	reference				front()					{ return *(this->__begin_); }
	const_reference			front() const			{ return *(this->__begin_); }

	reference				back()					{ return *(this->__end_ - 1); }
	const_reference			back() const			{ return *(this->__end_ - 1); }

//' modifiers
	template <class InputIterator>
	void assign(typename enable_if<is_input_iterator<InputIterator>::value,
				InputIterator>::type first,
				InputIterator last)
	// void assign(InputIterator first, InputIterator last)
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
		if (n > capacity())
		{
			vdeallocate();		// end = begin
			vallocate(recommend(n));
			construct_at_end(n, u);
		}
		else
		{
			iterator	cur(begin());
			size_type	old_size = size();

			for (;cur != end(); ++cur)
				*cur = u;
			if (n < old_size)
				this->destruct_at_end(this->__begin_ + n);
			else
				construct_at_end(n - old_size, u);
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
    void					insert( iterator				position,
									typename enable_if<is_input_iterator<InputIterator>::value,
									InputIterator>::type	first,
									InputIterator			last)
    // void					insert( iterator		position,
	// 								InputIterator	first,
	// 								InputIterator	last)
	{
		if (first < last)
		{
			size_type		insert_size		= distance(first, last);
			size_type		remained_cap	= (this->__end_cap() - this->__end_);

			if (insert_size <= remained_cap)
			{
				ft::pair<iterator,
						iterator>	copy_range;

				copy_range.first	= position;
				copy_range.second	= end();

				construct_at_end(insert_size);
				for (iterator new_end = end(); copy_range.second != copy_range.first;)		// copying backward from new_end
					*(--new_end) = *(--copy_range.second);

				for (iterator p = position; first != last; ++first, ++p)
					*p = *first;
			}
			else
				realloc_and_move(position, first, last);
		}
	}
	void					insert(iterator position, size_type n, const value_type& val)
	{
		if (n > 0)
		{
			size_type	remained_cap = (this->__end_cap() - this->__end_);
			if (n <= remained_cap)
			{
				ft::pair<iterator,
						iterator>	copy_range;

				copy_range.first	= position;
				copy_range.second	= end();

				construct_at_end(n);
				for (iterator new_end = end(); copy_range.second != copy_range.first;)		// copying backward from new_end
					*(--new_end) = *(--copy_range.second);
				for (iterator p = position; p != position + n; ++p)
					*p = val;
			}
			else
				realloc_and_move(position, n, val);
		}
	}

	iterator				insert(iterator position, const value_type& val)
	{
		pointer pos = this->__begin_ + distance(begin(), position);
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
		return __make_iter(pos);

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
		iterator	pos_f		= first;
		iterator	ret			= pos_f;

		if (first != last)
		{
			for (iterator pos_l = last; pos_l != end(); ++pos_l, ++pos_f)
				*pos_f = *pos_l;
			destruct_at_end(pos_f.base());
		}

		return ret;
	}

	void					swap (vector& x)
	{
		__swap(this->__begin_, x.__begin_);
		__swap(this->__end_, x.__end_);
		__swap(this->__alloc_, x.__alloc_);
		__swap(this->__size_, x.__size_);
		__swap(this->__end_cap(), x.__end_cap());
		__swap(this->__alloc(), x.__alloc());
	}

	void					clear() { destruct_at_end(this->__begin_); };

//' allocator
	allocator_type			get_allocator() const		{ return this->__alloc(); }


/**========================================================================
* %                              private
*========================================================================**/
private:
	allocator_type&			__alloc()							{ return this->__alloc_; }
	const allocator_type&	__alloc() const						{ return this->__alloc_; }
    pointer&				__end_cap()							{ return this->__end_cap_; }
    const pointer&			__end_cap() const					{ return this->__end_cap_; }
	const_iterator			__make_iter(const_pointer p) const	{ return const_iterator(p); }
	iterator				__make_iter(pointer p) 				{ return iterator(p); }


	void			vallocate(size_type n)	// initial allocate for now
	{
		if (n > max_size())
			std::__throw_length_error("vector");
		this->__begin_		= this->__alloc().allocate(n);
		// this->__cap()		= n;
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

	size_type		recommend(size_type new_size)
	{
		const size_type	ms	= max_size();
		const size_type	cap	= capacity();
		if (new_size > ms)	std::__throw_length_error("vector");
		if (cap >= ms / 2)	return ms;

		return std::max(2 * cap, new_size);
	}

	void			construct_at_end(size_type n)
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

	template <class InputIterator>
	void			construct_at_end(typename enable_if<is_input_iterator<InputIterator>::value,	//NOTE: forward OK?
									InputIterator>::type	first,
									InputIterator			last)
	{
		difference_type		__range_size_	= distance(first, last);
		pointer				__pos_ 			= this->__end_;
		pointer				__new_end_		= this->__end_ + __range_size_;
		const_pointer		__first_		= unwrap_iter(first);

		for (; __pos_ != __new_end_; __pos_++, __first_++)
			this->__alloc().construct(__pos_, *__first_);

		this->__size_	+= __range_size_;
		this->__end_	= __new_end_;
	}

	void			destruct_at_end(pointer new_end)
	{
		while (__end_ != new_end)
		{
			this->__alloc().destroy(--__end_);
			--__size_;
		}
	}

	// reallocate, convert old_end to new_pos, construct at new_pos with val/
	// copy construct source before that range.
	void			realloc_and_move(size_type n, const value_type& val)
	{
		if (n == 0)	return;
		size_type	old_size	= size();

		size_type	new_cap		= recommend(size() + n);
		pointer		new_begin	= __alloc().allocate(new_cap);
		pointer		new_pos		= new_begin + size();

		for (size_type i = 0; i < n; i++)
			this->__alloc().construct(new_pos + i, val);
		--new_pos;
		construct_backward(__alloc(), this->__begin_, this->__end_, new_pos);

		vdeallocate();

		this->__begin_		= new_begin;
		this->__size_		= old_size + n;
		this->__end_		= new_begin + size();
		this->__end_cap()	= __begin_ + new_cap;
	}


	// reallocate, convert position to reallocated one, construct at new_position with val.
	// copy construct source before and after that range.
	pointer		realloc_and_move(iterator position, size_type n, const value_type& val)
	{
		if (n == 0)				return unwrap_iter(position);
		size_type	old_size	= size();

		size_type	new_cap		= recommend(size() + n);
		pointer		new_begin	= __alloc().allocate(new_cap);
		pointer		new_pos		= new_begin + distance(begin(), position);


		for (size_type i = 0; i < n; i++)
			this->__alloc().construct(new_pos + i, val);
		--new_pos;
		construct_backward(__alloc(), this->__begin_, unwrap_iter(position), new_pos++);
		construct_forward(__alloc(), unwrap_iter(position), this->__end_, new_pos + n);

		vdeallocate();

		this->__begin_		= new_begin;
		this->__size_		= old_size + n;
		this->__end_		= new_begin + size();
		this->__end_cap()	= __begin_ + new_cap;

		return new_pos;
	}


	// reallocate, convert position to reallocated one, construct at new_pos with (first, last]
	// copy construct source before and after that range.
	template <class InputIterator>
	void			realloc_and_move(iterator				position,
									 typename enable_if< is_input_iterator<InputIterator>::value,
									 InputIterator>::type	first,
									 InputIterator			last)
	{
		if (first == last)				return;
		size_type	old_size			= size();

		difference_type		range_size	= distance(first, last);
		size_type			new_cap		= recommend(size() + range_size);
		pointer				new_begin	= __alloc().allocate(new_cap);
		pointer				new_pos		= new_begin + distance(begin(), position);

		for (size_type i = 0; first != last; i++, first++)
			this->__alloc().construct(new_pos + i, *first);
		--new_pos;
		construct_backward(__alloc(), this->__begin_, unwrap_iter(position), new_pos++);
		construct_forward(__alloc(), unwrap_iter(position), this->__end_, new_pos + range_size);

		vdeallocate();

		this->__begin_		= new_begin;
		this->__size_		= old_size + range_size;
		this->__end_		= new_begin + size();
		this->__end_cap()	= __begin_ + new_cap;
	}


	void			reserve_impl(size_type new_cap)	//check
	{
		size_type	old_size	= size();
		pointer		new_begin	= __alloc().allocate(new_cap);
		pointer		new_end		= new_begin + old_size;

		construct_backward(__alloc(), this->__begin_, this->__end_, new_end-1);
		// * new_end always points after last elem, except (begin == end). if b == e, won't be constructed.

		vdeallocate();

		this->__size_		= old_size;
		this->__begin_		= new_begin;
		this->__end_		= new_begin + size();
		this->__end_cap()	= __begin_ + new_cap;
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
