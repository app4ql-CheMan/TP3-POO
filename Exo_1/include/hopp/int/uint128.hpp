// Copyright © 2014, 2016 Lénaïc Bagnères, hnc@singularity.fr

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


#ifndef HOPP_INT_UINT128_HPP
#define HOPP_INT_UINT128_HPP

#include <iostream>
#include <limits>

#include "ullint.hpp"
#include "div_q_r.hpp"


namespace hopp
{
	/**
	 * @brief unsigned int with values between 0 and 255
	 *
	 * @code
	   #include <hopp/int.hpp>
	   @endcode
	 *
	 * @ingroup hopp_int_and_float
	 */
	class uint128
	{
	public:
		
		/// Lower part
		hopp::ullint lo;
		
		/// High part
		hopp::ullint hi;
		
	public:
		
		/// @brief Constructor from hopp::ullint
		/// @param[in] i Integer between 0 and 255
		uint128(hopp::ullint const i = 0) : lo(i), hi(0) { }
		
		/// @brief Constructor from string
		/// @param[in] i A std::string
		uint128(std::string const & i) : lo(0), hi(0)
		{
			// TODO
		}
	};
	
	// ==, !=, <, >, <=, >=
	
	/// @brief Operator == between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return true if the hopp::uint128 are equal, false otherwise
	/// @relates hopp::uint128
	inline bool operator ==(hopp::uint128 const & a, hopp::uint128 const & b)
	{
		return (a.lo == b.lo) && (a.hi == b.hi);
	}
	
	/// @brief Operator != between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return true if the hopp::uint128 are different, false otherwise
	/// @relates hopp::uint128
	inline bool operator !=(hopp::uint128 const & a, hopp::uint128 const & b)
	{
		return (a.lo != b.lo) || (a.hi != b.hi);
	}
	
	/// @brief Operator < between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return true if a < b, false otherwise
	/// @relates hopp::uint128
	inline bool operator <(hopp::uint128 const & a, hopp::uint128 const & b)
	{
		if (a.hi < b.hi) { return true; }
		if (a.hi == b.hi) { return a.lo < b.lo; }
	}
	
	/// @brief Operator > between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return true if a > b, false otherwise
	/// @relates hopp::uint128
	inline bool operator >(hopp::uint128 const & a, hopp::uint128 const & b)
	{
		return b < a;
	}
	
	/// @brief Operator <= between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return true if a <= b, false otherwise
	/// @relates hopp::uint128
	inline bool operator <=(hopp::uint128 const & a, hopp::uint128 const & b)
	{
		return (a == b) || (a < b);
	}
	
	/// @brief Operator > between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return true if a >= b, false otherwise
	/// @relates hopp::uint128
	inline bool operator >=(hopp::uint128 const & a, hopp::uint128 const & b)
	{
		return b >= a;
	}
	
	// &, |, <<, >>
	
	/// @brief Operator & between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return a & b
	/// @relates hopp::uint128
	inline hopp::uint128 operator &(hopp::uint128 const & a, hopp::uint128 const & b)
	{
		hopp::uint128 r = a;
		r.lo &= b.lo;
		r.hi &= b.hi;
		return r;
	}
	
	/// @brief Operator &= between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return a &= b
	/// @relates hopp::uint128
	inline hopp::uint128 & operator &=(hopp::uint128 & a, hopp::uint128 const & b)
	{
		a = a & b;
		return a;
	}
	
	/// @brief Operator | between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return a | b
	/// @relates hopp::uint128
	inline hopp::uint128 operator |(hopp::uint128 const & a, hopp::uint128 const & b)
	{
		hopp::uint128 r = a;
		r.lo |= b.lo;
		r.hi |= b.hi;
		return r;
	}
	
	/// @brief Operator |= between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return a |= b
	/// @relates hopp::uint128
	inline hopp::uint128 & operator |=(hopp::uint128 & a, hopp::uint128 const & b)
	{
		a = a | b;
		return a;
	}
	
	/// @brief Operator << between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return a << b
	/// @relates hopp::uint128
	inline hopp::uint128 operator <<(hopp::uint128 const & a, hopp::uint128 const & b)
	{
		if (b >= 128) { return 0; }
		
		hopp::uint128 r = a;
		
		if (b >= 64)
		{
			r.hi = r.lo;
			r.lo = 0;
			r.hi <<= b.lo - 64;
		}
		else
		{
			hopp::ullint tmp = a.lo & (std::numeric_limits<hopp::ullint>::max() << (64 - b.lo));
			r.lo <<= b.lo;
			r.hi <<= b.lo;
			r.hi += tmp;
		}
		
		return r;
	}
	
	/// @brief Operator << between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return a <<= b
	/// @relates hopp::uint128
	inline hopp::uint128 & operator <<=(hopp::uint128 & a, hopp::uint128 const & b)
	{
		a = a << b;
		return a;
	}
	
