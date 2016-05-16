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

#include <hopp/print/std.hpp>

#include "vector_view.hpp"


int main()
{
	// Vector
	
	std::vector<int> vector(10);
	
	// View
	
	auto view = make_view(vector, 2, 7);
	
	for (size_t i = 0; i < view.size(); ++i)
	{
		view[i] = int(view.size() - i);
	}
	
	std::cout << "View         = " << view << std::endl;
	std::cout << "Vector       = " << vector << std::endl;
	std::cout << std::endl;
	
	// Increment
	
	for (auto & e : view)
	{
		++e;
	}
	
	std::cout << "View         = " << view << std::endl;
	std::cout << "Vector       = " << vector << std::endl;
	std::cout << std::endl;
	
	// Sort
	
	std::sort(view.begin(), view.end());
	
	std::cout << "View         = " << view << std::endl;
	std::cout << "Vector       = " << vector << std::endl;
	std::cout << std::endl;
	
	// View of view
	
	auto view_of_view = make_view(view, 1, 3);
	
	std::transform(view_of_view.begin(), view_of_view.end(), view_of_view.begin(), [](int const) { return 7; });
	
	std::cout << "View of view = " << view_of_view << std::endl;
	std::cout << "View         = " << view << std::endl;
	std::cout << "Vector       = " << vector << std::endl;
	std::cout << std::endl;
	
	return 0;
}
