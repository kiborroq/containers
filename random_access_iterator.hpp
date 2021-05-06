/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:51:49 by kiborroq          #+#    #+#             */
/*   Updated: 2021/04/18 10:16:07 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "iterator.hpp"

namespace ft
{
	template <typename T>
	class _normal_iterator
	{
		public:
			typedef ptrdiff_t	difference_type;
			typedef T			value_type;
			typedef T *			pointer;
			typedef T &			reference;
			typedef random_access_iterator_tag iterator_category;

		protected:
			pointer _p;

		public:
			_normal_iterator(void) { }
			_normal_iterator(pointer p) : _p(p) { }
			_normal_iterator(_normal_iterator const &it) : _p(it._p) { }
			~_normal_iterator(void) { }

			_normal_iterator & operator=(_normal_iterator const &it) { _p = it._p; return *this; }

			reference operator*(void) const { return *_p; }
			pointer operator->(void) const { return _p; }
			reference operator[](difference_type n) const { return *(_p + n); }

			bool operator==(_normal_iterator const &it) const { return _p == it._p; }
			bool operator!=(_normal_iterator const &it) const { return _p != it._p; }
			bool operator>(_normal_iterator const &it) const { return _p > it._p; }
			bool operator<(_normal_iterator const &it) const { return _p < it._p; }
			bool operator>=(_normal_iterator const &it) const { return _p >= it._p; }
			bool operator<=(_normal_iterator const &it) const { return _p <= it._p; }

			_normal_iterator & operator++(void) { ++_p; return *this; }
			_normal_iterator operator++(int) { return _normal_iterator(_p++); }
			_normal_iterator & operator--(void) { --_p; return *this; }
			_normal_iterator operator--(int) { return _normal_iterator(_p--); }

			_normal_iterator operator+(difference_type n) const { return _normal_iterator(_p + n); }
			_normal_iterator operator-(difference_type n) const { return _normal_iterator(_p - n); }
			_normal_iterator & operator+=(difference_type n) { _p += n; return *this; }
			_normal_iterator & operator-=(difference_type n) { _p -= n; return *this; }

			friend _normal_iterator operator+(difference_type n, _normal_iterator const& it) { return it + n; }
			friend difference_type operator-(_normal_iterator const& it1, _normal_iterator const& it2) { return it1._p - it2._p; }
	};

	template <typename Iterator>
	class _reverse_iterator
	{
		public:
			typedef Iterator								iterator_type;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::iterator_category	iterator_category;

		protected:
			iterator_type _it;

		public:
			_reverse_iterator(void) { }
			_reverse_iterator(iterator_type const & it) : _it(it) { }
			template <typename Iter>
			_reverse_iterator(_reverse_iterator<Iter> const & rev_it) : _it(rev_it.base()) { }
			~_reverse_iterator(void) { }

			iterator_type base(void) const { return _it; }
 
			_reverse_iterator & operator=(_reverse_iterator const &rev_it) { this->_it = rev_it.base(); return *this; }

			reference operator*(void) const { iterator_type tmp = _it; return *(--tmp); }
			pointer operator->(void) const { return &(operator*()); }
			reference operator[](difference_type n) const { return _it[-n]; }

			_reverse_iterator & operator++(void) { --_it; return *this; }
			_reverse_iterator operator++(int) { return _reverse_iterator(_it--); }
			_reverse_iterator & operator--(void) { ++_it; return *this; }
			_reverse_iterator operator--(int) { return _reverse_iterator(_it++); }

			_reverse_iterator operator+(difference_type n) const { return _reverse_iterator(_it - n); }
			_reverse_iterator operator-(difference_type n) const { return _reverse_iterator(_it + n); }
			_reverse_iterator & operator+=(difference_type n) { _it -= n; return *this; }
			_reverse_iterator & operator-=(difference_type n) { _it += n; return *this; }
	};

	template<typename Iterator>
	bool operator==(_reverse_iterator<Iterator> const &rev_it1,
					_reverse_iterator<Iterator> const &rev_it2)
	{ return rev_it1.base() == rev_it2.base(); }

	template<typename Iterator>
	bool operator!=(_reverse_iterator<Iterator> const &rev_it1,
					_reverse_iterator<Iterator> const &rev_it2)
	{ return rev_it1.base() != rev_it2.base(); }

	template<typename Iterator>
	bool operator>(_reverse_iterator<Iterator> const &rev_it1,
					_reverse_iterator<Iterator> const &rev_it2)
	{ return rev_it1.base() < rev_it2.base(); }

	template<typename Iterator>
	bool operator<(_reverse_iterator<Iterator> const &rev_it1,
					_reverse_iterator<Iterator> const &rev_it2)
	{ return rev_it1.base() > rev_it2.base(); }

	template<typename Iterator>
	bool operator>=(_reverse_iterator<Iterator> const &rev_it1,
					_reverse_iterator<Iterator> const &rev_it2)
	{ return rev_it1.base() <= rev_it2.base(); }

	template<typename Iterator>
	bool operator<=(_reverse_iterator<Iterator> const &rev_it1,
					_reverse_iterator<Iterator> const &rev_it2)
	{ return rev_it1.base() >= rev_it2.base(); }

	template <typename Iterator>
	_reverse_iterator<Iterator> operator+(
		typename _reverse_iterator<Iterator>::difference_type n,
		_reverse_iterator<Iterator> const& rev_it)
	{ return rev_it - n; }

	template <typename Iterator>
	typename _reverse_iterator<Iterator>::difference_type operator-(
		_reverse_iterator<Iterator> const& rev_it1,
		_reverse_iterator<Iterator> const& rev_it2)
	{ return rev_it2.base() - rev_it1.base(); }
};

#endif