	/// @brief Operator >> between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return a << b
	/// @relates hopp::uint128
	inline hopp::uint128 operator >>(hopp::uint128 const & a, hopp::uint128 const & b)
	{
		if (b >= 128) { return 0; }
		
		hopp::uint128 r = a;
		
		if (b >= 64)
		{
			r.lo = r.hi;
			r.hi = 0;
			r.lo >>= b.lo - 64;
		}
		else
		{
			hopp::ullint tmp = a.lo & (std::numeric_limits<hopp::ullint>::max() >> b.lo);
			r.lo >>= b.lo;
			r.hi >>= b.lo;
			r.lo += tmp;
		}
		
		return r;
	}
	
	/// @brief Operator >> between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return a >>= b
	/// @relates hopp::uint128
	inline hopp::uint128 & operator >>=(hopp::uint128 & a, hopp::uint128 const & b)
	{
		a = a >> b;
		return a;
	}
	
	// +
	
	/// @brief Operator + between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return a + b
	/// @relates hopp::uint128
	inline hopp::uint128 operator +(hopp::uint128 const & a, hopp::uint128 const & b)
	{
		hopp::uint128 r = a;
		r.lo += b.lo;
		r.hi += b.hi + ((r.lo < a.lo) || (r.lo < b.lo)) ? 1 : 0;
		return r;
	}
	
	/// @brief Operator += between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return a += b
	/// @relates hopp::uint128
	inline hopp::uint128 & operator +=(hopp::uint128 & a, hopp::uint128 const & b)
	{
		a = a + b;
		return a;
	}
	
	/// @brief Operator ++ (prefix) with a hopp::uint128
	/// @param[in] i A hopp::uint128
	/// @return i++
	/// @relates hopp::uint128
	inline hopp::uint128 & operator ++(hopp::uint128 & i)
	{
		++i.lo;
		if (i.lo == 0) { ++i.hi; }
		return i;
	}
	
	/// @brief Operator ++ (postfix) with a hopp::uint128
	/// @param[in] i A hopp::uint128
	/// @return i++
	/// @relates hopp::uint128
	inline hopp::uint128 operator ++(hopp::uint128 & i, int)
	{
		hopp::uint128 tmp = i;
		++i;
		return tmp;
	}
	
	// -
	
	/// @brief Operator - between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return a - b
	/// @relates hopp::uint128
	inline hopp::uint128 operator -(hopp::uint128 const & a, hopp::uint128 const & b)
	{
		hopp::uint128 r;
		if (a >= b)
		{
			r.lo = a.lo - b.lo;
			r.hi = a.hi - b.hi;
		}
		else
		{
			r = std::numeric_limits<hopp::uint128>::max() - (b - a) - 1;
		}
		return r;
	}
	
	/// @brief Operator -= between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return a -= b
	/// @relates hopp::uint128
	inline hopp::uint128 & operator -=(hopp::uint128 & a, hopp::uint128 const & b)
	{
		a = a - b;
		return a;
	}
	
	/// @brief Operator -- (prefix) with a hopp::uint128
	/// @param[in] i A hopp::uint128
	/// @return i--
	/// @relates hopp::uint128
	inline hopp::uint128 & operator --(hopp::uint128 & i)
	{
		if (i.lo != 0) { --i.lo; }
		else if (i.lo == 0)
		{
			if (i.hi == 0) { i = std::numeric_limits<hopp::uint128>::max(); }
			else { --i.hi; i.lo = std::numeric_limits<hopp::ullint>::max(); }
		}
		return i;
	}
	
	/// @brief Operator -- (postfix) with a hopp::uint128
	/// @param[in] i A hopp::uint128
	/// @return i--
	/// @relates hopp::uint128
	inline hopp::uint128 operator --(hopp::uint128 & i, int)
	{
		hopp::uint128 tmp = i;
		--i;
		return tmp;
	}
	
	// *
	
	/// @brief Operator * between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return a * b
	/// @relates hopp::uint128
	inline hopp::uint128 operator *(hopp::uint128 const & a, hopp::uint128 const & b)
	{
		if ((a == 0) || (b == 0)) { return 0; }
		if (a == 1) { return b; }
		if (b == 1) { return a; }
		if (a == 2) { return b + b; }
		if (b == 2) { return a + a; }
		
		// TODO: Use logical shift
		hopp::uint128 r;
		//for ()
		
		return r;
	}
	
	/// @brief Operator *= between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return a *= b
	/// @relates hopp::uint128
	inline hopp::uint128 & operator *=(hopp::uint128 & a, hopp::uint128 const & b)
	{
		a = a * b;
		return a;
	}
	
	// /
	
	/// @brief Operator / between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return a / b
	/// @relates hopp::uint128
	inline hopp::uint128 operator /(hopp::uint128 const & a, hopp::uint128 const & b)
	{
		return hopp::div_q_r(a, b).q;
	}
	
	/// @brief Operator /= between two hopp::uint128
	/// @param[in] a A hopp::uint128
	/// @param[in] b A hopp::uint128
	/// @return a /= b
	/// @relates hopp::uint128
	inline hopp::uint128 & operator /=(hopp::uint128 & a, hopp::uint128 const & b)
	{
		a = a / b;
		return a;
	}
	
