#pragma once
//This software is released under the MIT License, see LICENSE.txt.

#include<exception>
#include<stdexcept>
#include<sstream>
#include<cctype>
#include<iostream>

namespace ctp
{
	template<class T, T Min, T Max>class integer_value
	{
		static constexpr T min = Min;
		static constexpr T max = Max;
		T val;
		void value_check(T const& v)
		{
			if (!(min <= v && v <= max))
			{
				std::stringstream ss;
				ss << "given value is not in [" << min << ", " << max << "]";
				throw std::invalid_argument(ss.str());
			}
		}
	public:
		integer_value(T const& v) :val(v)
		{
			value_check(v);
		}
		integer_value(integer_value const&) = default;
		integer_value(integer_value&&) = default;
		integer_value& operator=(integer_value const&) = default;
		integer_value& operator=(integer_value&&) = default;
		integer_value& operator=(T const& rhs)
		{
			value_check(rhs);
			val = rhs;
		}

		operator T()const
		{
			return val;
		}
		T const& operator*()const
		{
			return val;
		}
	};
	template<class T, T min, T max>auto& operator<<(std::ostream& os, integer_value<T, min, max>const& v)
	{
		return os << *v;
	}
}