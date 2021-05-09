/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:49:59 by kiborroq          #+#    #+#             */
/*   Updated: 2021/05/10 01:47:16 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP 

# include "utils.hpp"
# include "random_access_iterator.hpp"
# include "_rb_tree.hpp"
# include <memory>

namespace ft
{
	template <typename Pair>
	struct _pair_first_comp : ft::binary_function<Pair, Pair, bool>
	{
		bool operator()(Pair x, Pair y)
		{ ft::less<typename Pair::first_type> _less; return _less(x.first, y.first); }
	};

	template <	typename Key,
				typename T,
				typename Compare = ft::less<Key>,
				typename Alloc = std::allocator< ft::pair<Key, T> >
			>
	class map
	{
		public:
			typedef Key						key_type;
			typedef T						mapped_type;
			typedef ft::pair<Key, T>	value_type;
			typedef Alloc					allocator_type;
			typedef value_type &			reference;
			typedef Compare					key_compare;
			typedef value_type const&		const_reference;
			typedef value_type *			pointer;
			typedef value_type const*		const_pointer;

		private:
			typedef ft::_pair_first_comp<value_type> _pair_comp;
			typedef ft::_rb_tree< value_type, Alloc, _pair_comp > tree;

		public:
			typedef typename tree::iterator					iterator;
			typedef typename tree::const_iterator			const_iterator;
			typedef typename tree::reverse_iterator			reverse_iterator;
			typedef typename tree::const_reverse_iterator	const_reverse_iterator;
			typedef ptrdiff_t								difference_type;
			typedef size_t									size_type;

			class value_compare : ft::binary_function<value_type, value_type, bool>
			{
				friend map<key_type, mapped_type, Compare, allocator_type>;

				protected:
					Compare comp;

					value_compare(Compare c)
						: comp(c)
					{ }

				public:
					bool operator()(value_type const & x, value_type const & y)
					{ return comp(x.first, y.first); }

			}; // class value_comp

		private:
			key_compare _comp;
			allocator_type _alloc;
			tree _map;

		public:
			explicit map(key_compare const& comp = key_compare(),
            	allocator_type const& alloc = allocator_type())
				: _comp(comp), _alloc(alloc), _map(_pair_comp(), _alloc)
			{ }

			template <class InputIterator>
			map(InputIterator first, InputIterator last,
				key_compare const& comp = key_compare(),
				allocator_type const& alloc = allocator_type())
				: _comp(comp), _alloc(alloc), _map(first, last, _pair_comp(), _alloc)
			{ }

			map(map const& mp)
				: _comp(mp._comp), _alloc(mp._alloc), _map(mp._map)
			{ }
			
			~map(void)
			{ }

			map operator=(map const& mp)
			{ _map = mp._map; return *this; }


			/*
			**Member functions - ITERATORS
			*/

			iterator begin(void) { return _map._begin(); }
			const_iterator begin(void) const { return _map._begin(); }
			iterator end(void) { return _map._end(); }
			const_iterator end(void) const { return _map._end(); }
			reverse_iterator rbegin(void) { return _map._rbegin(); }
			const_reverse_iterator rbegin(void) const { return _map._rbegin(); }
			reverse_iterator rend(void) { return _map._rend(); }
			const_reverse_iterator rend(void) const { return _map._rend(); }

			/*
			**Member functions - CAPACITY
			*/

			size_type size(void) const
			{ return _map._size; }

			size_type max_size(void) const
			{ return _map._max_size(); }

			bool empty(void) const
			{ return _map._size == 0; }

			
			/*
			**Member functions - ELEMENT ACCESS
			*/

			mapped_type & operator[](key_type const& k)
			{ return  (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second; }


			/*
			**Member functions - MODIFIERS
			*/

			pair<iterator, bool> insert(value_type const& val)
			{
				iterator pos = _map._find(val);

				if (pos._tree != NULL && _map._equal_to(*pos._tree->data, val))
					return ft::make_pair(pos, false);
				return ft::make_pair(_map._insert(val), true);
			}

			iterator insert(iterator position, value_type const& val)
			{
				(void)position;
				return (insert(val)).first;
			}

			template <typename InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
					insert(*first++);
			}

			void erase(iterator position)
			{ _map._erase(position); }
			
			void erase(iterator first, iterator last)
			{ _map._erase(first, last); }

			size_type erase(key_type const& k)
			{
				iterator pos = _map._find(ft::make_pair(k, mapped_type()));
				
				if (_map._equal_to(*pos._tree->data, ft::make_pair(k, mapped_type())))
					erase(pos);
				return 1;
			}

			void swap(map & x)
			{ _map._swap(x._map); }

			void clear(void)
			{ _map._clear(); }

			
			/*
			**Member functions - OBSERVES
			*/

			key_compare key_comp(void) const
			{ return _comp; }

			value_compare value_comp(void) const
			{ return value_compare(_comp); }


			/*
			**Member functions - OPERATIONS
			*/

			iterator find(key_type const& k)
			{
				iterator pos = _map._find(ft::make_pair(k, mapped_type()));
				
				if (_map._equal_to(*pos._tree->data, ft::make_pair(k, mapped_type())))
					return pos;
				return end();
			}

			iterator find(key_type const& k) const
			{
				const_iterator pos = _map._find(ft::make_pair(k, mapped_type()));
				
				if (_map._equal_to(*pos._tree->data, ft::make_pair(k, mapped_type())))
					return pos;
				return end();
			}

			size_type count(key_type const& k) const
			{ return find(k) == end() ? 0 : 1; }

			iterator lower_bound(key_type const& k)
			{
				iterator b = begin();
				iterator e = end();

				while (b != e)
				{
					if (!_comp((*b).first, k))
						break;
					++b;
				}
				return b;
			}

			const_iterator lower_bound(key_type const& k) const
			{
				const_iterator b = begin();
				const_iterator e = end();

				while (b != e)
				{
					if (!_comp((*b).first, k))
						break;
					++b;
				}
				return b;
			}

			iterator upper_bound(key_type const& k)
			{
				iterator b = begin();
				iterator e = end();

				while (b != e)
				{
					if (_comp(k, (*b).first))
						break;
					++b;
				}
				return b;
			}

			const_iterator upper_bound(key_type const& k) const
			{
				const_iterator b = begin();
				const_iterator e = end();

				while (b != e)
				{
					if (_comp(k, (*b).first))
						break;
					++b;
				}
				return b;
			}

			ft::pair<iterator, iterator> equal_range (key_type const& k)
			{ return (ft::make_pair(lower_bound(k), upper_bound(k))); }

			ft::pair<const_iterator, const_iterator> equal_range (key_type const& k) const
			{ return (ft::make_pair(lower_bound(k), upper_bound(k))); }

	};

}; //namespace ft

#endif
