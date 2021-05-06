/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ForTests.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiborroq <kiborroq@kiborroq.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 13:45:00 by kiborroq          #+#    #+#             */
/*   Updated: 2021/05/05 11:43:06 by kiborroq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORTESTS_HPP
# define FORTESTS_HPP

#include <string>
#include <iostream>
#include <list>
#include <vector>
#include "vector.hpp"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "iterator.hpp"

#define OK "\033[1;32mOK\033[0m"
#define KO "\033[1;31mKO\033[0m"

template <typename InputIterator>
void print_cont(InputIterator first, InputIterator last, std::iostream & os)
{
	for ( ; first != last; first++)
		os << *first << " ";
	os << "\n";
}

template <typename itCont>
std::string get_info_cont(itCont const& c)
{
	std::stringstream stream;

	stream << "SIZE: " << c.size() << "\n";

	stream << "NORMAL: ";
	print_cont(c.begin(), c.end(), stream);
				// std::cout << stream.str() << std::endl;

	stream << "REVERSE: ";
	print_cont(c.rbegin(), c.rend(), stream);
				// std::cout << 51 << std::endl;

	return stream.str();
}

void print_container_header(std::string header)
{
	std::cout << "\033[1;35m" << std::setfill('=') << std::setw(header.size() + 46) << "\033[0m" << std::endl;
	std::cout << "\033[1;35m=" << std::setfill(' ') <<  std::setw(20 + header.size());
	std::cout << header << std::setw(25) << "=\033[0m" << std::endl;
	std::cout << "\033[1;35m" << std::setfill('=') << std::setw(header.size() + 46) << "\033[0m" << std::endl;
	std::cout << std::endl;
}

void print_type(std::string header)
{
	std::cout << "\033[1;36m=================== " << header << " ===================\033[0m" << std::endl;
}

void print_test_res(std::string res)
{
	std::cout << "[" << res << "]";
}

void print_func_name(std::string name)
{
	std::cout << "\033[4;37m" << name << "\033[0m => ";
}

class Human
{
	private:
		std::string name;
		unsigned int age;
	public:
		
		Human(void) : name("Defualt"), age(21) { }
		Human(std::string const & n, unsigned int a) : name(n), age(a) { }
		~Human(void) {}
		bool operator<(Human const & h) const { return(this->age < h.getAge()); }
		bool operator>(Human const & h) const { return(this->age > h.getAge()); }
		bool operator==(Human const & h) const { return(this->age == h.getAge()); }
		bool operator!=(Human const & h) const { return(this->age != h.getAge()); }
		unsigned int getAge(void) const { return (age); }
		std::string getName(void) const { return (name); }
};

std::ostream & operator<<(std::ostream & out, Human const & h) 
{
	out << h.getName() << " " << h.getAge();
	return (out);
}

int get_random_val(int)
{
	return 5 + rand() % 10;
}

std::string get_random_val(std::string)
{
	int			strLength;
	std::string	str;
	std::string	charSet = "abcdefghijklmnopqrstuvwxyzABSCDEFGHIJKLMOPQRSTUVWXYZ";

	strLength = 5 + rand() % 10;
	str.resize(strLength);
	for (int i = 0; i < strLength; i++)
		str[i] = charSet[rand() % charSet.length()];
	return str;
}

char get_random_val(char)
{
	return 33 + rand() % 127;
}

Human get_random_val(Human)
{
	int age = 1 + rand() % 120;
	return Human(get_random_val(std::string()), age);
}

template <typename stdCont, typename ftCont>
void print_result(stdCont const& std_c, ftCont const& ft_c)
{
	std::string std_res = get_info_cont<stdCont>(std_c);
	std::string ft_res = get_info_cont<ftCont>(ft_c);
	if (ft_res == std_res)
		print_test_res(OK);
	else
	{
		print_test_res(KO);
		std::cout << std::endl;
		std::cout << "std-> " << std_res << std::endl;
		std::cout << "ft -> " << ft_res << std::endl;
	}
}

template <typename T>
void print_result(T std_res, T ft_res)
{
	if (ft_res == std_res)
		print_test_res(OK);
	else
	{
		print_test_res(KO);
		std::cout << std::endl;
		std::cout << "std-> " << std_res << std::endl;
		std::cout << "ft -> " << ft_res << std::endl;
	}
}

template <typename T, typename stdCont, typename ftCont>
class VectorTests
{
		public:
		VectorTests(void) { }
		~VectorTests(void) { }

		void DoTests(void)
		{
			print_func_name("constructors");
			{
				size_t size = get_random_val(int());
				T val = get_random_val( T() );

				stdCont std0;
				ftCont ft0;
				print_result(std0, ft0);

				stdCont std1( size, val);
				ftCont ft1( size, val);
				print_result(std1, ft1);

				stdCont std2(std1);
				ftCont ft2(ft1);
				print_result(std2, ft2);

				stdCont std3 = std1;
				ftCont ft3 = ft1;
				print_result(std3, ft3);

				std3 = std2;
				ft3 = ft2;
				print_result(std3, ft3);

				stdCont std4(std3.begin(), std3.end());
				ftCont ft4(ft3.begin(), ft3.end());
				print_result(std4, ft4);

				stdCont std5( static_cast<size_t>(0), val);
				ftCont ft5( static_cast<size_t>(0), val);
				print_result(std5, ft5);
			}
			std::cout << std::endl;

			T val = get_random_val(T());
			size_t size = get_random_val(int());

			stdCont std1(size, val);
			ftCont ft1(size, val);

			print_func_name("max_size");
			{
				print_result<size_t>(std1.max_size(), ft1.max_size());
			}
			std::cout << std::endl;

			print_func_name("resize");
			{
				T val = get_random_val(T());
				size_t size = get_random_val(int());
				
				stdCont std1(size, val);
				ftCont ft1(size, val);
				
				std1.resize(std1.size() - std1.size() / 3);
				ft1.resize(ft1.size() - ft1.size() / 3);
				print_result(std1, ft1);

				val = get_random_val(T());
				std1.resize(std1.size() + size, val);
				ft1.resize(ft1.size() + size, val);
				print_result(std1, ft1);
			}
			std::cout << std::endl;

			print_func_name("empty");
			{
				stdCont std2;
				ftCont ft2;

				if (std1.empty() == ft1.empty())
					print_test_res(OK);
				else
					print_test_res(KO);

				if (std2.empty() == ft2.empty())
					print_test_res(OK);
				else
					print_test_res(KO);
			}
			std::cout << std::endl;

			print_func_name("reserve");
			{
				size_t size = get_random_val(int());

				ftCont ft2;

				ft2.reserve(size);
				if (ft2.capacity() >= size)
					print_test_res(OK);
				else
					print_test_res(KO);

				try
				{
					ft1.reserve(ft1.max_size() + 1);
					print_test_res(KO);
				}
				catch(const std::exception& e)
				{
					print_test_res(OK);
				}
			}
			std::cout << std::endl;

			print_func_name("push_back");
			{
				int times = get_random_val(int());
				T val;
				while (times-- > 0)
				{
					val = get_random_val(T());
					std1.push_back( val );
					ft1.push_back( val );					
				}
				print_result(std1, ft1);
			}
			std::cout << std::endl;

			print_func_name("pop_back");
			{
				stdCont std2;
				std2.push_back(T());
				std2.push_back(T());
				
				ftCont ft2;
				ft2.push_back(T());
				ft2.push_back(T());

				std2.pop_back();
				ft2.pop_back();
				print_result(std2, ft2);

				std2.pop_back();
				ft2.pop_back();
				print_result(std2, ft2);
			}
			std::cout << std::endl;

			print_func_name("assign");
			{
				T val = get_random_val(T());
				size_t size = get_random_val(int());
				
				stdCont std2(size, val);
				ftCont ft2(size, val);

				stdCont std3(std1.rbegin(), std1.rend());
				ftCont ft3(ft1.rbegin(), ft1.rend());

				std2.assign(std1.begin(), std1.end());
				ft2.assign(ft1.begin(), ft1.end());
				print_result(std2, ft2);

				std3.assign(size, val);
				ft3.assign(size, val);
				print_result(std2, ft2);

				std2.assign((size_t)0, T());
				ft2.assign((size_t)0, T());
				print_result(std2, ft2);
			}
			std::cout << std::endl;

			print_func_name("insert");
			{
				T val = get_random_val(T());
				size_t size = get_random_val(int());
				
				stdCont std2(size, val);
				ftCont ft2(size, val);

				stdCont std3(std1.rbegin(), std1.rend());
				ftCont ft3(ft1.rbegin(), ft1.rend());

				std2.insert(std2.end() - std2.size() / 2, std1.begin() + 1, std1.end() - 1);
				ft2.insert(ft2.end() - ft2.size() / 2, ft1.begin() + 1, ft1.end() - 1);
				print_result(std2, ft2);

				std3.insert(std3.begin(), size, val);
				ft3.insert(ft3.begin(), size, val);
				print_result(std3, ft3);

				std2.insert(std2.end() - 1, (size_t)0, T());
				ft2.insert(ft2.end() - 1, (size_t)0, T());
				print_result(std2, ft2);

				std3.insert(std3.begin() + std3.size() / 2, std3.begin(), std3.end());
				ft3.insert(ft3.begin() + ft3.size() / 2, ft3.begin(), ft3.end());
				print_result(std3, ft3);
			}
			std::cout << std::endl;

			print_func_name("erase");
			{
				T val = get_random_val(T());
				size_t size = get_random_val(int());
				
				stdCont std2(size, val);
				ftCont ft2(size, val);

				stdCont std3(std1.rbegin(), std1.rend());
				ftCont ft3(ft1.rbegin(), ft1.rend());

				std2.erase(std2.begin() + std2.size() / 2);
				ft2.erase(ft2.begin() + ft2.size() / 2);
				print_result(std2, ft2);

				std3.erase(std3.begin());
				ft3.erase(ft3.begin());
				print_result(std3, ft3);
				
				std3.erase(std3.begin() + std3.size() / 2, std3.end());
				ft3.erase(ft3.begin() + ft3.size() / 2, ft3.end());
				print_result(std3, ft3);
			}
			std::cout << std::endl;

			print_func_name("swap");
			{
				T val = get_random_val(T());
				size_t size = get_random_val(int());
				
				stdCont std2(size, val);
				ftCont ft2(size, val);
				
				std2.swap(std1);
				ft2.swap(ft1);
				print_result(std2, ft2);
			}
			std::cout << std::endl;

			print_func_name("clear");
			{
				T val = get_random_val(T());
				size_t size = get_random_val(int());
				
				stdCont std2(size, val);
				ftCont ft2(size, val);
				
				std2.clear();
				ft2.clear();
				print_result(std2, ft2);
			}
			std::cout << std::endl;

			print_func_name("operator[]");
			{
				T val = get_random_val(T());

				std1[std1.size() / 2] = val;
				ft1[ft1.size() / 2] = val;
				print_result(std1, ft1);							
			}
			std::cout << std::endl;

			print_func_name("at");
			{
				print_result<T>(std1.at(std1.size() / 2), ft1.at(ft1.size() / 2));
				
				try
				{
					ft1.at(ft1.size() + 1);
					print_test_res(KO);
				}
				catch(const std::exception& e)
				{
					print_test_res(OK);
				}
			}
			std::cout << std::endl;

			print_func_name("back");
			{
				print_result<T>(std1.back(), ft1.back());
			}
			std::cout << std::endl;

			print_func_name("front");
			{
				print_result<T>(std1.front(), ft1.front());
			}
			std::cout << std::endl;

			print_func_name("relational");
			{
				T val = get_random_val(T());

				stdCont std2(std1);
				ftCont ft2(ft1);
				print_result<bool>(std1 == std2, ft1 == ft2);

				std2.push_back(val);
				ft2.push_back(val);
				print_result<bool>(std2 > std1, ft2 > ft1);

				std2.insert(++std2.begin(), std1.begin(), std1.end());
				ft2.insert(++ft2.begin(), ft1.begin(), ft1.end());
				print_result<bool>(std2 < std1, ft2 < ft1);

				print_result(std2 != std1, ft2 != ft1);
			}
			std::cout << std::endl;
		}
};

template <typename T, typename stdCont, typename ftCont>
class ListTests
{
	public:
		ListTests(void) { }
		~ListTests(void) { }

		typedef typename stdCont::iterator stdIt;
		typedef typename ftCont::iterator ftIt;

		static bool stdPred(T const& elem)
		{
			static size_t n;
			(void)elem;
			
			n++;
			if (n % 2 == 0)
				return true;
			else
				return false; 
		}

		static bool ftPred(T const& elem)
		{
			static size_t n;
			(void)elem;
			
			n++;
			if (n % 2 == 0)
				return true;
			else
				return false; 
		}

		static bool equals(T const& first, T const& second) { return first == second; }

		void DoTests(void)
		{
			print_func_name("constructors");
			{
				size_t size = get_random_val(int());
				T val = get_random_val( T() );
				
				stdCont std0;
				ftCont ft0;
				print_result(std0, ft0);

				stdCont std1( size, val);
				ftCont ft1( size, val);
				print_result(std1, ft1);

				stdCont std2(std1);
				ftCont ft2(ft1);
				print_result(std2, ft2);

				stdCont std3 = std1;
				ftCont ft3 = ft1;
				print_result(std3, ft3);

				std3 = std2;
				ft3 = ft2;
				print_result(std3, ft3);

				stdCont std4(std3.begin(), std3.end());
				ftCont ft4(ft3.begin(), ft3.end());
				print_result(std4, ft4);

				stdCont std5( static_cast<size_t>(0), val);
				ftCont ft5( static_cast<size_t>(0), val);
				print_result(std5, ft5);

			}
			std::cout << std::endl;

			T val = get_random_val(T());
			size_t size = get_random_val(int());

			stdCont std1(size, val);
			ftCont ft1(size, val);

			print_func_name("max_size");
			{
				print_result<size_t>(std1.max_size(), ft1.max_size());
			}
			std::cout << std::endl;

			print_func_name("resize");
			{
				T val = get_random_val(T());
				size_t size = get_random_val(int());

				stdCont std1(size, val);
				ftCont ft1(size, val);

				std1.resize(std1.size() - std1.size() / 3);
				ft1.resize(ft1.size() - ft1.size() / 3);
				print_result(std1, ft1);

				val = get_random_val(T());
				std1.resize(std1.size() + size, val);
				ft1.resize(ft1.size() + size, val);
				print_result(std1, ft1);
			}
			std::cout << std::endl;

			print_func_name("empty");
			{
				stdCont std2;
				ftCont ft2;

				print_result<bool>(std1.empty(), ft1.empty());
				print_result<bool>(std2.empty(), ft2.empty());
			}
			std::cout << std::endl;

			print_func_name("push_back");
			{
				int times = get_random_val(int());
				T val;
				while (times-- > 0)
				{
					val = get_random_val(T());
					std1.push_back( val );
					ft1.push_back( val );					
				}
				print_result(std1, ft1);
			}
			std::cout << std::endl;

			print_func_name("pop_back");
			{
				stdCont std2;
				std2.push_back(T());
				std2.push_back(T());
				
				ftCont ft2;
				ft2.push_back(T());
				ft2.push_back(T());

				std2.pop_back();
				ft2.pop_back();
				print_result(std2, ft2);

				std2.pop_back();
				ft2.pop_back();
				print_result(std2, ft2);
			}
			std::cout << std::endl;

			print_func_name("push_front");
			{
				int times = get_random_val(int());
				T val;
				while (times-- > 0)
				{
					val = get_random_val(T());
					std1.push_front( val );
					ft1.push_front( val );
				}
				print_result(std1, ft1);
			}
			std::cout << std::endl;

			print_func_name("pop_front");
			{
				stdCont std2;
				std2.push_front(T());
				std2.push_front(T());
				
				ftCont ft2;
				ft2.push_front(T());
				ft2.push_front(T());

				std2.pop_front();
				ft2.pop_front();
				print_result(std2, ft2);

				std2.pop_front();
				ft2.pop_front();
				print_result(std2, ft2);
			}
			std::cout << std::endl;

			print_func_name("assign");
			{
				T val = get_random_val(T());
				size_t size = get_random_val(int());
				
				stdCont std2(size, val);
				ftCont ft2(size, val);

				stdCont std3(std1.rbegin(), std1.rend());
				ftCont ft3(ft1.rbegin(), ft1.rend());

				std2.assign(std1.begin(), std1.end());
				ft2.assign(ft1.begin(), ft1.end());
				print_result(std2, ft2);

				std3.assign(size, val);
				ft3.assign(size, val);
				print_result(std2, ft2);

				std2.assign((size_t)0, T());
				ft2.assign((size_t)0, T());
				print_result(std2, ft2);
			}
			std::cout << std::endl;

			print_func_name("insert");
			{
				val = get_random_val(T());
				size = get_random_val(int());
				
				stdCont std2;
				ftCont ft2;

				std2.insert(std2.begin(), size, val);
				ft2.insert(ft2.begin(), size, val);
				print_result(std2, ft2);

				stdIt std_it = std2.begin();
				ftIt ft_it = ft2.begin();

				std2.insert(std_it, std1.rbegin(), std1.rend());
				ft2.insert(ft_it, ft1.rbegin(), ft1.rend());
				print_result(std2, ft2);

				std2.insert(std2.end(), size, val);
				ft2.insert(ft2.end(), size, val);
				print_result(std2, ft2);

				std2.insert(std_it, std2.begin(), std2.end());
				ft2.insert(ft_it, ft2.begin(), ft2.end());
				print_result(std2, ft2);
			}
			std::cout << std::endl;

			print_func_name("erase");
			{
				val = get_random_val(T());
				size = get_random_val(int());
				
				stdCont std2(size, val);
				ftCont ft2(size, val);

				stdIt std_it = ++std2.begin();
				ftIt ft_it = ++ft2.begin();

				std2.insert(std_it, std1.begin(), std1.end());
				ft2.insert(ft_it, ft1.begin(), ft1.end());

				std2.erase(std2.begin());
				ft2.erase(ft2.begin());
				print_result(std2, ft2);

				std2.erase(std_it, std2.end());
				ft2.erase(ft_it, ft2.end());
				print_result(std2, ft2);

				std2.erase(std2.begin(), std2.end());
				ft2.erase(ft2.begin(), ft2.end());
				print_result(std2, ft2);

				std2.erase(std2.begin(), std2.end());
				ft2.erase(ft2.begin(), ft2.end());
				print_result(std2, ft2);
			}
			std::cout << std::endl;

			print_func_name("swap");
			{
				T val = get_random_val(T());
				size_t size = get_random_val(int());
				
				stdCont std2(size, val);
				ftCont ft2(size, val);
				
				std2.swap(std1);
				ft2.swap(ft1);
				print_result(std2, ft2);
			}
			std::cout << std::endl;

			print_func_name("clear");
			{
				T val = get_random_val(T());
				size_t size = get_random_val(int());
				
				stdCont std2(size, val);
				ftCont ft2(size, val);
				
				std2.clear();
				ft2.clear();
				print_result(std2, ft2);
			}
			std::cout << std::endl;

			print_func_name("back");
			{
				print_result<T>(std1.back(), ft1.back());
			}
			std::cout << std::endl;

			print_func_name("front");
			{
				print_result<T>(std1.front(), ft1.front());
			}
			std::cout << std::endl;

			print_func_name("relational");
			{
				T val = get_random_val(T());

				stdCont std2(std1);
				ftCont ft2(ft1);
				print_result<bool>(std1 == std2, ft1 == ft2);

				std2.push_back(val);
				ft2.push_back(val);
				print_result<bool>(std2 > std1, ft2 > ft1);

				std2.insert(++std2.begin(), std1.begin(), std1.end());
				ft2.insert(++ft2.begin(), ft1.begin(), ft1.end());
				print_result<bool>(std2 < std1, ft2 < ft1);

				print_result(std2 != std1, ft2 != ft1);
			}
			std::cout << std::endl;

			print_func_name("splice");
			{
				T val = get_random_val(T());
				size_t size = get_random_val(int());
				
				stdCont std2(std1);
				ftCont ft2(ft1);

				stdCont std3(size, val);
				ftCont ft3(size, val);

				std2.splice(++std2.begin(), std1, ++std1.begin());
				ft2.splice(++ft2.begin(), ft1, ++ft1.begin());
				print_result(std1, ft1);
				print_result(std2, ft2);

				stdIt std_it1 = --std3.end();
				ftIt ft_it1 = --ft3.end();

				std3.insert(std3.end(), std2.rbegin(), std2.rend());
				ft3.insert(ft3.end(), ft2.rbegin(), ft2.rend());

				stdIt std_it2 = --std3.end();
				ftIt ft_it2 = --ft3.end();

				std3.insert(std3.end(), std2.begin(), std2.end());
				ft3.insert(ft3.end(), ft2.begin(), ft2.end());

				std3.splice(std_it1, std2);
				ft3.splice(ft_it1, ft2);
				print_result(std3, ft3);
				print_result(std2, ft2);

				std3.splice(++std3.begin(), std3, std_it1, std_it2);
				ft3.splice(++ft3.begin(), ft3, ft_it1, ft_it2);
				print_result(std3, ft3);
			}
			std::cout << std::endl;

			print_func_name("remove");
			{
				T val1 = get_random_val(T());
				T val2 = get_random_val(T());

				stdCont std2;
				ftCont ft2;

				size_t size = 500;

				while (size-- > 0)
				{
					if (size % 2 == 0)
						std2.push_back(val1);
					else
						std2.push_back(val2);
				}
				
				size = 500;
				while (size-- > 0)
				{
					if (size % 2 == 0)
						ft2.push_back(val1);
					else
						ft2.push_back(val2);
				}

				std2.remove(val1);
				ft2.remove(val1);
				print_result(std2, ft2);

				std2.remove(val2);
				ft2.remove(val2);
				print_result(std2, ft2);

				std2.remove(val1);
				ft2.remove(val1);
				print_result(std2, ft2);
			}
			std::cout << std::endl;
			
			print_func_name("remove_if");
			{
				T val = get_random_val(T());
				size_t size = get_random_val(int());

				stdCont std2(size, val);
				ftCont ft2(size, val);

				std2.remove_if(stdPred);
				ft2.remove_if(ftPred);
				print_result(std2, ft2);

				std2.remove_if(stdPred);
				ft2.remove_if(ftPred);
				print_result(std2, ft2);
			}
			std::cout << std::endl;
			
			print_func_name("unique");
			{
				T val[3] = {
					get_random_val(T()),
					get_random_val(T()),
					get_random_val(T())
				};

				size_t count = 1000;
				size_t num;
			
				stdCont std2;
				ftCont ft2;
				std2.unique();
				ft2.unique();
				print_result(std2, ft2);

				while (count-- > 0)
				{
					num = get_random_val(int());

					std2.push_back( val[ num % 3 ] );
					ft2.push_back( val[ num % 3 ] );		
				}
				
				stdCont std3(std2);
				ftCont ft3(ft2);

				std2.unique();
				ft2.unique();
				print_result(std2, ft2);

				std3.unique(equals);
				ft3.unique(equals);
				print_result(std2, ft2);
			}
			std::cout << std::endl;

			print_func_name("sort");
			{
				
			}
			std::cout << std::endl;

			print_func_name("merge");
			{
				
			}
			std::cout << std::endl;
			
			print_func_name("reverse");
			{
				stdCont std2;
				ftCont ft2;
				std2.reverse();
				ft2.reverse();
				print_result(std2, ft2);

				std1.reverse();
				ft1.reverse();
				print_result(std1, ft1);
			}
			std::cout << std::endl;
		}
};

#endif
