/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 19:30:50 by kiborroq          #+#    #+#             */
/*   Updated: 2021/05/23 13:50:32 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include "list.hpp"

#include <vector>
#include "vector.hpp"

#include <map>
#include "map.hpp"
#include "multimap.hpp"

#include <set>
#include "set.hpp"
#include "multiset.hpp"

#include <stack>
#include "stack.hpp"

#include <queue>
#include "queue.hpp"

#include "ForTests.hpp"

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <algorithm>

void vector_tests(void)
{
	print_container_header("VECTOR");

	print_type("INTEGER");
	VectorTests<int, std::vector<int>, ft::vector<int> > test1;
	test1.DoTests();
	std::cout << std::endl;

	// print_type("STRING");
	// VectorTests<std::string, std::vector<std::string>, ft::vector<std::string> > test2;
	// test2.DoTests();
	// std::cout << std::endl;

	// print_type("HUMAN");
	// VectorTests<Human, std::vector<Human>, ft::vector<Human> > test4;
	// test4.DoTests();
	// std::cout << std::endl;
}

void list_tests(void)
{
	print_container_header("LIST");

	print_type("INTEGER");
	ListTests<int, std::list<int>, ft::list<int> > test1;
	test1.DoTests();
	std::cout << std::endl;

	// print_type("HUMAN");
	// ListTests<Human, std::list<Human>, ft::list<Human> > test4;
	// test4.DoTests();
	// std::cout << std::endl;

}

void map_tests(void)
{
	print_container_header("MAP");

	print_type("INT-STR");
	MapSetTests<ft::map<int, std::string>, std::map<int, std::string>, int> test1;
	test1.DoTests();
	test1.accessOperator();
	std::cout << std::endl;

	// print_type("CHR-HUM");
	// MapSetTests<ft::map<char, Human>, std::map<char, Human>, char> test3;
	// test3.accessOperator();
	// test3.DoTests();
	// std::cout << std::endl;
}

void multimap_tests(void)
{
	print_container_header("MULTIMAP");

	print_type("INT-STR");
	MapSetTests<ft::multimap<int, std::string>, std::multimap<int, std::string>, int> test1;
	test1.DoTests();
	std::cout << std::endl;

	// print_type("CHR-HUM");
	// MapSetTests<ft::multimap<char, Human>, std::multimap<char, Human>, char> test3;
	// test3.DoTests();
	// std::cout << std::endl;
}

void set_tests(void)
{
	print_container_header("SET");

	print_type("INTEGER");
	MapSetTests<ft::set<int>, std::set<int>, int> test1;
	test1.DoTests();
	std::cout << std::endl;

	// print_type("HUMAN");
	// MapSetTests<ft::set<Human>, std::set<Human>, Human> test4;
	// test4.DoTests();
	// std::cout << std::endl;
}

void multiset_tests(void)
{
	print_container_header("MULTISET");

	print_type("INTEGER");
	MapSetTests<ft::multiset<int>, std::multiset<int>, int> test1;
	test1.DoTests();
	std::cout << std::endl;

	// print_type("HUMAN");
	// MapSetTests<ft::multiset<Human>, std::multiset<Human>, Human> test4;
	// test4.DoTests();
	// std::cout << std::endl;
}

void stack_tests(void)
{
	print_container_header("STACK");

	print_type("VECT-INT");
	StakcQueueTests< ft::stack< int, ft::vector<int> >, std::stack< int, std::vector<int> > > test1;
	test1.DoTests();
	test1.stackAccess();
	std::cout << std::endl;

	// print_type("VECT-HUM");
	// StakcQueueTests< ft::stack< Human, ft::vector<Human> >, std::stack< Human, std::vector<Human> > > test2;
	// test2.DoTests();
	// test2.stackAccess();
	// std::cout << std::endl;

	print_type("LIST-INT");
	StakcQueueTests< ft::stack< int, ft::list<int> >, std::stack< int, std::list<int> > > test3;
	test3.DoTests();
	test3.stackAccess();
	std::cout << std::endl;

	// print_type("LIST-HUM");
	// StakcQueueTests< ft::stack< Human, ft::list<Human> >, std::stack< Human, std::list<Human> > > test4;
	// test4.DoTests();
	// test4.stackAccess();
	// std::cout << std::endl;
}

void queue_tests(void)
{
	print_container_header("QUEUE");

	print_type("LIST-INT");
	StakcQueueTests< ft::queue< int, ft::list<int> >, std::queue< int, std::list<int> > > test1;
	test1.DoTests();
	test1.queueAccess();
	std::cout << std::endl;

	// print_type("LIST-HUM");
	// StakcQueueTests< ft::queue< Human, ft::list<Human> >, std::queue< Human, std::list<Human> > > test2;
	// test2.DoTests();
	// test2.queueAccess();
	// std::cout << std::endl;
}

int main(void)
{
	srand(time(NULL));

	vector_tests();
	list_tests();
	map_tests();
	multimap_tests();
	set_tests();
	multiset_tests();
	stack_tests();
	queue_tests();
	return 0;
}