	// <<
	
	/// @brief Operator << between a std::ostream and a hopp::uint128
	/// @param[in,out] o     Output stream
	/// @param[in]     uint128 A hopp::uint128
	/// @return the output stream
	/// @relates hopp::uint128
	inline std::ostream & operator <<(std::ostream & o, hopp::uint128 const uint128)
	{
		// TODO
		o << "TODO{hopp::uint128}";
		return o;
	}
}

/*namespace std
{
	/// @brief Specialization of std::numeric_limits<hopp::uint128>
	/// @relates hopp::uint128
	template <>
	class numeric_limits<hopp::uint128>
	{
	public:
		
		// http://en.cppreference.com/w/cpp/types/numeric_limits
		
		/// Identifies types for which std::numeric_limits is specialized 
		static constexpr bool is_specialized = true;
		
		/// Identifies signed types 
		static constexpr bool is_signed = false;
		
		/// Identifies integer types 
		static constexpr bool is_integer = true;
		
		/// Identifies exact types 
		static constexpr bool is_exact = true;
		
		/// Identifies floating-point types that can represent the special value "positive infinity"
		static constexpr bool has_infinity = false;
		
		/// Identifies floating-point types that can represent the special value "signaling not-a-number" (NaN)
		static constexpr bool has_signaling_NaN = false;
		
		/// Identifies the denormalization style used by the floating-point type
		static constexpr bool has_denorm = std::denorm_absent;
		
		/// Identifies the floating-point types that detect loss of precision as denormalization loss rather than inexact result
		static constexpr bool has_denorm_loss = false;
		
		/// Identifies the rounding style used by the type
		static constexpr bool round_style = std::round_toward_zero;
		
		/// Identifies the IEC 559/IEEE 754 floating-point types
		static constexpr bool is_iec559 = false;
		
		/// Identifies the types that represent a finite set of values
		static constexpr bool is_bounded = false;
		
		/// Identifies the types that handle overflows with modulo arithmetic
		static constexpr bool is_modulo = true;
		
		/// Number of radix digits that can be represented without change
		static constexpr int digits = 8;
		
		/// Number of decimal digits that can be represented without change
		static constexpr int digits10 = std::numeric_limits<unsigned char>::digits10;
		
		/// Number of decimal digits necessary to differentiate all values of this type
		static constexpr int max_digits10 = 0;
		
		/// The radix or integer base used by the representation of the given type
		static constexpr int radix = 2;
		
		/// One more than the smallest negative power of the radix that is a valid normalized floating-point value
		static constexpr int min_exponent = 0;
		
		/// The smallest negative power of ten that is a valid normalized floating-point value
		static constexpr int min_exponent10 = 0;
		
		/// One more than the largest integer power of the radix that is a valid finite floating-point value
		static constexpr int max_exponent = 0;
		
		/// The largest integer power of 10 that is a valid finite floating-point value
		static constexpr int max_exponent10 = 0;
		
		/// Identifies types which can cause arithmetic operations to trap
		static constexpr bool traps = std::numeric_limits<unsigned char>::traps;
		
		/// Identifies floating-point types that detect tinyness before rounding
		static constexpr bool tinyness_before = false;
		
	public:
		
		/// @brief Returns the smallest finite value of the given type
		/// @return the smallest finite value of the given type
		static hopp::uint128 min() { return 0u; }
		
		/// @brief Returns the lowest finite value of the given type
		/// @return the lowest finite value of the given type
		static hopp::uint128 lowest() { return 0u; }
		
		/// @brief Returns the largest finite value of the given type
		/// @return the largest finite value of the given type
		static hopp::uint128 max() { return 255u; }
		
		/// @brief Returns the difference between 1.0 and the next representable value of the given floating-point type
		/// @return the difference between 1.0 and the next representable value of the given floating-point type
		static hopp::uint128 epsilon() { return 0u; }
		
		/// @brief Returns the maximum rounding error of the given floating-point type
		/// @return the maximum rounding error of the given floating-point type
		static hopp::uint128 round_error() { return 0u; }
		
		/// @brief Returns the positive infinity value of the given floating-point type
		/// @return the positive infinity value of the given floating-point type
		static hopp::uint128 infinity() { return 0u; }
		
		/// @brief Returns a quiet NaN value of the given floating-point type
		/// @return a quiet NaN value of the given floating-point type
		static hopp::uint128 quiet_NaN() { return 0u; }
		
		/// @brief Returns a signaling NaN value of the given floating-point type
		/// @return a signaling NaN value of the given floating-point type
		static hopp::uint128 signaling_NaN() { return 0u; }
		
		/// @brief Returns the smallest positive subnormal value of the given floating-point type
		/// @return the smallest positive subnormal value of the given floating-point type
		static hopp::uint128 denorm_min() { return 0u; }
	};
}*/

#endif
