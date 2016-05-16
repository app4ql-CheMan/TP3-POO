// Copyright © 2016 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef HOPP_CONVERSATION_IS_INTEGER_HPP
#define HOPP_CONVERSATION_IS_INTEGER_HPP

#include <string>
#include <cctype>


namespace hopp
{
	/**
	 * @brief Check if string contains an integer
	 *
	 * @code
	   #include <hopp/conversion.hpp>
	   @endcode
	 *
	 * @param[in] string A std::string
	 *
	 * @return true if the string  contains an integer, false otherwise
	 *
	 * @ingroup hopp_conversion
	 */
	inline
	bool is_integer(std::string const & string)
	{
		if (string.size() == 0) { return false; }
		
		if (string.size() == 1 && std::isdigit(string[0]) == false) { return false; }
		
		if (string[0] != '+' && string[0] != '-' && std::isdigit(string[0]) == false) { return false; }
		
		for (auto it = string.begin() + 1; it != string.end(); ++it)
		{
			if (std::isdigit(*it) == false) { return false; }
		}
		
		return true;
	}
}

#endif
