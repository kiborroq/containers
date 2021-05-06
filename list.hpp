/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 22:32:52 by kiborroq          #+#    #+#             */
/*   Updated: 2021/04/19 00:09:06 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include <memory>
# include "random_access_iterator.hpp"
# include "list_iterator.hpp"
# include "iterator.hpp"

namespace ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class list
	{
		public:
			typedef T									value_type;
			typedef Alloc								allocator_type;
			typedef value_type &						reference;
			typedef value_type const&					const_reference;
			typedef value_type *						pointer;
			typedef value_type const*					const_pointer;
			typedef ptrdiff_t							difference_type;
			typedef size_t								size_type;
			typedef list_iterator<T, T>					iterator;
			typedef list_iterator<const T, T>			const_iterator;
			typedef _reverse_iterator<iterator>			reverse_iterator;
			typedef _reverse_iterator<const_iterator>	const_reverse_iterator;

		private:
			typedef _node<value_type> node;

		private:
			size_type	_size;

		protected:
			allocator_type	_alloc;
			node			_begin;
			node			_end;

		public:
			explicit list(allocator_type const& alloc = allocator_type())
				: _size(0), _alloc(alloc)
			{ _link_begin_end(); }

			explicit list(size_type n, value_type const& val = value_type(),
                allocator_type const& alloc = allocator_type())
				: _size(0), _alloc(alloc)
			{ _link_begin_end(); insert(begin(), n, val); }

			template <class InputIterator>
  			list(InputIterator first, InputIterator last,
         		allocator_type const& alloc = allocator_type())
				: _size(0), _alloc(alloc)
			{ _link_begin_end(); insert(begin(), first, last); }

			list(list const& x)
				: _size(0), _alloc(x._alloc)
			{ _link_begin_end(); *this = x; }

			list & operator=(list const & x)
			{
				if (_size > 0)
					clear();
				assign(x.begin(), x.end());
				return *this;
			}

			~list(void) { clear(); }


			/*
			**Member functions - ITERATORS
			*/

			iterator begin(void) { return _begin.next; }
			const_iterator begin(void) const { return const_iterator(_begin.next); }
			iterator end(void) { return &_end; }
			const_iterator end(void) const { return const_cast<node *>(&_end); }
			reverse_iterator rbegin(void) { return iterator(&_end); }
			const_reverse_iterator rbegin(void) const { return const_iterator(const_cast<node *>(&_end)); }
			reverse_iterator rend(void) { return iterator(_begin.next); }
			const_reverse_iterator rend(void) const { return const_iterator(_begin.next); }


			/*
			**Member functions - CAPACITY
			*/

			bool empty(void) const { return _size == 0; }
			size_type size(void) const { return _size; }
			size_type max_size(void) const { return _alloc.max_size(); }


			/*
			**Member functions - ELEMENT ACCESS
			*/

			reference front(void) { return *_begin.next->data; }
			const_reference front(void) const { return *_begin.next->data; }
			reference back(void) { return *_end.prev->data; }
			const_reference back(void) const { return *_end.prev->data; }


			/*
			**Member functions - MODIFIERS
			*/

			template <class InputIterator>
			void assign(InputIterator first, InputIterator last)
			{
				if (_size > 0)
					clear();
				insert( begin(), first, last );
			}

			void assign(size_type n, const value_type& val)
			{
				if (_size > 0)
					clear();
				insert( begin(), n, val );
			}

			void push_front(const value_type& val) { insert( begin(), val ); }
			void push_back(const value_type& val) { insert( end(), val ); }
			void pop_front(void) { erase( begin() ); }
			void pop_back(void) { erase( --end() ); }

			iterator insert(iterator position, value_type const& val)
			{
				return iterator( _insert_node(position._list->prev, position._list, val) );
			}

			void insert(iterator position, size_type n, value_type const& val)
			{		
				while (n-- > 0)
					_insert_node(position._list->prev, position._list, val);
			}

			template <typename InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last)
			{
				difference_type count = ft::distance<InputIterator>(first, last);

				if (position == begin() || position == end())
				{
					while (count-- > 0)
						_insert_node(position._list->prev, position._list, *first++);
				}
				else
				{
					list tmp(first, last);
					splice(position, tmp, tmp.begin(), tmp.end());
				}
			}

			iterator erase(iterator position)
			{
				if (_size == 0)
					return end();
				return iterator( _erase_node(position._list->prev, position._list->next) );
			}

			iterator erase(iterator first, iterator last)
			{
				while (first != last)
					first = erase(first);
				return last;
			}

			void swap(list & x)
			{
				size_type size_tmp = x._size;
				node * begin_tmp = x._begin.next;
				node * end_tmp = x._end.prev;

				x._size = _size;
				x._begin.next = _begin.next;
				_begin.next->prev = &x._begin;
				x._end.prev = _end.prev;
				_end.prev->next = &x._end;

				_size = size_tmp;
				_begin.next = begin_tmp;
				begin_tmp->prev = &_begin;
				_end.prev = end_tmp;
				end_tmp->next = &_end;
			}

			void resize(size_type n, value_type val = value_type())
			{
				if (_size > n)
				{
					size_type count = _size - n;
					while (count-- > 0)
						erase( --end() );
				}
				else if (_size < n)
					insert(end(), n - _size, val);					
			}

			void clear(void) { erase( begin(), end() ); }


			/*
			**Member functions - OPERATIONS
			*/

			void splice(iterator position, list & x)
			{
				splice(position, x, x.begin(), x.end());
			}

			void splice(iterator position, list & x, iterator i)
			{
				splice(position, x, i, ++i);
			}

			void splice(iterator position, list & x, iterator first, iterator last)
			{
				difference_type count = ft::distance<iterator>(first, last);
				
				if (count > 0)
				{
					node *last_prev = last._list->prev;

					first._list->prev->next = last._list;
					last._list->prev = first._list->prev;

					position._list->prev->next = first._list;
					first._list->prev = position._list->prev;

					last_prev->next = position._list;
					position._list->prev = last_prev;

					if (&x != this)
					{
						_size += count;
						x._size -= count;
					}
				}
			}

			void remove(value_type const& val)
			{
				iterator first = begin();
				iterator last = end();

				while (first != last)
				{
					if (*first == val)
						first = erase(first);
					else
						first++;
				}
			}

			template <typename Predicate>
			void remove_if(Predicate pred)
			{
				iterator first = begin();
				iterator last = end();

				while (first != last)
				{
					if (pred( *first ))
						first = erase(first);
					else
						first++;
				}
			}

			void unique(void)
			{
				iterator second = ++begin();
				iterator last = end();

				while (second != last)
				{
					if (*second == *(--iterator(second)))
						erase(second++);
					else
						second++;
				}
			}

			template <typename BinaryPredicate>
			void unique(BinaryPredicate binary_pred)
			{
				iterator second = ++begin();
				iterator last = end();

				while (second != last)
				{
					if ( binary_pred( *second, *(--iterator(second)) ))
						second = erase(second);
					else
						second++;
				}		
			}

			void merge(list & x)
			{
				if (&x != this)
				{
					iterator first = begin();
					iterator last = end();

					while (first != last)
					{
						while ( first > x.begin() )
							splice(first, x, x.begin());
						first++;				
					}
					if (x.size() != 0)
						splice(last, x.begin(), x.end());
				}
			}

			template <typename Compare>
			void merge(list & x, Compare comp)
			{
				if (&x != this)
				{
					iterator first = begin();
					iterator last = end();

					while (first != last)
					{
						while ( comp( *x.begin(), *first ) )
							splice(first, x, x.begin());
						first++;				
					}
					if (x.size() != 0)
						splice(last, x.begin(), x.end());
				}
			}

			void sort(void)
			{
						
			}

			void reverse(void)
			{
				if (_size > 0)
				{
					iterator first = begin();
					iterator last = end();

					while (first != last)
					{
						_swap_nodelinks(first._list);
						--first;
					}
					_swap_end_begin();
				}
			}

		private:

			/*
			**Private member functions
			*/
			
			node *_insert_node(node *prev, node *next, value_type const& val)
			{
				pointer p = _alloc.allocate(1);
				_alloc.construct(p, val);
				node *n = new node(p, next, prev);
				prev->next = n;
				next->prev = n;
				_size++;
				return n;
			}
 
			node *_erase_node(node *prev, node *next)
			{
				node *n = prev->next;
				_alloc.destroy(n->data);
				_alloc.deallocate(n->data, 1);
				delete n;
				prev->next = next;
				next->prev = prev;
				_size--;
				return next;
			}

			void _add_nodes(node *to_prev, node *to_next, node *from_first, node * from_last)
			{
				to_prev->next = from_first;
				from_first->prev = to_prev;
				
				from_last->next = to_next;
				to_next->prev = from_last;
			}

			node *_merge_slices(node *first, node *second)
			{
				node *begin = first->data < second->data ? first : second;
				node *curr = begin;

				first = first->next;
				second = second->next;
				while (first != NULL)
				{
					while (second != NULL && second->data < first->data)
					{
						curr = second;
						second = curr->next;
						curr = curr->next;
					}
					curr = first;
					first = curr->next;
					curr = curr->next;
				}
				if (second != NULL)
					curr->next = second;
				return begin;
			}

			void _swap_nodelinks(node *n)
			{
				node *tmp;

				tmp = n->next;
				n->next = n->prev;
				n->prev = tmp;
			}

			void _swap_end_begin(void)
			{
				node *tmp;

				_begin.next->next = &_end;
				_end.prev->prev = &_begin;

				tmp = _begin.next;
				_begin.next = _end.prev;
				_end.prev = tmp;
			}

			void _link_begin_end(void) { _begin.next = &_end; _end.prev = &_begin; }
	};


	/*
	**Non-member functions - OVERLOADS
	*/

	template <typename T, typename Alloc>
	void swap(list<T,Alloc>& x, list<T,Alloc>& y) { x.swap(y); }

	template <typename T, typename Alloc>
	bool operator==(list<T,Alloc> const& lhs, list<T,Alloc> const& rhs)
	{
		if (lhs.size() == rhs.size())
		{
			typedef typename list<T, Alloc>::const_iterator const_iterator;

			const_iterator lhs_first = lhs.begin();
			const_iterator rhs_first = rhs.begin();
			const_iterator lhs_last = lhs.end();

			while (lhs_first != lhs_last)
			{
				if (*rhs_first++ != *lhs_first++)
					return false;
			}
			return true;
		}
		else
			return false;
	}

	template <typename T, typename Alloc>
	bool operator!=(list<T,Alloc> const& lhs, list<T,Alloc> const& rhs) { return !(lhs == rhs); }

	template <typename T, typename Alloc>
	bool operator<(list<T,Alloc> const& lhs, list<T,Alloc> const& rhs)
	{
		typedef typename list<T, Alloc>::const_iterator const_iterator;

		const_iterator lhs_first = lhs.begin();
		const_iterator lhs_last = lhs.end();

		const_iterator rhs_first = rhs.begin();
		const_iterator rhs_last = rhs.end();

		for ( ; lhs_first != lhs_last && rhs_first != rhs_last ; lhs_first++, rhs_first++)
		{
			if (*lhs_first < *rhs_first)
				return true;
			else if (*lhs_first > *rhs_first)
				return false;
		}
		return lhs.size() < rhs.size();
	}

	template <typename T, typename Alloc>
	bool operator>(list<T,Alloc> const& lhs, list<T,Alloc> const& rhs) { return !(lhs < rhs); }

	template <typename T, typename Alloc>
	bool operator<=(list<T,Alloc> const& lhs, list<T,Alloc> const& rhs) { return !(lhs > rhs); }

	template <typename T, typename Alloc>
	bool operator>=(list<T,Alloc> const& lhs, list<T,Alloc> const& rhs) { return !(lhs < rhs); }

} // namespace ft

#endif
