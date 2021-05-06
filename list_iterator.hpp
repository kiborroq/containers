/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:29:44 by kiborroq          #+#    #+#             */
/*   Updated: 2021/04/23 10:48:34 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_ITERATOR_HPP
# define LIST_ITERATOR_HPP

# include "iterator.hpp"

namespace ft
{
	template <typename T>
	struct	_node
	{
		private:
			typedef T * pointer;

		public:
			pointer	data;
			_node<T>	*next;
			_node<T>	*prev;

			_node(void)
				: data(NULL), next(NULL), prev(NULL)
			{ }
			
			_node(pointer data, _node *next, _node *prev)
				: data(data), next(next), prev(prev)
			{ }
			
			_node(_node const& n)
				: data(n.data), next(n.next), prev(n.next)
			{ }
	};

	template <typename T, typename _T>
	class list_iterator
	{
		public:
			typedef ptrdiff_t	difference_type;
			typedef T			value_type;
			typedef T *			pointer;
			typedef T &			reference;
			typedef bidirectional_iterator_tag iterator_category;

		private:
			typedef _node<_T> node;

		public:
			node *_list;
		
		private:
			value_type _empty;

		public:
			list_iterator(void)
				: _empty(value_type())
			{ }
			
			list_iterator(node *p)
				: _list(p), _empty(value_type())
			{ }
			
			list_iterator(list_iterator const& li)
				: _list(li._list), _empty(value_type())
			{ }
			
			~list_iterator(void) { }


			list_iterator & operator=(list_iterator const& li)
			{ _list = li._list; return *this; }
			

			bool operator==(list_iterator const& li)
			{ return _list == li._list; }
			
			bool operator!=(list_iterator const& li)
			{ return _list != li._list; }


			reference & operator*(void)
			{
				if (_list->data != NULL)
					return *_list->data;
				return _empty;
			}

			pointer operator->(void)
			{ return _list->data; }


			list_iterator & operator++(void)
			{
				if (_list->next != NULL)
					_list = _list->next;
				return *this;
			}

			list_iterator operator++(int)
			{
				if (_list->next != NULL)
					_list = _list->next;
				return list_iterator(_list->prev);
			}


			list_iterator & operator--(void)
			{
				if (_list->prev != NULL)
					_list = _list->prev;
				return *this;
			}

			list_iterator operator--(int)
			{
				if (_list->prev != NULL)
					_list = _list->prev;
				return list_iterator(_list->next);
			}
	};
}

#endif
