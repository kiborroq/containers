/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 19:30:50 by kiborroq          #+#    #+#             */
/*   Updated: 2021/05/10 02:02:05 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#include <list>
#include "list.hpp"
#include <vector>
#include "vector.hpp"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <algorithm>
#include "ForTests.hpp"


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

	// print_type("CHAR");
	// VectorTests<char, std::vector<char>, ft::vector<char> > test3;
	// test3.DoTests();
	// std::cout << std::endl;

	// print_type("HUMAN");
	// VectorTests<Human, std::vector<Human>, ft::vector<Human> > test4;
	// test4.DoTests();
}

void list_tests(void)
{
	print_container_header("LIST");

	print_type("INTEGER");
	ListTests<int, std::list<int>, ft::list<int> > test1;
	test1.DoTests();
	std::cout << std::endl;

	// print_type("STRING");
	// ListTests<std::string, std::list<std::string>, ft::list<std::string> > test2;
	// test2.DoTests();
	// std::cout << std::endl;

	// print_type("CHAR");
	// ListTests<char, std::list<char>, ft::list<char> > test3;
	// test3.DoTests();
	// std::cout << std::endl;

	// print_type("HUMAN");
	// ListTests<Human, std::list<Human>, ft::list<Human> > test4;
	// test4.DoTests();
}

void map_tests(void)
{
	print_container_header("MAP");

	print_type("INT-STR");
	MapTests<int, std::string> test1;
	test1.DoTests();
	std::cout << std::endl;

	// print_type("STR-INT");
	// MapTests<std::string, int> test2;
	// test1.DoTests();
	// std::cout << std::endl;

	// print_type("CHR-INT");
	// MapTests<char, int> test3;
	// test1.DoTests();
}

#include "_rb_tree.hpp"
#include "map.hpp"

int main(void)
{
	srand(time(NULL));

	vector_tests();
	list_tests();
	map_tests();

	return 0;
}
