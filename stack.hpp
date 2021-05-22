/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 21:52:10 by kiborroq          #+#    #+#             */
/*   Updated: 2021/05/22 11:44:24 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "list.hpp"

namespace ft
{
	template <typename T, typename Container = ft::list<T> >
	class stack
	{
		public:
			typedef T			value_type;
			typedef Container	container_type;
			typedef size_t		size_type;

		protected:
			container_type _stack;

		public:
			explicit stack(container_type const& ctnr = container_type())
				: _stack(ctnr)
			{ }
	
			~stack(void)
			{ }


			/*
			**Member functions - CAPACITY
			*/

			bool empty() const
			{ return _stack.empty(); }

			size_type size() const
			{ return _stack.size(); }


			/*
			**Member functions - ELEMENT ACCESS
			*/

			value_type & top(void)
			{ return _stack.back(); }

			const value_type & top(void) const
			{ return _stack.back(); }


			/*
			**Member functions - MODIFIERS
			*/

			void push(value_type const& val)
			{ _stack.push_back(val); }

			void pop(void)
			{ _stack.pop_back(); }


			/*
			**Non-member functions - OVERLOAD FRIENDS
			*/

			template <class T1, class Container1>
			friend bool operator==(ft::stack<T1, Container1> const& lhs,  ft::stack<T1, Container1> const& rhs);

			template <class T1, class Container1>
			friend bool operator!=(ft::stack<T1, Container1> const& lhs,  ft::stack<T1, Container1> const& rhs);

			template <class T1, class Container1>
			friend bool operator<(ft::stack<T1, Container1> const& lhs,  ft::stack<T1, Container1> const& rhs);

			template <class T1, class Container1>
			friend bool operator<=(ft::stack<T1, Container1> const& lhs,  ft::stack<T1, Container1> const& rhs);

			template <class T1, class Container1>
			friend bool operator> (ft::stack<T1, Container1> const& lhs,  ft::stack<T1, Container1> const& rhs);

			template <class T1, class Container1>
			friend bool operator>=(ft::stack<T1, Container1> const& lhs,  ft::stack<T1, Container1> const& rhs);
	};


	/*
	**Non-member functions - OVERLOADS
	*/

	template <class T, class Container>
	bool operator==(ft::stack<T, Container> const& lhs,  ft::stack<T, Container> const& rhs)
	{ return lhs._stack == rhs._stack; }

	template <class T, class Container>
	bool operator!=(ft::stack<T, Container> const& lhs,  ft::stack<T, Container> const& rhs)
	{ return lhs._stack != rhs._stack; }

	template <class T, class Container>
	bool operator<(ft::stack<T, Container> const& lhs,  ft::stack<T, Container> const& rhs)
	{ return lhs._stack < rhs._stack; }

	template <class T, class Container>
	bool operator<=(ft::stack<T, Container> const& lhs,  ft::stack<T, Container> const& rhs)
	{ return lhs._stack <= rhs._stack; }

	template <class T, class Container>
	bool operator>(ft::stack<T, Container> const& lhs,  ft::stack<T, Container> const& rhs)
	{ return lhs._stack > rhs._stack; }

	template <class T, class Container>
	bool operator>=(ft::stack<T, Container> const& lhs,  ft::stack<T, Container> const& rhs)
	{ return lhs._stack >= rhs._stack; }

} // namespace ft

#endif // STACK_HPP
