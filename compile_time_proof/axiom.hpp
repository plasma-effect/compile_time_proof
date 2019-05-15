#pragma once
//This software is released under the MIT License, see LICENSE.txt.

#include"compile_time_proof/value_type.hpp"
#include<numeric>

namespace ctp
{
	namespace detail
	{
		template<class T>constexpr auto min_value = std::numeric_limits<T>::min();
		template<class T>constexpr auto max_value = std::numeric_limits<T>::max();

		template<class T>constexpr bool plus_overflow_check(T lhs, T rhs)
		{
			if (rhs > 0 && lhs > max_value<T> -rhs)
			{
				return false;
			}
			if (rhs < 0 && lhs < min_value<T> -rhs)
			{
				return false;
			}
			return true;
		}
	}
	template<class T, T LhsMin, T LhsMax, T RhsMin, T RhsMax>
	auto operator+(integer_value<T, LhsMin, LhsMax>const& lhs, integer_value<T, RhsMin, RhsMax>const& rhs)
	{
		static_assert(
			detail::plus_overflow_check(LhsMin, RhsMin) &&
			detail::plus_overflow_check(LhsMax, RhsMax), "this operation may cause overflow");
		return integer_value<T, LhsMin + RhsMin, LhsMax + RhsMax>(*lhs + *rhs);
	}
	template<class T, T LhsMin, T LhsMax, T RhsMin, T RhsMax>
	auto operator-(integer_value<T, LhsMin, LhsMax>const& lhs, integer_value<T, RhsMin, RhsMax>const& rhs)
	{
		return lhs + integer_value<T, -RhsMax, -RhsMin>(-(*rhs));
	}
}