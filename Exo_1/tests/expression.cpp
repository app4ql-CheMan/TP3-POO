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

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

#include "expression.hpp"



int main()
{
	expression_t e;
	std::cout << "Expression = " << e << std::endl;
	std::cout << std::endl;
	
	e = variable_t("var_name", 7);
	std::cout << "Expression = " << e << std::endl;
	std::cout << std::endl;
	
	e = constant_t(42);
	std::cout << "Expression = " << e << std::endl;
	std::cout << std::endl;
	
	e = operator_t('+', variable_t("var_name", 7), constant_t(42));
	std::cout << "Expression = " << e << std::endl;
	std::cout << std::endl;
	
	return 0;
}
