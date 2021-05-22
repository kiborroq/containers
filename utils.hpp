/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 10:09:38 by kiborroq          #+#    #+#             */
/*   Updated: 2021/05/23 00:13:54 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <limits>

namespace ft
{

	/*
	**Swap implementation
	*/

	template <typename T>
	void swap(T & first, T & second)
	{
		T tmp = first;
		first = second;
		second = tmp;
	}


	/*
	**Binary functions implementation
	*/

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
		{
			ft::less<T> _less;
			if (_less(x, y) == false && _less(y, x) == false)
				return true;
			return false;
		}
	};


	/*
	**Pair implementation
	*/

	template <typename Pair>
	struct _pair_first_comp : ft::binary_function<Pair, Pair, bool>
	{
		bool operator()(Pair x, Pair y) const
		{ ft::less<typename Pair::first_type> _less; return _less(x.first, y.first); }
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
	
	
	/*
	**Red/Black tree with own iterator implementation for map/multimap and set/multiset
	*/

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

		bool _is_child(_rb_node *parent)
		{ return parent->left == this || parent->right == this; }

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

	template < typename T, typename Alloc = std::allocator<T>, typename Less = ft::less<T> >
	class _rb_tree
	{
		public:
			typedef T									value_type;
			typedef Alloc								allocator_type;
			typedef value_type &						reference;
			typedef Less								compare_less;
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
			allocator_type _alloc;

		public:
			explicit _rb_tree(compare_less const& l = compare_less(),
				allocator_type const& alloc = allocator_type())
				: _size(0), _root(NULL), _min(node()), _max(node()), _less(l), _alloc(alloc)
			{ _link_root_min_max(); }

			template <typename InputIterator>
			_rb_tree (InputIterator first, InputIterator last,
				compare_less const& l = compare_less(),
				allocator_type const& alloc = allocator_type())
				: _size(0), _root(NULL), _min(node()), _max(node()), _less(l), _alloc(alloc)
			{
				_link_root_min_max();
				_insert(first, last);
			}

			_rb_tree(_rb_tree const& tree)
				: _size(0), _root(NULL), _min(node()), _max(node()), _less(tree._less), _alloc(tree._alloc)
			{
				_link_root_min_max();
				_insert(tree._begin(), tree._end());
			}

			~_rb_tree(void)
			{ _clear(); }

			_rb_tree operator=(_rb_tree const& tree)
			{
				if (_size > 0)
					_clear();
				_insert(tree._begin(), tree._end());
				return *this;
			}

			/*
			**Member functions - ITERATORS
			*/

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

			/*
			**Member functions - CAPASITY
			*/	

			size_type _max_size(void) const
			{
				return std::numeric_limits<difference_type>::max() / (sizeof(node) + sizeof(value_type));
			}

			/*
			**Member functions - MODIFIERS
			*/

			iterator _insert(value_type const& val)
			{
				if (_size == 0)
					return _insert_first_node(val);
				if (_less(val, *_min.parent->data))
					return _insert_by_val(val, _min.parent);
				if (!_less(val, *_max.parent->data))
					return _insert_by_val(val, _max.parent);
				return _insert_by_val(val, _root);
			}

			template <typename InputIterator>
			void _insert(InputIterator first, InputIterator last)
			{
				while (first != last)
					_insert(*first++);
			}

			size_type _erase(value_type const& v)
			{
				size_type num = 0;
				iterator pos = _find_lower(v, _root, _root);
				
				while (pos != _end() && pos._tree != NULL && _equal_to(*pos._tree->data, v))
				{
					num++;
					_erase(pos++);
				}
				return num;
			}

			void _erase(iterator position)
			{ _erase_node(position._tree); }

			void _erase(iterator first, iterator last)
			{
				while (first != last)
					_erase(first++);				
			}

			void _clear(void)
			{ _erase(_begin(), _end()); }

			void _swap(_rb_tree & tree)
			{
				if (_size > 0)
				{
					this->_min.parent->left = &tree._min;
					tree._min.parent->left = &this->_min;

					this->_max.parent->right = &tree._max;
					tree._max.parent->right = &this->_max;

					ft::swap(this->_min.parent, tree._min.parent);
					ft::swap(this->_max.parent, tree._max.parent);
					ft::swap(this->_size, tree._size);
					ft::swap(this->_less, tree._less);
					ft::swap(this->_alloc, tree._alloc);
				}
			}

			/*
			**Member functions - OPERATIONS
			*/

			iterator _find(value_type const& val)
			{ return iterator(_find_by_val(val, _root)); }

			const_iterator _find(value_type const& val) const
			{ return const_cast<node *>( _find_by_val(val, _root) ); }

			size_type _count(value_type const& val) const
			{
				size_type num = 0;
				const_iterator it = const_cast<node *>( _find_lower(val, _root, _root));

				if (it._tree == NULL)
					return num;

				while (it != _end()	&& _equal_to(*it._tree->data, val))
				{
					num++;
					it++;
				}
				return num;				
			}

			iterator _lower_bound(value_type const& val)
			{ return iterator(_find_lower(val, _root, _root)); }

			const_iterator _lower_bound(value_type const& val) const
			{ return iterator(_find_lower(val, _root, _root)); }

			iterator _upper_bound(value_type const& val)
			{ return iterator(_find_upper(val)); }

			const_iterator _upper_bound(value_type const& val) const
			{ return iterator(_find_upper(val)); }

			/*
			**Selfmember functions - COMPARES
			*/

			bool _equal_to(value_type const& x, value_type const& y) const
			{
				if (_less(x, y) == false && _less(y, x) == false)
					return true;
				return false;
			}

		private:
			/*
			**Help functions - INNERS
			*/

			node *_find_by_val(value_type const& val, node *curr) const
			{
				if (curr == NULL
					|| curr->color == _color::min
					|| curr->color == _color::max)
					return NULL;
				if (_equal_to(val, *curr->data))
					return curr;
				if (_less(val, *curr->data))
					return _find_by_val(val, curr->left);
				return _find_by_val(val, curr->right);
			}

			node *_find_lower(value_type const& val, node *curr, node *graet) const
			{
				if (curr == NULL
					|| curr->color == _color::min
					|| curr->color == _color::max)
					return graet;
				if (_equal_to(val, *curr->data) ||
					_less(val, *curr->data))
					return _find_lower(val, curr->left, curr);
				return _find_lower(val, curr->right, graet);
			}

			node *_find_upper(value_type const& val) const
			{
				const_iterator lower = _find_lower(val, _root, _root);

				while (lower != _end() && _equal_to(*lower._tree->data, val))
					lower++;
				return lower._tree;				
			}

			iterator _insert_by_val(value_type const& val, node *start)
			{
				pointer data = _alloc.allocate(1);
				_alloc.construct(data, val);

				node *child = new node(_color::red, NULL, NULL, NULL, data);
				node *parent = _get_pos_for_insert(val, start);

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

				_balance_after_insert(child);
				return iterator(child);
			}

			void _erase_node(node *n)
			{
				if (_size == 1)
					_link_root_min_max();
				else if (_count_child(n) == 0)
				{
					node **ptr = _get_ptr_to_node(n);
					if (n->left == &_min)
					{
						*ptr = &_min;
						_min.parent = n->parent;
					}
					else if (n->right == &_max)
					{
						*ptr = &_max;
						_max.parent = n->parent;
					}
					else
						*ptr = NULL;
					if (n->color == _color::black)
						_balance_after_erase(n->parent, _get_son(n->parent));
				}
				else if (_count_child(n) == 1)
				{
					node *tmp = (n->right == NULL || n->right == &_max) ? n->left : n->right;

					_relink_parent(n, tmp);
					if (n->left == &_min)
					{
						tmp->left = &_min;
						_min.parent = tmp;
					}
					else if (n->right == &_max)
					{
						tmp->right = &_max;
						_max.parent = tmp;
					}
					tmp->color = _color::black;
				}
				else
				{
					node *min = _get_max(n->left);

					_swap_nodes(n, min);
					_erase_node(n);
					return ;
				}

				_alloc.destroy(n->data);
				_alloc.deallocate(n->data, 1);
				delete n;

				_size--;
			}

			int _count_child(node *n)
			{
				if ((n->left == NULL || n->left == &_min) && (n->right == NULL || n->right == &_max))
					return 0;
				if (n->left != NULL && n->left != &_min && n->right != NULL && n->right != &_max)
					return 2;
				return 1;
			}

			node *_get_max(node * n)
			{
				if (n != NULL && n != &_max)
				{
					while (n->right != NULL && n->left != &_max)
						n = n->right;
				}
				return n;
			}

			void _swap_nodes(node *n1, node *n2)
			{
				if (n2->_is_child(n1))
					_swap_parent_child(n1, n2);
				else if (n1->_is_child(n2))
					_swap_parent_child(n2, n1);
				else
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
				}
				if (n1->left != NULL)
					n1->left->parent = n1;
				if (n1->right != NULL)
					n1->right->parent = n1;

				if (n2->left != NULL)
					n2->left->parent = n2;
				if (n2->right != NULL)
					n2->right->parent = n2;

				char color = n1->color;
				n1->color = n2->color;
				n2->color = color;
			}

			void _swap_parent_child(node *parent, node *child)
			{
				node *tmp;
				node **parent_ptr = _get_ptr_to_node(parent);

				if (parent_ptr != NULL)
					*parent_ptr = child;
				else
					_root = child;
				child->parent = parent->parent;
				parent->parent = child;

				tmp = parent->left;
				parent->left = child->left;
				child->left = tmp == child ? parent : tmp;

				tmp = parent->right;
				parent->right = child->right;
				child->right = tmp == child ? parent : tmp;
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

			iterator _insert_first_node(value_type const& val)
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

				return iterator(n);
			}

			void _balance_after_insert(node *child)
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
					{
						grandpa->color = _color::red;
						_balance_after_insert(grandpa);
					}
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

			void _balance_after_erase(node *parent, node * son)
			{
				if (parent == NULL)
					return ;

				node *one_side_grandson = son->_is_right() ? son->right : son->left;
				node *oppos_grandson = son->_is_right() ? son->left : son->right;

				if (parent->color == _color::red)
				{
					if (one_side_grandson != NULL && one_side_grandson->color == _color::red)
					{
						_small_rotate(parent, son);
						parent->color = _color::black;
						son->color = _color::red;
						one_side_grandson->color = _color::black;
					}
					else if (oppos_grandson != NULL && oppos_grandson->color == _color::red)
					{
						_greate_rotate(parent, son);
						parent->color = _color::black;
					}
					else
					{
						parent->color = _color::black;
						son->color = _color::red;
					}
				}
				else if (son->color == _color::red)
				{
					_small_rotate(parent, son);
					parent->color = _color::red;
					son->color = _color::black;
					_balance_after_erase(parent, oppos_grandson);
				}
				else
				{
					if (one_side_grandson != NULL && one_side_grandson->color == _color::red)
					{
						_small_rotate(parent, son);
						one_side_grandson->color = _color::black;
					}
					else if (oppos_grandson != NULL && oppos_grandson->color == _color::red)
					{
						_greate_rotate(parent, son);
						oppos_grandson->color = _color::black;
					}
					else
					{
						son->color = _color::red;
						if (parent->parent != NULL)
							_balance_after_erase(parent->parent, _get_brother(parent));
					}
				}
			}

			void _small_rotate(node *parent, node *son)
			{
				if (son->_is_left())
					_rotate_right(parent);
				else
					_rotate_left(parent);
			}

			void _greate_rotate(node *parent, node *son)
			{
				if (son->_is_left())
				{
					_rotate_left(son);
					_rotate_right(parent);
				}
				else
				{
					_rotate_right(son);
					_rotate_left(parent);
				}
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

			node *_get_son(node *n)
			{
				if (n == NULL)
					return NULL;
				if (n->left != NULL && n->left != &_min)
					return n->left;
				if (n->right != NULL && n->right != &_max)
					return n->right;
				return NULL;
			}

			node *_get_brother(node *n)
			{
				if (n == NULL || n->parent == NULL)
					return NULL;
				if (n->_is_right())
					return n->parent->left == &_min ? NULL: n->parent->left;
				return  n->parent->right == &_max ? NULL : n->parent->right;
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
				_root = NULL;	

				_min.right = &_max;
				_max.left = &_min;

				_min.parent = &_max;
				_max.parent = &_min;

				_min.color = _color::min;
				_max.color = _color::max;
			}

	}; // class _rb_tree

}; // namespace ft

#endif // UTILS_HPP
