/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 20:41:55 by kiborroq          #+#    #+#             */
/*   Updated: 2021/04/19 19:19:49 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "random_access_iterator.hpp"
# include <memory>
# include <stdexcept>
# include <cstddef>

namespace ft
{
	template < typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T										value_type;
			typedef Alloc									allocator_type;
			typedef value_type &							reference;
			typedef value_type const&						const_reference;
			typedef value_type * 							pointer;
			typedef value_type const*						const_pointer;
			typedef ptrdiff_t								difference_type;
			typedef size_t									size_type;
			typedef _normal_iterator<value_type>			iterator;
			typedef _normal_iterator<const value_type>		const_iterator;
			typedef _reverse_iterator<iterator>				reverse_iterator;
			typedef _reverse_iterator<const_iterator>		const_reverse_iterator;

		private:
			size_type _cap;
			size_type _size;

		protected:
			allocator_type	_alloc;
			pointer			_v;

		public:
			explicit vector(allocator_type const& alloc = allocator_type())
				: _cap(0), _size(_cap), _alloc(alloc), _v(_alloc.allocate(_cap))
			{ return; }

			explicit vector(size_type n, value_type const& val = value_type(),
				allocator_type const& alloc = allocator_type())
				: _cap(0), _size(0), _alloc(alloc), _v(NULL)
			{ insert(end(), n, val); }

			template <typename InputIterator>
			vector (InputIterator first, InputIterator last,
				allocator_type const& alloc = allocator_type())
				: _cap(0), _size(0), _alloc(alloc), _v(NULL)
			{ insert(end(), first, last); }

			vector(vector const& x) : _cap(0), _size(0), _alloc(x._alloc), _v(NULL) { *this = x; }

			~vector(void) { _alloc.deallocate(_v, _cap); }

			vector & operator=(vector const& x)
			{
				assign(x.begin(), x.end());
				return *this;
			}


			/*
			**Member functions - ITERATORS
			*/

			iterator begin(void) { return _v; }
			iterator end(void) { return _v + _size; }
			const_iterator begin(void) const { return _v; }
			const_iterator end(void) const { return _v + _size; }
			reverse_iterator rbegin(void) { return iterator(_v + _size); }
			reverse_iterator rend(void) { return iterator(_v); }
			const_reverse_iterator rbegin(void) const { return const_iterator(_v + _size); }
			const_reverse_iterator rend(void) const { return const_iterator(_v); }			


			/*
			**Member functions - CAPACITY
			*/

			size_type size(void) const { return _size; }
			size_type max_size(void) const { return _alloc.max_size(); }
			size_type capacity(void) const { return _cap; }
			bool empty(void) const { return _size == 0; }
			
			void resize(size_type n, value_type val = value_type())
			{
				if (_size < n)
					insert(end(), n - _size, val);
				else if (_size > n)
					_destroy(_v + n, _size - n);
				_size = n;
			}

			void reserve (size_type n)
			{
				if (n > _cap)
				{
					if (n > _alloc.max_size())
						throw std::length_error("Length error!");

					pointer tmp = _v;
					size_type old_cap = _cap;

					_increase_cap(n);
					_v = _alloc.allocate(_cap);
					_fill_by(_v, _size, tmp);
					_destroy(tmp, _size);
					_alloc.deallocate(tmp, old_cap);
				}
			}


			/*
			**Member functions - ELEMENT ACCESS
			*/			

			reference operator[](size_type n) { return _v[n]; }
			const_reference operator[](size_type n) const { return _v[n]; }
			reference front(void) { return *_v; }
			const_reference front(void) const { return *_v; }
			reference back(void) { return _v[_size - 1]; }
			const_reference back(void) const { return _v[_size - 1]; }

			reference at(size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("Out of range!");
				return _v[n];
			}

			const_reference at(size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("Out of range!");
				return _v[n];
			}


			/*
			**Member functions - MODIFIERS
			*/

			template <typename InputIterator>
  			void assign(InputIterator first, InputIterator last)
			{
				if (_size > 0)
					clear();
				insert(begin(), first, last);
			}

			void assign(size_type n, value_type const& val)
			{
				if (_size > 0)
					clear();
				insert(begin(), n, val);
			}

			void push_back(value_type const& val) { insert(end(), val); }
			void pop_back(void) { if (_size > 0) erase(end() - 1); }
			void clear(void) { _destroy(_v, _size); _size = 0; }
			iterator erase(iterator position) { return erase(position, position + 1); }

			iterator erase(iterator first, iterator last)
			{
				if (last - first > 0)
				{
					pointer _curr = _v + (first - begin());

					_destroy(_curr, last - first);
					_shift_left(_curr, end() - last, last - first);
				}
				return (first);
			}

			iterator insert(iterator position, value_type const& val)
			{
				insert(position, static_cast<size_type>(1), val);
				return position;
			}

			void insert(iterator position, size_type n, value_type const& val)
			{
				if (n > 0)
				{
					size_type to_pos = position - begin();

					reserve(_size + n);

					if (begin() + to_pos < end() && _size > 0)
						_shift_right(_v + _size - 1, _size - to_pos, n);

					_fill_by(_v + to_pos, n, val);

					_size += n;
				}
			}

			template <typename InputIterator>
    		void insert(iterator position, InputIterator first, InputIterator last)
			{
				size_type to_pos = position - begin();

				size_type n = ft::distance(first, last);

				if (n > 0)
				{
					pointer tmp = _alloc.allocate(n);
					_fill_by(tmp, first, last);

					reserve(_size + n);
			
					if (begin() + to_pos < end() && _size > 0)
						_shift_right(_v + _size - 1, _size - to_pos, n);
					_fill_by(_v + to_pos, n, tmp);

					_alloc.destroy(tmp);
					_alloc.deallocate(tmp, n);

					_size += n;
				}
			}

			void swap(vector & x)
			{
				pointer v_tmp = x._v;
				size_type size_tmp = x.size();
				size_type cap_tmp = x.size();

				x._v = _v;
				x._size = _size;
				x._cap = _cap;

				_v = v_tmp;
				_size = size_tmp;
				_cap = cap_tmp;
			}

			private:

				/*
				**Private member functions
				*/

				void _increase_cap(size_type n)
				{
					if (n > 0 && _cap == 0)
						_cap = 1;
					while (_cap < n)
						_cap <<= 1;
				}

				void _fill_by(pointer _dest, size_type n, value_type const& val)
				{
					while (n-- > 0)
						_alloc.construct(_dest++, val);
				}

				template <typename InputIterator>
				void _fill_by(pointer _dest, InputIterator first, InputIterator last)
				{
					while (first != last)
						_alloc.construct(_dest++, *first++);
				}

				void _fill_by(pointer _dest, size_type n, pointer _src)
				{
					while (n-- > 0)
						_alloc.construct(_dest++, *_src++);
				}

				void _destroy(pointer _p, size_type n)
				{
					while (n-- > 0)
						_alloc.destroy(_p++);
				}

				void _shift_right(pointer _p, size_type _count, size_type shift)
				{
					while (_count-- > 0)
					{
						_alloc.construct(_p + shift, *_p);
						_alloc.destroy(_p);
						_p--;
					}
				}

				void _shift_left(pointer _p, size_type _count, size_type shift)
				{
					while (_count-- > 0)
					{
						_alloc.construct(_p, _p[shift]);
						_alloc.destroy(_p + shift);
						_p++;
					}
					_size -= shift;
				}
	};


	/*
	**Non-member functions - OVERLOADS
	*/

	template <typename T, typename Alloc>
	void swap(vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }

	template <typename T, typename Alloc>
	bool operator==(vector<T,Alloc> const& lhs, vector<T,Alloc> const& rhs)
	{
		if (lhs.size() == rhs.size())
		{
			typedef typename vector<T, Alloc>::size_type size_type;

			size_type size = lhs.size();
			for (size_type i = 0; i < size; i++)
			{
				if (lhs[i] != rhs[i])
					return false;
			}
			return true;
		}
		else
			return false;
	}

	template <typename T, typename Alloc>
	bool operator!=(vector<T,Alloc> const& lhs, vector<T,Alloc> const& rhs) { return !(lhs == rhs); }

	template <typename T, typename Alloc>
	bool operator<(vector<T,Alloc> const& lhs, vector<T,Alloc> const& rhs)
	{
		typedef typename vector<T, Alloc>::size_type size_type;

		size_type size = lhs.size() < rhs.size() ? lhs.size() : rhs.size();
		for (size_type i = 0; i < size; i++)
		{
			if (lhs[i] < rhs[i])
				return true;
			else if (lhs[i] > rhs[i])
				return false;
		}
		return lhs.size() < rhs.size();
	}

	template <typename T, typename Alloc>
	bool operator>(vector<T,Alloc> const& lhs, vector<T,Alloc> const& rhs) { return !(lhs < rhs); }

	template <typename T, typename Alloc>
	bool operator<=(vector<T,Alloc> const& lhs, vector<T,Alloc> const& rhs) { return !(lhs > rhs); }

	template <typename T, typename Alloc>
	bool operator>=(vector<T,Alloc> const& lhs, vector<T,Alloc> const& rhs) { return !(lhs < rhs); }
};

#endif
