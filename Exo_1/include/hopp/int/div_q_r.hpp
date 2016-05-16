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


#ifndef HOPP_INT_DIV_Q_R_HPP
#define HOPP_INT_DIV_Q_R_HPP

#include <stdexcept>
#include <climits>


namespace hopp
{
	/**
	 * @brief Container for q and r
	 *
	 * @code
	   #include <hopp/int.hpp>
	   @endcode
	 *
	 * @ingroup hopp_int_and_float
	 */
	template <class T>
	class q_r
	{
	public:
		
		/// q
		T q;
		
		/// r
		T r;
		
		/// @brief Default constructor
		q_r() : q(), r()
		{ }
		
		/// @brief Constructor
		/// @param[in] q q
		/// @param[in] r r
		q_r(T const & q, T const & r) : q(q), r(r)
		{ }
	};
	
	/// @brief Operator << between a std::ostream and a hopp::q_r<T>
	/// @param[in,out] out A std::ostream
	/// @param[in]     q_r A hopp::q_r<T>
	/// @return out
	/// @relates hopp::q_r
	template <class T>
	std::ostream & operator <<(std::ostream & out, hopp::q_r<T> const & q_r)
	{
		out << "{ " << q_r.x << ", " << q_r.y << " }";
		return out;
	}
	
	/**
	 * @brief Divide two integer using >=, >>, &, ==, <<=, !=, -= and |= operators
	 *
	 * @code
	   #include <hopp/int.hpp>
	   @endcode
	 *
	 * @param[in] a Numerator
	 * @param[in] b Denominator
	 *
	 * @pre b != 0
	 *
	 * @return quotient and remainder in hopp::q_r<T>
	 *
	 * @ingroup hopp_int_and_float
	 */
	template <class int_t>
	hopp::q_r<int_t> div_q_r(int_t const & a, int_t const & b)
	{
		// From http://stackoverflow.com/questions/1188939/representing-128-bit-numbers-in-c
		// Copyright © 2008 Evan Teran
		
		if (b == 0)
		{
			throw std::domain_error("hopp::div_q_r: divide by zero");
		}
		else
		{
			constexpr int const bits = sizeof(int_t) * CHAR_BIT;
			
			int_t r = a;
			int_t b_copy = b;
			int_t x = 1;
			int_t q = 0;
			
			while ((r >= b_copy) && (((b_copy >> (bits - 1)) & 1) == 0))
			{
				x <<= 1;
				b_copy <<= 1;
			}
			
			while (x != 0)
			{
				if (r >= b_copy)
				{
					r -= b_copy;
					q |= x;
				}
				x >>= 1;
				b_copy >>= 1;
			}
			
			return { q, r };
		}
	}
}

#endif
