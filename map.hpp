/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:49:59 by kiborroq          #+#    #+#             */
/*   Updated: 2021/04/24 10:09:21 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP 

# include "utils.hpp"
# include "random_access_iterator.hpp"
# include "map_iterator.hpp"
# include <memory>

namespace ft
{
	template <	typename Key,
				typename T,
				typename Compare = ft::less<Key>,
				typename Alloc = std::allocator< pair<const Key, T> >
			>
	class map
	{
		public:
			typedef Key									key_type;
			typedef T									mapped_type;
			typedef pair<const key_type, mapped_type>	value_type;
			typedef Alloc								allocator_type;
			typedef value_type &						reference;
			typedef Compare								key_compare;
			typedef value_type const&					const_reference;
			typedef value_type *						pointer;
			typedef value_type const*					const_pointer;
			typedef map_iterator<value_type>			iterator;
			typedef map_iterator<const value_type>		const_iterator;
			typedef _reverse_iterator<iterator>			reverse_iterator;
			typedef _reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef ptrdiff_t							difference_type;
			typedef size_t								size_type;

			class value_comp : ft::binary_function<value_type, value_type, bool>
			{
				friend map<key_type, mapped_type, Compare, allocator_type>;

				protected:
					Compare comp;

					value_comp(Compare c)
						: comp(c)
					{ }

				public:
					bool operator()(value_type const & x, value_type const & y)
					{ return comp(x.first, y.first); }

			}; // class value_comp

		private:
			typedef _node<value_type> node;

		private:
			node _min;
			node _max;
			node _root;
			key_compare _comp;
			allocator_type _alloc;

		public:
			explicit map(key_compare const& comp = key_compare(),
				allocator_type const& alloc = allocator_type())
				: _min(node()), _max(node()), _root(node()), _comp(comp), _alloc(alloc)
			{ _link_root_min_max(); }

			
			~map(void);


		private:
			void _link_root_min_max()
			{
				_root.left = &_min;
				_min.parent = &_root;

				_root.right = &_max;
				_max.parent = &_root;
			}
	};

}; //namespace ft

#endif
