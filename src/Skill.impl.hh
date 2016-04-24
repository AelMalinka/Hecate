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
			using std::tuple;

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

			template<typename tag, typename bases, typename type>
			template<typename ...T>
			Skill<tag, bases, type>::Skill(const type &v, T &... b)
				: _base_skills(b...), _value(v)
			{}

			template<typename tag, typename bases, typename type> Skill<tag, bases, type>::~Skill() = default;

			template<typename tag, typename bases, typename type>
			type Skill<tag, bases, type>::Value() const
			{
				int x = 0;
				detail::for_each(_base_skills, [&x](auto &v){ x += v.Value(); });
				return _value + (x / std::tuple_size<decltype(_base_skills)>::value);
			}

			template<typename tag, typename bases, typename type>
			void Skill<tag, bases, type>::setValue(const type &v)
			{
				_value = v;
			}
		}
	}

#endif
