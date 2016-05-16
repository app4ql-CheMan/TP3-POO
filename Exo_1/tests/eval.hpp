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

#ifndef EVAL_HPP
#define EVAL_HPP

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "expression.hpp"
#include "make_factory.hpp"


inline
bool is_constant(expression_t const & e)
{
	return dynamic_cast<constant_t const *>(e.get()) != nullptr;
}

inline
bool is_variable(expression_t const & e)
{
	return dynamic_cast<variable_t const *>(e.get()) != nullptr;
}

inline
bool is_operator(expression_t const & e)
{
	return dynamic_cast<operator_t const *>(e.get()) != nullptr;
}

template <class T>
T & expression_cast(expression_t & e)
{
	return *static_cast<T *>(e.get()); // we can check if this cast is valid
}

template <class T>
T const & expression_cast(expression_t const & e)
{
	return *static_cast<T const *>(e.get()); // we can check if this cast is valid
}


inline
void propagate(std::map<std::string, double> const & variable_values, expression_t & e);


inline
std::map<std::string, double> eval(std::vector<std::string> const & lines)
{
	std::map<std::string, double> r;
	auto f = make_factory();
	// TODO
	for(auto &line : lines)
	{
		auto expression = f.make(line);
		propagate(r, expression);
		if(is_operator(expression))
		{
			auto & op = expression_cast<operator_t>(expression);
			if(op.symbol == '=')
			{
				if(is_variable(op.a))
				{
					r[expression_cast<variable_t>(op.a).name] = op.b.eval();
				}
			}
		}
	}
	return r;
}


inline
void propagate(std::map<std::string, double> const & variable_values, expression_t & e)
{
	if((is_operator(e)))
	{
		auto & op = expression_cast<operator_t>(e);
		propagate(variable_values, op.b);
		propagate(variable_values, op.a);
	}
	else if(is_variable(e))
	{
		auto & v = expression_cast<variable_t>(e);
		//si variable est dans la hashmap
		if(variable_values.find(v.name) != variable_values.end())
		{
			v.value = variable_values.at(v.name);
		}
	}
}

#endif
