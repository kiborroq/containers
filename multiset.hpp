/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiset.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:49:59 by kiborroq          #+#    #+#             */
/*   Updated: 2021/05/23 00:13:39 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTISET_HPP
# define MULTISET_HPP 

# include "iterator.hpp"
# include "utils.hpp"
# include <memory>

namespace ft
{
	template <	typename T,
				typename Compare = ft::less<T>,
				typename Alloc = std::allocator<T>
			>
	class multiset
	{
		public:
			typedef T					key_type;
			typedef T					value_type;
			typedef Compare				key_compare;
			typedef Compare				value_compare;
			typedef Alloc				allocator_type;
			typedef value_type &		reference;
			typedef value_type const&	const_reference;
			typedef value_type *		pointer;
			typedef value_type const*	const_pointer;

		private:
			typedef ft::_rb_tree< value_type, allocator_type, key_compare > tree;

		public:
			typedef typename tree::iterator					iterator;
			typedef typename tree::const_iterator			const_iterator;
			typedef typename tree::reverse_iterator			reverse_iterator;
			typedef typename tree::const_reverse_iterator	const_reverse_iterator;
			typedef ptrdiff_t								difference_type;
			typedef size_t									size_type;

		private:
			key_compare _comp;
			allocator_type _alloc;
			tree _set;

		public:
			explicit multiset(key_compare const& comp = key_compare(),
            	allocator_type const& alloc = allocator_type())
				: _comp(comp), _alloc(alloc), _set(comp, alloc)
			{ }

			template <class InputIterator>
			multiset(InputIterator first, InputIterator last,
				key_compare const& comp = key_compare(),
				allocator_type const& alloc = allocator_type())
				: _comp(comp), _alloc(alloc), _set(first, last, comp, alloc)
			{ }

			multiset(multiset const& st)
				: _comp(st._comp), _alloc(st._alloc), _set(st._set)
			{ }
			
			~multiset(void)
			{ }

			multiset operator=(multiset const& st)
			{ _set = st._set; return *this; }


			/*
			**Member functions - ITERATORS
			*/

			iterator begin(void) { return _set._begin(); }
			const_iterator begin(void) const { return _set._begin(); }
			iterator end(void) { return _set._end(); }
			const_iterator end(void) const { return _set._end(); }
			reverse_iterator rbegin(void) { return _set._rbegin(); }
			const_reverse_iterator rbegin(void) const { return _set._rbegin(); }
			reverse_iterator rend(void) { return _set._rend(); }
			const_reverse_iterator rend(void) const { return _set._rend(); }

			/*
			**Member functions - CAPACITY
			*/

			size_type size(void) const
			{ return _set._size; }

			size_type max_size(void) const
			{ return _set._max_size(); }

			bool empty(void) const
			{ return _set._size == 0; }


			/*
			**Member functions - MODIFIERS
			*/

			iterator insert(value_type const& val)
			{ return _set._insert(val); }

			iterator insert(iterator position, value_type const& val)
			{
				(void)position;
				return insert(val);
			}

			template <typename InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
					insert(*first++);
			}

			void erase(iterator position)
			{ _set._erase(position); }
			
			void erase(iterator first, iterator last)
			{ _set._erase(first, last); }

			size_type erase(value_type const& v)
			{ return _set._erase(v); }

			void swap(multiset & x)
			{ _set._swap(x._set); }

			void clear(void)
			{ _set._clear(); }

			
			/*
			**Member functions - OBSERVES
			*/

			key_compare key_comp(void) const
			{ return _comp; }

			value_compare value_comp(void) const
			{ return value_compare(_comp); }

			allocator_type get_allocator(void) const
			{ return _alloc; }


			/*
			**Member functions - OPERATIONS
			*/

			iterator find(value_type const& v)
			{
				iterator pos = _set._find(v);
				
				if (_set._equal_to(*pos._tree->data, v))
					return pos;
				return end();
			}

			iterator find(value_type const& v) const
			{
				const_iterator pos = _set._find(v);
				
				if (_set._equal_to(*pos._tree->data, v))
					return pos;
				return end();
			}

			size_type count(value_type const& v) const
			{ return _set._count(v); }

			iterator lower_bound(value_type const& v)
			{ return _set._lower_bound(v); }

			const_iterator lower_bound(value_type const& v) const
			{ return _set._lower_bound(v); }

			iterator upper_bound(value_type const& v)
			{ return _set._upper_bound(v); }

			const_iterator upper_bound(value_type const& v) const
			{ return _set._upper_bound(v); }

			ft::pair<iterator, iterator> equal_range (value_type const& v)
			{ return (ft::make_pair(lower_bound(v), upper_bound(v))); }

			ft::pair<const_iterator, const_iterator> equal_range (value_type const& v) const
			{ return (ft::make_pair(lower_bound(v), upper_bound(v))); }
	};

}; //namespace ft

#endif // MULTISET_HPP
