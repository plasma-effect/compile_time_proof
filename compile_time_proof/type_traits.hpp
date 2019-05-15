#pragma once
//This software is released under the MIT License, see LICENSE.txt.

#include<type_traits>
#include<functional>
#include<cctype>

namespace ctp
{
	namespace type_traits
	{
		template<class Func>struct has_unit :std::false_type
		{

		};
		template<class Func>struct has_commutative :std::false_type
		{

		};
		template<class Func>struct has_associative :std::false_type
		{

		};
		template<class Func>struct has_inverse :std::false_type
		{

		};
		template<class Func>bool has_unit_v = has_unit<Func>::value;
		template<class Func>bool has_commutative_v = has_commutative<Func>::value;
		template<class Func>bool has_associative_v = has_associative<Func>::value;
		template<class Func>bool has_inverse_v = has_inverse<Func>::value;

		namespace detail
		{
			template<class T>struct castable;
			template<>struct castable<std::int64_t>
			{
				static constexpr bool check(std::int64_t v)
				{
					return true;
				}
				static constexpr bool check(std::uint64_t v)
				{
					return v <= static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max());
				}
			};
			template<>struct castable<std::uint64_t>
			{
				static constexpr bool check(std::int64_t v)
				{
					return 0 <= v;
				}
				static constexpr bool check(std::uint64_t v)
				{
					return true;
				}
			};
		}
		template<class T, auto v>constexpr bool castable_v = detail::castable<T>::check(v);
	}
}