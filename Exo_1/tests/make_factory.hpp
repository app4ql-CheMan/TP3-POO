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

#ifndef MAKE_FACTORY_HPP
#define MAKE_FACTORY_HPP

#include "factory.hpp"


inline
factory_t make_factory()
{
	factory_t f;
	
	f.add
	(
		hopp::is_integer,
		[](std::string const & string) -> expression_t { return constant_t(std::stoi(string)); }
	);
	
	f.add
	(
		[](std::string const & string) -> bool
		{
			return std::find_if(string.begin(), string.end(), [](char const c) { return std::isalpha(c) == false; }) == string.end();
		},
		[](std::string const & string) -> expression_t { return variable_t(string, 0); }
	);
	
	f.add
	(
		[](std::string const & string) -> bool
		{
			return (string == "+" || string == "-" || string == "*" || string == "/" || string == "=");
		},
		[](std::string const & string, std::vector<expression_t> & expressions) -> expression_t
		{
			if (expressions.size() < 2)
			{
				std::cerr << "ERROR: make_factory: operator_t needs two expressions" << std::endl;
				exit(1); // or throw
			}
			
			auto r = operator_t
			(
				string[0],
				expressions[expressions.size() - 2].release(),
				expressions[expressions.size() - 1].release()
			);
			
			expressions.resize(expressions.size() - 2);
			
			return std::move(r);
		}
	);
	
	return f;
}

#endif
