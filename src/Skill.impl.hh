/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_SKILL_IMPL
#	define ENTROPY_HECATE_SKILL_IMPL

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
			}

			template<typename tag, typename ...skills>
			template<typename ...Skills>
			Skill<tag, skills...>::Skill(const unsigned short v, Skills &...s)
				: _value(v), _base_skills(s...)
			{}

			template<typename tag, typename ...skills> Skill<tag, skills...>::~Skill() = default;

			template<typename tag, typename ...skills>
			unsigned short Skill<tag, skills...>::Value() const
			{
				int x = 0;
				detail::for_each(_base_skills, [&x](auto &v){ x += v.Value(); });
				return _value + (x / std::tuple_size<decltype(_base_skills)>::value);
			}

			template<typename tag, typename ...skills>
			void Skill<tag, skills...>::setValue(const unsigned short v)
			{
				_value = v;
			}
		}
	}

#endif
