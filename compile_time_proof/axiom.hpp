#pragma once
//This software is released under the MIT License, see LICENSE.txt.

#include"compile_time_proof/value_type.hpp"
#include<numeric>

namespace ctp
{
	namespace detail
	{
		template<class T>constexpr bool plus_overflow_check(T lhs, T rhs)
		{
			constexpr auto min = std::numeric_limits<T>::min();
			constexpr auto max = std::numeric_limits<T>::max();
			if (rhs > 0 && lhs > max - rhs)
			{
				return false;
			}
			if (rhs < 0 && lhs < min - rhs)
			{
				return false;
			}
			return true;
		}
	}
	template<class T,T LhsMin, T LhsMax,T RhsMin,T RhsMax>
	auto operator+(integer_value<T, LhsMin, LhsMax>const& lhs, integer_value<T, RhsMin, RhsMax>const& rhs)
	{
		static_assert(
			detail::plus_overflow_check(LhsMin, RhsMin) &&
			detail::plus_overflow_check(LhsMax, RhsMax), "this operation may cause overflow");
		return integer_value<T, LhsMin + RhsMin, LhsMax + RhsMax>(*lhs + *rhs);
	}
}