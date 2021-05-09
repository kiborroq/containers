/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 11:24:36 by kiborroq          #+#    #+#             */
/*   Updated: 2021/05/08 23:34:46 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <memory>
#include <vector>
#include "map_iterator.hpp"
// #include "vector.hpp"
#include <iostream>
#include <iterator>
// #include "randomaccesiterator.hpp"

// int main(void)
// {
	// int n[3] = {3, 2, 1};
	// ft::normal_iterator<int> it1;
	// it1 = n;
	// ft::normal_iterator<int> it2 = it1;
	// ft::normal_iterator<int> it3(it1);
	// // std::vector<int>::iterator::iterator_category;
	// std::cout << "*it1=" << *it1 << std::endl;
	// std::cout << "*it2=" << *it2 << std::endl;
	// std::cout << "*it3=" << *it3 << std::endl;
	// std::cout << "it3-it1=" << it3 - it1 << std::endl;
	// std::cout << "it1[1]=" << it1[1] << std::endl;
	// std::cout << "*(it2 + 1)=" << *(it2 + 1) << std::endl;
	// it3 += 2;
	// std::cout << "*it3=" << *it3 <<std::endl;
	// std::cout << "*it1=" << *it1 <<std::endl;
	// std::cout << "*(it3 - 1)=" << *(it3 - 1) << std::endl;
	// std::cout << std::boolalpha;
	// std::cout << "it3 == it2 " << (it3 == it2) << std::endl;
	// std::cout << "it3 < it2 " << (it3 < it2) << std::endl;
	// std::cout << "it1 == it2 " << (it1 == it2) << std::endl;
	// std::cout << "it3 > it2 " << (it3 > it2) << std::endl;


	// ft::reverse_iterator< ft::normal_iterator<int> > rit1 = 1 + it3;
	// ft::reverse_iterator< ft::normal_iterator<int> > rit2(rit1);
	// std::cout << "*rit2=" << *rit2 << std::endl;
	// std::cout << "*rit1=" << *rit1 << std::endl;
	// std::cout << "*rit1.base()=" << *rit1.base() << std::endl;
	// std::cout << "*rit1++=" << *rit1++ << std::endl;
	// std::cout << "*rit1=" << *rit1 << std::endl;
	// std::cout << "*(++rit1)=" << *(++rit1) << std::endl;
	// std::cout << "rit1-rit2=" << rit1 - rit2 << std::endl;
	// std::cout << "rit1 < rit2 " << (rit1 < rit2) << std::endl;
	// std::cout << "rit1 == rit2 " << (rit1 == rit2) << std::endl;
	// std::cout << "rit1 > rit2 " << (rit1 > rit2) << std::endl;

// 	std::vector<int> myvector;
// 	myvector.resize

//   // set some initial content:
//   	for (int i=1;i<10;i++) myvector.push_back(i);
	
// 	std::vector<int> v1(20, myvector.begin(), myvector.end());

// 	std::vector<int>::iterator first = v1.begin();
// 	std::vector<int>::iterator last = v1.end();
// 	while (first != last)
// 		std::cout << *first++ << " ";
// 	std::cout << std::endl;
// 	// std::vector<int>::const_reverse_iterator it4(n + 1);
// 	// std::cout << "*it4=" << *it4 << std::endl;
// 	// std::cout << "*it4=" << *it4 << std::endl;
// 	return (0);
// }

#include <iostream>
#include "vector.hpp"
#include <algorithm>
#include <list>
#include <stack>
#include <map>
#include <iomanip>

class Human
{
	private:
		std::string name;
		unsigned int age;
	public:
		
		Human(void) : name(std::string()), age(int()) { std::cout << "I was born! Defualt" << std::endl; }
		Human(std::string const & n, unsigned int a) : name(n), age(a) { std::cout << "I was born! Fill" << std::endl; }
		~Human(void) { }
		bool operator<(Human const & h) const { return(this->age < h.getAge()); }
		bool operator>(Human const & h) const { return(this->age > h.getAge()); }
		bool operator==(Human const & h) const { return(this->age == h.getAge()); }
		unsigned int getAge(void) const { return (age); }
		std::string getName(void) const { return (name); }
};

std::ostream & operator<<(std::ostream & out, Human const & h) 
{
	out << h.getName() << " " << h.getAge();
	return (out);
}
struct _color { static const char RED = 0; char static const BLACK = 1; static const char MIN = 4; static const char MAX = 3; };

template <typename T>
void print_tree(ft::_rb_tree<T> const & tr)
{
	std::cout << "direct: ";
	typedef typename ft::_rb_tree<T>::const_iterator iterator;
	for (iterator begin = tr._begin(); begin != tr._end(); begin++)
		std::cout << *begin << " ";
	std::cout << std::endl;

	std::cout << "revers: ";
	typedef typename ft::_rb_tree<T>::const_reverse_iterator reverse_iterator;
	for (reverse_iterator begin = tr._rbegin(); begin != tr._rend(); begin++)
		std::cout << *begin << " ";
	std::cout << std::endl;
}

template <typename T>
void print_tree(T begin, T end)
{
	while (begin != end)
		std::cout << *begin++ << " ";
	std::cout << std::endl;
}

int get_random_val(int)
{
	return -500 + rand() % 1000;
}

int main ()
{

// std::vector<int> foo (20,-100);   // three ints with a value of 100
//   std::vector<int> bar (40,-100);   // five ints with a value of 200

//   std::cout << "foo contains:";
//   for (unsigned i=0; i<foo.size(); i++)
//     std::cout << ' ' << foo[i];
//   std::cout << '\n';

//   std::cout << "bar contains:";
//   for (unsigned i=0; i<bar.size(); i++)
//     std::cout << ' ' << bar[i];
//   std::cout << '\n';

//   std::cout << std::boolalpha << "foo > bar " << (foo > bar) << std::endl;
//   std::cout << std::boolalpha << "foo < bar " << (foo < bar) << std::endl;
//   std::vector<int> myvector;

//   // set some values (from 1 to 10)
//   for (int i=1; i<=10; i++) myvector.push_back(i);

//   std::cout << "myvector contains:";
//   for (unsigned i=0; i<myvector.size(); ++i)
//     std::cout << ' ' << myvector[i];
//   std::cout << '\n';
//   std::cout << "size: " << myvector.size() << '\n';
//   std::cout << "capacity: " << myvector.capacity() << '\n';
//   std::cout << "max_size: " << myvector.max_size() << '\n';
//   // erase the 6th element
//   myvector.erase (myvector.begin()+5);

//   std::cout << "myvector contains:";
//   for (unsigned i=0; i<myvector.size(); ++i)
//     std::cout << ' ' << myvector[i];
//   std::cout << '\n';
//   std::cout << "size: " << myvector.size() << '\n';
//   std::cout << "capacity: " << myvector.capacity() << '\n';
//   std::cout << "max_size: " << myvector.max_size() << '\n';
//   // erase the first 3 elements:
//     std::vector<int>::iterator it1;
//    it1 = myvector.erase (myvector.begin(),myvector.begin()+3);

// 	std::cout << "it1=" << *it1 << std::endl;

//   std::cout << "myvector contains:";
//   for (unsigned i=0; i<myvector.size(); ++i)
//     std::cout << ' ' << myvector[i];
//   std::cout << '\n';
//   std::cout << "size: " << myvector.size() << '\n';
//   std::cout << "capacity: " << myvector.capacity() << '\n';
//   std::cout << "max_size: " << myvector.max_size() << '\n';

// //   myvector.erase(myvector.end());
//   std::vector<int> v1;
//   v1.pop_back();

	// int *arr = new int[] {1, 2, 3, 4, 5};

	// std::list

	// std::list<int> l1;
	// std::list<int>::reverse_iterator r1 = l1.rbegin();
	// std::list<int>::reverse_iterator r2 = l1.rend();

	// std::cout << "|" << *r1 << "|\n";
	// std::cout << "|" << *r2 << "|\n";

	// while (r1 != r2)
	// {
	// 	std::cout << *r1 << " ";
	// 	r1++;
	// }
	// std::cout << std::endl;

	// std::list<Human> hl(1);
	// std::list<Human>::iterator rl = hl.begin();
	// std::cout << *rl << std::endl;

	// node n(145, nullptr, nullptr);
	// std::cout << n.data << std::endl;

//   std::list<int> l1;
//   l1.push_back(1);
//   l1.push_back(3);
//   l1.push_back(5);
//   l1.push_back(7);
//   l1.push_back(9);
//   l1.push_back(11);
//   l1.push_back(13);
//   l1.push_back(22);

//   std::list<int> l2;
//   l2.push_back(2);
//   l2.push_back(3);
//   l2.push_back(6);
//   l2.push_back(8);
//   l2.push_back(10);
//   l2.push_back(12);
//   l2.push_back(14);
//   l2.reverse();


//   l1.merge(l2);
//   std::list<int>::iterator it;

//   // set some initial values:
//   for (int i=1; i<=5; ++i) mylist.push_back(i); // 1 2 3 4 5

//   it = mylist.begin();
//   ++it;       // it points now to number 2           ^

//   mylist.insert (it,10);                        // 1 10 2 3 4 5

//   // "it" still points to number 2                      ^
//   mylist.insert (it,2,20);                      // 1 10 20 20 2 3 4 5
//   mylist.insert (it,10);                        // 1 10 2 3 4 5


//   --it;       // it points now to the second 20            ^

//   std::list<int> l;
//   std::cout << std::boolalpha << (l.begin() == l.end()) << std::endl;
//   l.insert(l.begin(), 5, -55);
//     std::cout << l.size() << std::endl;
// 	// l.erase(l.end());
//     // std::cout << l.size() << std::endl;
// //   l.insert(l.begin(), 10, -555);
//                                                 // 1 10 20 30 30 20 2 3 4 5
//                                                 //               ^
// 	mylist.push_front(2);
// 	mylist.push_front(3);
// 	mylist.push_front(4);
//   std::cout << "mylist contains:";
//   for (it=l1.begin(); it!=l1.end(); ++it)
//     std::cout << ' ' << *it;
//   std::cout << '\n';

//   mylist.unique();
//   std::cout << "mylist contains:";
//   for (it=mylist.begin(); it!=mylist.end(); ++it)
//     std::cout << ' ' << *it;
//   std::cout << '\n';

	// std::map<int, int> tree;
	// tree.insert(std::make_pair(155, 155));
	// tree.insert(std::make_pair(105, 105));
	// std::map<int, int>::iterator it;

	srand(time(NULL));

	ft::_rb_tree<int> tree;

	int count = 10000;
	std::vector<int> nums;

	while (count-- > 0)
	{
		int num = get_random_val(int());
		tree._insert(num);
		nums.push_back(num);
	}
	
	std::cout << tree._size << std::endl;
	std::cout << nums.size() << std::endl;

	// print_tree(tree);

	ft::_rb_tree<int>::iterator tree_it;
	std::vector<int>::iterator vec_it;

	while (nums.size() > 0)
	{
		int idx = 0 + rand() % nums.size();
		tree_it = tree._find(nums.at(idx));
		tree._erase_node(tree_it._tree);
		vec_it = std::find(nums.begin(), nums.end(), nums.at(idx));
		nums.erase(vec_it);

		// print_tree(tree);
	}

	count = 100;
	while (count-- > 0)
	{
		int num = get_random_val(int());
		tree._insert(num);
		nums.push_back(num);
	}

	while (nums.size() > 0)
	{
		int idx = 0 + rand() % nums.size();
		tree_it = tree._find(nums.at(idx));
		tree._erase_node(tree_it._tree);
		vec_it = std::find(nums.begin(), nums.end(), nums.at(idx));
		nums.erase(vec_it);

		// print_tree(tree);
	}

	// char c = _color::BLACK;

	// std::map<Human, Human> m;
	// std::map<Human, Human>::iterator it = m.begin();
	// std::cout << it._M_node->_M_color << std::endl;
	// m[Human()] = Human();

	// *it;
	// it++;
	// it++;
	// it++;
	// it++;
	// it++;
	// it++;
	// it++;
	// it++;
	// it++;
	// std::cout << std::boolalpha << (it == m.begin()) << std::endl;
	// std::cout << sizeof(c) << std::endl;
	return 0;
}

// int main ()
// {
//   std::vector<int> v1;
//   std::vector<int> v2;
// //   std::cout << "size: " << v1.size() << '\n';
// //   std::cout << "capacity: " << v1.capacity() << '\n';
// //   std::cout << "max_size: " << v1.max_size() << '\n';
//   // set some content in the vector:
//   for (int i=1; i<=15; i++) v1.push_back(i);
//   for (int i=-1; i>=-25; i--) v2.push_back(i);


// 	// std::allocator<int> al;

// //   std::cout << al.max_size() << std::endl;
// //   std::cout << v1.max_size() << std::endl;

//   std::vector<int>::iterator it1 = v1.begin() + 2;
//   std::vector<int>::iterator it2 = v1.begin() + 3;
  
// 	std::vector<int>::iterator it3 = v2.begin();
//   std::vector<int>::iterator it4 = v2.end();


// //   v1.insert(it3, it1, it2);
//   for (std::vector<int>::iterator beg = v1.begin() ; beg != v1.end(); beg++) std::cout << *beg << " ";
//   std::cout << std::endl;

//   std::cout << "size: " << v1.size() << '\n';
//   std::cout << "capacity: " << v1.capacity() << '\n';
//   std::cout << "max_size: " << v1.max_size() << '\n';
// 	v1.assign(it3, it4);
//   for (std::vector<int>::iterator beg = v1.begin() ; beg != v1.end(); beg++) std::cout << *beg << " ";
//   std::cout <<  std::endl;
//   std::cout << "size: " << v1.size() << '\n';
//   std::cout << "capacity: " << v1.capacity() << '\n';
//   std::cout << "max_size: " << v1.max_size() << '\n';

//   	v1.erase(it1, it2);
//   for (std::vector<int>::iterator beg = v1.begin() ; beg != v1.end(); beg++) std::cout << *beg << " ";
//   std::cout <<  std::endl;
//   std::cout << "size: " << v1.size() << '\n';
//   std::cout << "capacity: " << v1.capacity() << '\n';
//   std::cout << "max_size: " << v1.max_size() << '\n';
//   return 0;
// }

// // #include <iostream>     // std::cout
// // #include <iterator>     // std::reverse_iterator
// // #include <vector>       // std::vector

// // int main () {
// //   std::vector<int> myvector;
// //   for (int i=10; i<30; i++) myvector.push_back(i);

// //   typedef std::vector<int>::iterator iter_type;
// // 														 // ? 0 1 2 3 4 5 6 7 8 9 ?
// //   iter_type from (myvector.begin());                     //   ^
// // 	from++;	
// //   std::cout << "from=" << *from << std::endl;								 //         ------>
// //   iter_type until (myvector.end());                      //                       ^
// //   std::cout << "until=" << *until << std::endl;
// // 														 //
// //   std::reverse_iterator<iter_type> rev_until (from);
// // //   rev_until-=1;     // ^
// //   std::cout << "rev_until=" << *rev_until << std::endl;
// //   std::cout << "rev_until.base()=" << *rev_until.base() << std::endl;

// // 														 //         <------
// //   std::reverse_iterator<iter_type> rev_from (until);     //                     ^
// //   std::cout << "rev_from=" << *rev_from << std::endl;
// //   std::cout << "rev_from.base()=" << *rev_from.base() << std::endl;


// // 	std::cout << std::boolalpha << (from == until) << " " << (from < until) << " " << (from > until) << std::endl;


// //   std::cout << "myvector:";
// //   while (from != until)
// // 	std::cout << ' ' << *from++;
// //   std::cout << '\n';

// // 	std::cout << "rev_from[3]=" << rev_from[3] << std::endl;
// // 	std::cout << "rev_until[3]=" << rev_until[-3] << std::endl; 

// // 	std::cout << std::boolalpha << (from == until) << " " << (from < until) << " " << (from > until) << std::endl;

// // 	std::cout << from->operator+(5);

// //   return 0;
// // }


// #include <iostream>     // std::cout
// #include <iterator>     // std::reverse_iterator
// #include <utility>      // std::make_pair
// #include <map>          // std::map
// #include <string>       // std::string

// int main () {
//   std::map<int,std::string> numbers;
//   numbers.insert (std::make_pair(1,"one"));
//   numbers.insert (std::make_pair(2,"two"));
//   numbers.insert (std::make_pair(3,"three"));

//   typedef std::map<int,std::string>::iterator map_iter;

//   std::reverse_iterator<map_iter> rev_end (numbers.begin());

//   std::reverse_iterator<map_iter> rev_iterator (numbers.end());

//   for ( ; rev_iterator != rev_end ; ++rev_iterator )
//     std::cout << rev_iterator->first << ' ' << rev_iterator->second << '\n';

//   return 0;
// }