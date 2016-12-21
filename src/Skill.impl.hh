/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_SKILL_IMPL
#	define ENTROPY_HECATE_SKILL_IMPL

#	include "Skill.hh"

#	include <tuple>
#	include <utility>
#	include <cstddef>

	namespace Entropy
	{
		namespace Hecate
		{
			namespace detail
			{
				template<std::size_t i = 0, typename F, typename ...T>
				typename std::enable_if<i == sizeof...(T), void>::type for_each(const tuple<T...> &, F)
				{}

				template<std::size_t i = 0, typename F, typename ...T>
				typename std::enable_if<i < sizeof...(T), void>::type for_each(tuple<T...> &t, F f)
				{
					using std::get;

					f(get<i>(t));
					for_each<i + 1, F, T...>(t, f);
				}

				template<std::size_t i = 0, typename F, typename ...T>
				typename std::enable_if<i < sizeof...(T), void>::type for_each(const tuple<T...> &t, F f)
				{
					using std::get;

					f(get<i>(t));
					for_each<i + 1, F, T...>(t, f);
				}

				template<typename S>
				tuple<> get_values(S &)
				{
					return tuple<>();
				}

				template<typename F, typename ...T, typename S>
				tuple<F, T...> get_values(S &s)
				{
					using namespace std;

					return tuple_cat(tuple<F>(get<typename remove_reference<F>::type>(s)), get_values<T...>(s));
				}
			}

			template<typename tag, CostType CostPer, typename ...skills>
			template<typename ...Skills>
			Skill<tag, CostPer, skills...>::Skill(const PercentType v, Skills &...s)
				: Base(v), _base_skills(s...)
			{}

			template<typename tag, CostType CostPer, typename ...skills>
			template<typename sl, typename>
			Skill<tag, CostPer, skills...>::Skill(sl &s)
				: Base(0), _base_skills(detail::get_values<skills &...>(s))
			{}

			template<typename tag, CostType CostPer, typename ...skills> Skill<tag, CostPer, skills...>::~Skill() = default;

			template<typename tag, CostType CostPer, typename ...skills>
			PercentType Skill<tag, CostPer, skills...>::Value() const
			{
				int x = 0;
				detail::for_each(_base_skills, [&x](auto &v){ x += v.Value(); });
				return this->Raw() + (x / std::tuple_size<decltype(_base_skills)>::value);
			}
		}
	}

#endif
