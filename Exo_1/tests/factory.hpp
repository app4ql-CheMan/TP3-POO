// Copyright © 2016 Université Paris-Sud, Written by Lénaïc Bagnères, lenaic.bagneres@u-psud.fr

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>

#include "expression.hpp"


class factory_t
{
public:
	
	using fct_test_t = std::function<bool (std::string const & string)>;
	
	using fct_make_t = std::function<expression_t (std::string const & string, std::vector<expression_t> & expressions)>;
	
	using fct_make_0_t = std::function<expression_t (std::string const & string)>;
	
private:
	
	std::vector<std::tuple<fct_test_t, fct_make_t>> m_fcts;
	
public:
	
	void add(fct_test_t const & fct_test, fct_make_0_t const & fct_make)
	{
		m_fcts.emplace_back
		(
			fct_test,
			[fct_make](std::string const & string, std::vector<expression_t> &) -> expression_t
			{
				return fct_make(string);
			}
		);
	}
	
	void add(fct_test_t const & fct_test, fct_make_t const & fct_make)
	{
		m_fcts.emplace_back(fct_test, fct_make);
	}
	
	expression_t make(std::string const & string)
	{
		std::istringstream ss(string);
		
		std::string word;
		
		std::vector<expression_t> tmp;
		
		while (ss >> word)
		{
			bool match = false;
			
			for (auto const & fct_test_and_fct_make : m_fcts)
			{
				auto const & fct_test = std::get<0>(fct_test_and_fct_make);
				auto const & fct_make = std::get<1>(fct_test_and_fct_make);
				
				if (fct_test(word))
				{
					tmp.push_back(fct_make(word, tmp));
					match = true;
					break;
				}
			}
			
			if (match == false) { std::cerr << "ERROR: factory_t::make: word \"" << word << "\" does not match" << std::endl; } // or throw
		}
		
		return tmp.front().release();
	}
};

#endif
