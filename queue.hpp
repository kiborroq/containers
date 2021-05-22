/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 21:52:10 by kiborroq          #+#    #+#             */
/*   Updated: 2021/05/22 11:57:41 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "list.hpp"

namespace ft
{
	template <typename T, typename Container = ft::list<T> >
	class queue
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

		protected:
			container_type _queue;

		public:
			explicit queue(container_type const& ctnr = container_type())
				: _queue(ctnr)
			{ }
	
			~queue(void)
			{ }


			/*
			**Member functions - CAPACITY
			*/

			bool empty() const
			{ return _queue.empty(); }

			size_type size() const
			{ return _queue.size(); }


			/*
			**Member functions - ELEMENT ACCESS
			*/

			value_type & front(void)
			{ return _queue.front(); }

			const value_type & front(void) const
			{ return _queue.front(); }

			value_type & back(void)
			{ return _queue.back(); }

			const value_type & back(void) const
			{ return _queue.back(); }

			/*
			**Member functions - MODIFIERS
			*/

			void push(value_type const& val)
			{ _queue.push_back(val); }

			void pop(void)
			{ _queue.pop_front(); }


			/*
			**Non-member functions - OVERLOAD FRIENDS
			*/

			template <class T1, class Container1>
			friend bool operator==(ft::queue<T1, Container1> const& lhs,  ft::queue<T1, Container1> const& rhs);

			template <class T1, class Container1>
			friend bool operator!=(ft::queue<T1, Container1> const& lhs,  ft::queue<T1, Container1> const& rhs);

			template <class T1, class Container1>
			friend bool operator<(ft::queue<T1, Container1> const& lhs,  ft::queue<T1, Container1> const& rhs);

			template <class T1, class Container1>
			friend bool operator<=(ft::queue<T1, Container1> const& lhs,  ft::queue<T1, Container1> const& rhs);

			template <class T1, class Container1>
			friend bool operator> (ft::queue<T1, Container1> const& lhs,  ft::queue<T1, Container1> const& rhs);

			template <class T1, class Container1>
			friend bool operator>=(ft::queue<T1, Container1> const& lhs,  ft::queue<T1, Container1> const& rhs);
	};


	/*
	**Non-member functions - OVERLOADS
	*/

	template <class T, class Container>
	bool operator==(ft::queue<T, Container> const& lhs,  ft::queue<T, Container> const& rhs)
	{ return lhs._queue == rhs._queue; }

	template <class T, class Container>
	bool operator!=(ft::queue<T, Container> const& lhs,  ft::queue<T, Container> const& rhs)
	{ return lhs._queue != rhs._queue; }

	template <class T, class Container>
	bool operator<(ft::queue<T, Container> const& lhs,  ft::queue<T, Container> const& rhs)
	{ return lhs._queue < rhs._queue; }

	template <class T, class Container>
	bool operator<=(ft::queue<T, Container> const& lhs,  ft::queue<T, Container> const& rhs)
	{ return lhs._queue <= rhs._queue; }

	template <class T, class Container>
	bool operator> (ft::queue<T, Container> const& lhs,  ft::queue<T, Container> const& rhs)
	{ return lhs._queue > rhs._queue; }

	template <class T, class Container>
	bool operator>=(ft::queue<T, Container> const& lhs,  ft::queue<T, Container> const& rhs)
	{ return lhs._queue >= rhs._queue; }

} // namespace ft

#endif // QUEUE_HPP
