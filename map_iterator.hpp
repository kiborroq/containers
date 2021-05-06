/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _rb_tree_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 21:05:30 by kiborroq          #+#    #+#             */
/*   Updated: 2021/04/24 10:52:19 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include <iostream>

# include <memory>
# include "iterator.hpp"
# include "random_access_iterator.hpp"
# include "utils.hpp"

namespace ft
{
	struct _color
	{
		static const char red = 0;
		static const char black = 1;
		static const char min = 3;
		static const char max = 4;
	};

	template <typename T>
	struct _rb_node
	{
		char color;
		_rb_node *parent;
		_rb_node *left;
		_rb_node *right;
		T *data;

		_rb_node(void)
			: color(_color::black), parent(NULL), left(NULL), right(NULL), data(NULL)
		{ }

		_rb_node(char c, _rb_node *p, _rb_node *l, _rb_node *r, T *k)
			: color(c), parent(p), left(l), right(r), data(k)
		{ }

		_rb_node(_rb_node const& n)
			: color(n.color), parent(n.parent), left(n.left), right(n.right), data(n.data)
		{ }

		bool _is_right(void)
		{ return this == this->parent->right; }

		bool _is_left(void)
		{ return !_is_right(); }

	}; // struct _rb_node

template <typename T, typename _T>
	class _rb_tree_iterator
	{
		public:
			typedef ptrdiff_t	difference_type;
			typedef T			value_type;
			typedef T *			pointer;
			typedef T &			reference;
			typedef bidirectional_iterator_tag iterator_category;

		private:
			typedef _rb_node<_T> node;

		public:
			node *_tree;
			
		private:
			value_type _empty;

		public:
			_rb_tree_iterator(void)
				: _empty(value_type())
			{ }

			_rb_tree_iterator(node *p)
				: _tree(p), _empty(value_type())
			{ }

			_rb_tree_iterator(_rb_tree_iterator const& tr)
				: _tree(tr._tree), _empty(value_type())
			{ }

			~_rb_tree_iterator(void)
			{ }

			_rb_tree_iterator & operator=(_rb_tree_iterator const& tr)
			{ _tree = tr._tree; return *this; }


			bool operator==(_rb_tree_iterator const& tr)
			{ return _tree == tr._tree; }
			
			bool operator!=(_rb_tree_iterator const& tr)
			{ return _tree != tr._tree; }


			reference & operator*(void)
			{
				if (_tree->data != NULL)
					return *_tree->data;
				return _empty;
			}

			pointer operator->(void)
			{ return _tree->data; }


			_rb_tree_iterator & operator++(void)
			{
				if (_tree->color != _color::max)
					_tree = _get_next_node(_tree);
				return *this;
			}

			_rb_tree_iterator operator++(int)
			{
				node *tmp = _tree;
				if (_tree->color != _color::max)
					_tree = _get_next_node(_tree);
				return _rb_tree_iterator(tmp);
			}


			_rb_tree_iterator & operator--(void)
			{
				if (_tree->left == NULL || _tree->left->color != _color::min)
					_tree = _get_prev_node(_tree);
				return *this;
			}

			_rb_tree_iterator operator--(int)
			{
				node *tmp = _tree;
				if (_tree->left == NULL || _tree->left->color != _color::min)
					_tree = _get_prev_node(_tree);
				return _rb_tree_iterator(tmp);
			}

		private:
			node *_get_next_node(node *curr)
			{
				if (curr == NULL)
					return NULL;
				if (curr->right == NULL)
				{
					while (curr->_is_right())
						curr = curr->parent;
					return curr->parent;
				}
				curr = curr->right;
				while (curr->left)
					curr = curr->left;
				return curr;
			}

			node *_get_prev_node(node *curr)
			{
				if (curr == NULL)
					return NULL;
				if (curr->left == NULL)
				{
					while (curr->_is_left())
						curr = curr->parent;
					return curr->parent;
				}
				curr = curr->left;
				while (curr->right)
					curr = curr->right;
				return curr;
			}

	}; // class _rb_tree_iterator

	template < typename T, typename Alloc = std::allocator<T>, typename Less = ft::less<T>, typename Equal = ft::equal_to<T> >
	class _rb_tree
	{
		public:
			typedef T									value_type;
			typedef Alloc								allocator_type;
			typedef value_type &						reference;
			typedef Less								compare_less;
			typedef Equal								compare_eqaul;
			typedef value_type const&					const_reference;
			typedef value_type *						pointer;
			typedef value_type const*					const_pointer;
			typedef _rb_tree_iterator<T, T>				iterator;
			typedef _rb_tree_iterator<const T, T>		const_iterator;
			typedef _reverse_iterator<iterator>			reverse_iterator;
			typedef _reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef ptrdiff_t							difference_type;
			typedef size_t								size_type;

		private:
			typedef _rb_node<T> node;

		public:
			size_type _size;
			node *_root;
			node _min;
			node _max;
			compare_less _less;
			compare_eqaul _equal;
			allocator_type _alloc;

		public:
			explicit _rb_tree(compare_less const& l = compare_less(),
				compare_eqaul const& e = compare_eqaul(),
				allocator_type const& alloc = allocator_type())
				: _size(0), _root(NULL), _min(node()), _max(node()), _less(l), _equal(e), _alloc(alloc)
			{ _link_root_min_max(); }

			iterator _begin(void)
			{ return iterator(_min.parent); }
			
			const_iterator _begin(void) const
			{ return const_iterator(_min.parent); }

			iterator _end(void)
			{ return iterator( const_cast<node *>(&_max) ); }

			const_iterator _end(void) const
			{ return const_iterator( const_cast<node *>(&_max) ); }

			reverse_iterator _rend(void)
			{ return reverse_iterator( iterator(_min.parent) ); }

			const_reverse_iterator _rend(void) const
			{ return const_reverse_iterator( const_iterator(_min.parent) ); }

			reverse_iterator _rbegin(void)
			{ return reverse_iterator( iterator(&_max) ); }

			const_reverse_iterator _rbegin(void) const
			{ return const_reverse_iterator( const_iterator( const_cast<node *>(&_max) ) ); }

			iterator _find(value_type const& val)
			{ return iterator(_find_by_val(val, _root)); }

			const_iterator _find(value_type const& val) const
			{ return const_iterator(_find_by_val(val, _root)); }

			node *_find_by_val(value_type const& val, node *curr)
			{
				if (curr == NULL || curr->color == _color::max || curr->color == _color::min)
					return &_max;
				if (_equal(val, *curr->data))
					return curr;
				if (_less(val, *curr->data))
					return _find_by_val(val, curr->left);
				return _find_by_val(val, curr->right);
			}

			void _erase_node(node *n)
			{
				if (_count_child(n) == 0)
					_relink_parent(n, NULL);
				else if (_count_child(n) == 1)
				{
					node *tmp = n->right == NULL ? n->left : n->right;
					_relink_parent(n, tmp);
					_balance_tree(tmp);
				}
				else
				{
					node *min = _get_min(n->right);
					_swap_nodes(n, min);
					_balance_tree(n->parent);
				}

				_alloc.destroy(n->data);
				_alloc.deallocate(n->data, 1);
				delete n;
			}

			int _count_child(node *n)
			{
				if (n->left == NULL && n->right == NULL)
					return 0;
				if (n->left != NULL && n->right != NULL)
					return 2;
				return 1;
			}

			node *_get_min(node * n)
			{
				if (n != NULL)
				{
					while (n->left != NULL)
						n = n->left;
				}
				return n;
			}

			void _swap_nodes(node *n1, node *n2)
			{
				node *tmp;
				node **n1_ptr = _get_ptr_to_node(n1);
				node **n2_ptr = _get_ptr_to_node(n2);

				tmp = n1->parent;
				n1->parent = n2->parent;
				n2->parent = tmp;

				if (n1_ptr != NULL)
					*n1_ptr = n2;
				else
					_root = n2;
				if (n2_ptr != NULL)
					*n2_ptr = n1;
				else
					_root = n1;

				tmp = n1->left;
				n1->left = n2->left;
				n2->left = tmp;

				tmp = n1->right;
				n1->right = n2->right;
				n2->right = tmp;

				char color = n1->color;
				n1->color = n2->color;
				n2->color = color;
			}

			node **_get_ptr_to_node(node *n)
			{
				if (n->parent == NULL)
					return NULL;
				if (n->_is_right())
					return &n->parent->right;
				return &n->parent->left;
			}

			void _relink_parent(node *_old, node *_new)
			{
				if (_old->parent == NULL)
					_root = _new;
				else if (_old->_is_right())
					_old->parent->right = _new;
				else
					_old->parent->left = _new;
				if (_new != NULL)
					_new->parent = _old->parent;
			}

			void _insert_by_val(value_type const& val)
			{
				if (_size == 0)
				{
					_insert_first_node(val);
					return;
				}

				pointer data = _alloc.allocate(1);
				_alloc.construct(data, val);

				node *child = new node(_color::red, NULL, NULL, NULL, data);
				node *parent = _get_pos_for_insert(val, _root);

				if (parent->color == _color::min || parent->color == _color::max)
					parent = parent->parent;
				if (_less(val, *parent->data))
				{
					child->left = parent->left;
					parent->left = child;
					if (child->left != NULL)
						child->left->parent = child;
				}
				else
				{
					child->right = parent->right;
					parent->right = child;
					if (child->right != NULL)
						child->right->parent = child;
				}
				child->parent = parent;
				_size++;

				_balance_tree(child);
			}

			void _insert_first_node(value_type const& val)
			{
				pointer data = _alloc.allocate(1);
				_alloc.construct(data, val);

				node *n = new node(_color::black, _root, &_min, &_max, data);

				_root = n;

				_min.parent = n;
				_max.parent = n;

				_min.left = NULL;
				_min.right = NULL;
				_max.left = NULL;
				_max.right = NULL;

				_size = 1;
			}

			void _balance_tree(node *child)
			{
				if (child->parent == NULL || child->parent->color == _color::black)
					return ;

				node *parent = child->parent;
				node *uncle = _get_uncle(child);
				node *grandpa = _get_grandpa(child);

				if (uncle != NULL && uncle->color == _color::red)
				{
					parent->color = _color::black;
					uncle->color = _color::black;
					if (grandpa->parent != NULL)
						grandpa->color = _color::red;
					_balance_tree(grandpa);
					return ;
				}

				if (child->_is_right() != parent->_is_right())
				{
					child->_is_right() ? _rotate_left(parent) : _rotate_right(parent);
					child = parent;
					parent = child->parent;
				}

				child->_is_right() ? _rotate_left(grandpa) : _rotate_right(grandpa);
				parent->color = _color::black;
				grandpa->color = _color::red;
			}

			void _rotate_right(node *n)
			{
				node *pivot = n->left;

				pivot->parent = n->parent;
				_relink_parent(n, pivot);

				n->left = pivot->right;
				if (pivot->right != NULL)
					pivot->right->parent = n;

				pivot->right = n;
				n->parent = pivot;
			}

			void _rotate_left(node *n)
			{
				node *pivot = n->right;

				pivot->parent = n->parent;
				if (n->parent != NULL)
				{
					if (n->_is_right())
						n->parent->right = pivot;
					else
						n->parent->left = pivot;
				}
				else
					_root = pivot;

				n->right = pivot->left;
				if (n->right != NULL)
					n->right->parent = n;

				pivot->left = n;
				n->parent = pivot;
			}

			node *_get_grandpa(node *curr)
			{
				if (curr != NULL && curr->parent != NULL)
					return curr->parent->parent;
				return NULL;
			}

			node *_get_uncle(node *curr)
			{
				node *grandpa = _get_grandpa(curr);

				if (grandpa != NULL)
				{
					if (curr->parent->_is_right())
						return grandpa->left;
					return grandpa->right;
				}
				return NULL;
			}

			node *_get_pos_for_insert(T const& val, node *curr)
			{
				if (curr->left == NULL && curr->right == NULL)
					return curr;
				if ( _less(val, *curr->data) )
				{
					if (curr->left == NULL)
						return curr;
					return _get_pos_for_insert(val, curr->left);
				}
				if (curr->right != NULL)
					return _get_pos_for_insert(val, curr->right);
				else
					return curr;
			}

			void _link_root_min_max(void)
			{
				_min.right = &_max;
				_max.left = &_min;

				_min.parent = &_max;
				_max.parent = &_min;

				_min.color = _color::min;
				_max.color = _color::max;
			}
   
	}; // class _rb_tree

}; // namespace ft

#endif
