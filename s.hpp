#include <cstddef>

struct input_iterator_tag  {};
struct output_iterator_tag {};
struct forward_iterator_tag       : public input_iterator_tag         {};
struct bidirectional_iterator_tag : public forward_iterator_tag       {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template<class Iterator>
struct iterator_traits
{
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
};

template<class T>
struct iterator_traits<T*>
{
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef random_access_iterator_tag iterator_category;
};

template<class Category, class T, class Distance = ptrdiff_t,
         class Pointer = T*, class Reference = T&>
struct iterator
{
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
};













template <class _Iter>
class __wrap_iter
{
public:
    typedef _Iter                                                      iterator_type;
    typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
    typedef typename iterator_traits<iterator_type>::value_type        value_type;
    typedef typename iterator_traits<iterator_type>::difference_type   difference_type;
    typedef typename iterator_traits<iterator_type>::pointer           pointer;
    typedef typename iterator_traits<iterator_type>::reference         reference;
private:
    iterator_type __i;
public:
      __wrap_iter() {}

    // template <class _Up>
    //     __wrap_iter(const __wrap_iter<_Up>& __u,
    //         typename enable_if<is_convertible<_Up, iterator_type>::value>::type* = nullptr)
    //         : __i(__u.base())

    reference     operator*() const                        { return *__i; }
    pointer       operator->() const                       { return (pointer)_VSTD::addressof(*__i);}
    __wrap_iter&  operator++()                             { ++__i; return *this; }
    __wrap_iter   operator++(int)                          { __wrap_iter __tmp(*this); ++(*this); return __tmp;}
    __wrap_iter&  operator--()                             { --__i; return *this;}
    __wrap_iter   operator--(int)                          { __wrap_iter __tmp(*this); --(*this); return __tmp;}
    __wrap_iter   operator+ (difference_type __n) const    { __wrap_iter __w(*this); __w += __n; return __w;}
    __wrap_iter&  operator+=(difference_type __n)          {  __i += __n; return *this; }
    __wrap_iter   operator- (difference_type __n) const    { return *this + (-__n);}
    __wrap_iter&  operator-=(difference_type __n)          { *this += -__n; return *this;}
    reference     operator[](difference_type __n) const    { return __i[__n];}

    iterator_type base()  const                            { return __i; }

private:
      __wrap_iter(iterator_type __x)  : __i(__x) {}


    template <class _Up> friend class __wrap_iter;
    template <class _CharT, class _Traits, class _Alloc> friend class basic_string;
    template <class _Tp, class _Alloc> friend class _LIBCPP_TEMPLATE_VIS vector;
    template <class _Tp, size_t> friend class _LIBCPP_TEMPLATE_VIS span;

    template <class _Iter1, class _Iter2>
    friend bool
    operator==(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;
    template <class _Iter1, class _Iter2>
    friend bool
    operator<(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;
    template <class _Iter1, class _Iter2>
    friend bool
    operator!=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;

    template <class _Iter1, class _Iter2>
    friend bool
    operator>(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;

    template <class _Iter1, class _Iter2>
    friend bool
    operator>=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;

    template <class _Iter1, class _Iter2>
    friend bool
    operator<=(const __wrap_iter<_Iter1>&, const __wrap_iter<_Iter2>&) ;

    template <class _Iter1, class _Iter2>
    friend auto
    operator-(const __wrap_iter<_Iter1>& __x, const __wrap_iter<_Iter2>& __y)
    -> decltype(__x.base() - __y.base());


    template <class _Iter1>
    friend __wrap_iter<_Iter1>
    operator+(typename __wrap_iter<_Iter1>::difference_type, __wrap_iter<_Iter1>) ;

    template <class _Ip, class _Op> friend _LIBCPP_CONSTEXPR_AFTER_CXX17 _Op copy(_Ip, _Ip, _Op);
    template <class _B1, class _B2> friend _LIBCPP_CONSTEXPR_AFTER_CXX17 _B2 copy_backward(_B1, _B1, _B2);
    template <class _Ip, class _Op> friend _LIBCPP_CONSTEXPR_AFTER_CXX17 _Op move(_Ip, _Ip, _Op);
    template <class _B1, class _B2> friend _LIBCPP_CONSTEXPR_AFTER_CXX17 _B2 move_backward(_B1, _B1, _B2);


    template <class _Tp>
    friend
    typename enable_if
    <
        is_trivially_copy_assignable<_Tp>::value,
        _Tp*
    >::type
    __unwrap_iter(__wrap_iter<_Tp*>);
};











template <class _Tp, class _Up, bool = __has_iterator_category<iterator_traits<_Tp> >::value>
struct __has_iterator_category_convertible_to
    : public integral_constant<bool, is_convertible<typename iterator_traits<_Tp>::iterator_category, _Up>::value>
{};

template <class _Tp, class _Up>
struct __has_iterator_category_convertible_to<_Tp, _Up, false> : public false_type {};

template <class _Tp>
struct __is_cpp17_input_iterator : public __has_iterator_category_convertible_to<_Tp, input_iterator_tag> {};

template <class _Tp>
struct __is_cpp17_forward_iterator : public __has_iterator_category_convertible_to<_Tp, forward_iterator_tag> {};

template <class _Tp>
struct __is_cpp17_bidirectional_iterator : public __has_iterator_category_convertible_to<_Tp, bidirectional_iterator_tag> {};

template <class _Tp>
struct __is_cpp17_random_access_iterator : public __has_iterator_category_convertible_to<_Tp, random_access_iterator_tag> {};

#if _LIBCPP_STD_VER > 17
template <class _Tp>
struct __is_cpp17_contiguous_iterator : public __has_iterator_category_convertible_to<_Tp, contiguous_iterator_tag> {};
#else
template <class _Tp>
struct __is_cpp17_contiguous_iterator : public false_type {};
#endif


template <class _Tp>
struct __is_exactly_cpp17_input_iterator
    : public integral_constant<bool,
         __has_iterator_category_convertible_to<_Tp, input_iterator_tag>::value &&
        !__has_iterator_category_convertible_to<_Tp, forward_iterator_tag>::value> {};





vector(size_type __n, const value_type& __v);
    vector(size_type __n, const value_type& __v, const allocator_type& __a);
    template <class _InputIterator>
        vector(_InputIterator __first, _InputIterator __last,
               typename enable_if<__is_cpp17_input_iterator  <_InputIterator>::value &&
                                 !__is_cpp17_forward_iterator<_InputIterator>::value>::type* = 0);
    template <class _InputIterator>
        vector(_InputIterator __first, _InputIterator __last, const allocator_type& __a,
               typename enable_if<__is_cpp17_input_iterator  <_InputIterator>::value &&
                                 !__is_cpp17_forward_iterator<_InputIterator>::value>::type* = 0);
    template <class _ForwardIterator>
        vector(_ForwardIterator __first, _ForwardIterator __last,
               typename enable_if<__is_cpp17_forward_iterator<_ForwardIterator>::value>::type* = 0);
    template <class _ForwardIterator>
        vector(_ForwardIterator __first, _ForwardIterator __last, const allocator_type& __a,
               typename enable_if<__is_cpp17_forward_iterator<_ForwardIterator>::value>::type* = 0);

    vector(const vector& __v);
    vector(const vector& __v, const allocator_type& __a);
    vector& operator=(const vector& __v);
