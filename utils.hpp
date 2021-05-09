/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 10:09:38 by kiborroq          #+#    #+#             */
/*   Updated: 2021/05/09 21:28:14 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
	template <typename T>
	void swap(T & first, T & second)
	{
		T tmp = first;
		first = second;
		second = tmp;
	}

	template <class T1, class T2, class Result>
	struct binary_function
	{
    	typedef T1 first_argument_type;
    	typedef T2 second_argument_type;
    	typedef Result result_type;
  	};

	template <typename T>
	struct less : binary_function<T, T, bool>
	{
		bool operator()(T const& x, T const& y) const
		{ return x < y; }
	};

	template <typename T>
	struct equal_to : binary_function <T, T, bool>
	{
  		bool operator() (T const& x, T const& y) const
		{ ft::less<T> _less; return _less(x, y) || _less(y, x); }
	};

	template <typename T1, typename T2>
	struct pair
	{
		public:
			typedef T1 first_type;
			typedef T2 second_type;

			first_type first;
			second_type second;

			pair(void)
				: first(), second()
			{ }

			pair(first_type const& f, second_type const& s)
				: first(f), second(s)
			{ }

			pair(pair const& p)
				: first(p.first), second(p.second)
			{ }

			pair & operator=(pair const& p)
			{ first = p.first; second = p.second; return *this; }

	}; // struct pair

	template <class T1, class T2>
	bool operator==(pair<T1,T2> const& lhs, pair<T1,T2> const& rhs)
	{ return lhs.first == rhs.first  && lhs.second == rhs.second; }

	template <class T1, class T2>
	bool operator!=(pair<T1,T2> const& lhs, pair<T1,T2> const& rhs)
	{ return !(lhs == rhs); }

	template <class T1, class T2>
	bool operator<(pair<T1,T2> const& lhs, pair<T1,T2> const& rhs)
	{ return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

	template <class T1, class T2>
	bool operator<=(pair<T1,T2> const& lhs, pair<T1,T2> const& rhs)
	{ return !(rhs < lhs); }

	template <class T1, class T2>
	bool operator>(pair<T1,T2> const& lhs, pair<T1,T2> const& rhs)
	{ return rhs < lhs; }

	template <class T1, class T2>
	bool operator>=(pair<T1,T2> const& lhs, pair<T1,T2> const& rhs)
	{ return !(lhs < rhs); }

	template <typename T1, typename T2>
	pair<T1, T2> make_pair(T1 f, T2 s)
	{ return pair<T1, T2>(f, s); }

}; // namespace ft

#endif
