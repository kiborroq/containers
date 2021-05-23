/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 22:32:52 by kiborroq          #+#    #+#             */
/*   Updated: 2021/05/23 13:51:14 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include "iterator.hpp"
# include "utils.hpp"
# include <memory>

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
			size_type max_size(void) const
			{ return std::numeric_limits<difference_type>::max() / ( sizeof(value_type) + sizeof(node) ); }


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
				if (this == &x)
					return ;

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
			{ splice(position, x, x.begin(), x.end()); }

			void splice(iterator position, list & x, iterator i)
			{ splice(position, x, i, ++i); }

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
						while (x.size() > 0 && *x.begin() < *first )
							splice(first, x, x.begin());
						first++;				
					}
					if (x.size() != 0)
						splice(last, x, x.begin(), x.end());
				}
				x._size = 0;
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
						while ( x.size() > 0 && comp( *x.begin(), *first ) )
							splice(first, x, x.begin());
						first++;
					}
					if (x.size() != 0)
						splice(last, x, x.begin(), x.end());
				}
				x._size = 0;
			}

			void sort(void)
			{ _merge_sort(*this, ft::less<value_type>()); }

			template <typename Compare>
			void sort(Compare comp)
			{ _merge_sort(*this, comp); }

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

			/*
			**Member functions - OBSERVERS
			*/

			allocator_type get_allocator(void) const
			{ return _alloc; }

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

			template <typename Compare>
			void _merge_sort(list & full, Compare comp)
			{
				if (full.size() < 2)
					return ;

				list first_half(_alloc);
				list second_half(_alloc);

				_split_full(full, first_half, second_half);

				_merge_sort(first_half, comp);
				_merge_sort(second_half, comp);

				first_half.merge(second_half, comp);
				full.splice(full.begin(), first_half);
			}

			void _split_full(list & full, list & first_half, list & second_half)
			{
				iterator half = full.begin();
				ft::advance(half, full.size() / 2);

				first_half.splice(first_half.begin(), full, full.begin(), half);
				second_half.splice(second_half.begin(), full);
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
	void swap(ft::list<T,Alloc>& x, ft::list<T,Alloc>& y) { x.swap(y); }

	template <typename T, typename Alloc>
	bool operator==(ft::list<T,Alloc> const& lhs, ft::list<T,Alloc> const& rhs)
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
	bool operator!=(ft::list<T,Alloc> const& lhs, ft::list<T,Alloc> const& rhs) { return !(lhs == rhs); }

	template <typename T, typename Alloc>
	bool operator<(ft::list<T,Alloc> const& lhs, ft::list<T,Alloc> const& rhs)
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
	bool operator>(ft::list<T,Alloc> const& lhs, ft::list<T,Alloc> const& rhs) { return !(lhs < rhs) && lhs != rhs; }

	template <typename T, typename Alloc>
	bool operator<=(ft::list<T,Alloc> const& lhs, ft::list<T,Alloc> const& rhs) { return !(lhs > rhs); }

	template <typename T, typename Alloc>
	bool operator>=(ft::list<T,Alloc> const& lhs, ft::list<T,Alloc> const& rhs) { return !(lhs < rhs); }

} // namespace ft

#endif // LIST_HPP
