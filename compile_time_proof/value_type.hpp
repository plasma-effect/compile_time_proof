#pragma once
//This software is released under the MIT License, see LICENSE.txt.

#include<exception>
#include<stdexcept>
#include<sstream>
#include<cctype>
#include<iostream>
#include"compile_time_proof/type_traits.hpp"

namespace ctp
{
	template<class T, T Min, T Max>class integer_value
	{
		static constexpr auto min = Min;
		static constexpr auto max = Max;
		T val;
		static void value_check(T const& v)
		{
			if (!(min <= v && v <= max))
			{
				std::stringstream ss;
				ss << "given value [" << v << "] is not in [" << min << ", " << max << "]";
				throw std::invalid_argument(ss.str());
			}
		}
	public:
		integer_value(T const& v) :val(v)
		{
			value_check(v);
		}
		integer_value() noexcept :val(0)
		{
			static_assert(Min <= 0 && 0 <= Max, "0 is not in [Min, Max]");
		}
		integer_value& operator=(T const& v)
		{
			value_check(v);
			val = v;
			return *this;
		}
		integer_value(integer_value const&) = default;
		integer_value(integer_value&&) = default;
		integer_value& operator=(integer_value const&) = default;
		integer_value& operator=(integer_value&&) = default;


		template<class U, U RMin, U RMax>integer_value(integer_value<U, RMin, RMax>const& v)noexcept :val(*v)
		{
			static_assert(
				type_traits::castable_v<T, RMin> &&
				type_traits::castable_v<T, RMax> &&
				Min <= static_cast<T>(RMin) &&
				static_cast<T>(RMax) <= Max, "this cast may cause out of range error");
		}
		template<class U, U RMin, U RMax>integer_value& operator=(integer_value<U, RMin, RMax>const& v)noexcept
		{
			static_assert(
				type_traits::castable_v<T, RMin> &&
				type_traits::castable_v<T, RMax> &&
				Min <= static_cast<T>(RMin) &&
				static_cast<T>(RMax) <= Max, "this cast may cause out of range error");
			val = *v;
			return *this;
		}

		T operator*()const noexcept
		{
			return val;
		}
	};
	template<std::int64_t Min, std::int64_t Max>using signed_integer=integer_value<std::int64_t, Min, Max>;
	template<std::uint64_t Min, std::uint64_t Max>using unsigned_integer=integer_value<std::uint64_t, Min, Max>;

	template<class T, T Min, T Max>auto& operator<<(std::ostream& os, integer_value<T, Min, Max>const& v)
	{
		return os << *v;
	}
	template<class T, T Min, T Max>auto& operator>>(std::istream& is, integer_value<T, Min, Max>& v)
	{
		T val;
		auto& ret = (is >> val);
		v = val;
		return ret;
	}
}