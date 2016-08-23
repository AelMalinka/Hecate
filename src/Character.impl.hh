/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_CHARACTER_IMPL
#	define ENTROPY_HECATE_CHARACTER_IMPL

#	include <typeindex>
#	include <type_traits>

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename stats>
			template<typename ...sl>
			Character<stats>::Character(const sl &... s)
				: _stats(s...)
			{}

			template<typename stats> Character<stats>::~Character() = default;

			template<typename stats>
			stats &Character<stats>::Stats()
			{
				return _stats;
			}

			template<typename stats>
			const stats &Character<stats>::Stats() const
			{
				return _stats;
			}

			template<typename stats>
			template<typename tag>
			Stat<tag> &Character<stats>::get(Stat<tag> &s)
			{
				using std::get;
				using std::remove_reference;

				s = get<typename remove_reference<decltype(s)>::type>(_stats);

				return s;
			}

			template<typename stats>
			template<typename tag>
			const Stat<tag> &Character<stats>::get(Stat<tag> &s) const
			{
				using std::get;
				using std::remove_reference;

				s = get<typename remove_reference<decltype(s)>::type>(_stats);

				return s;
			}

			template<typename stats>
			template<typename tag, typename ...sl>
			Skill<tag, sl...> &Character<stats>::set(Skill<tag, sl...> &s)
			{
				using boost::any_cast;

				_skills[typeid(s)] = s;

				return any_cast<decltype(s)>(_skills[typeid(s)]);
			}

			template<typename stats>
			template<typename tag, typename ...sl>
			Skill<tag, sl...> &Character<stats>::get(Skill<tag, sl...> &s)
			{
				using boost::any_cast;

				if(_skills.find(typeid(s)) != _skills.end())
					s = any_cast<decltype(s)>(_skills[typeid(s)]);

				return s;
			}

			template<typename stats>
			template<typename tag, typename ...sl>
			const Skill<tag, sl...> &Character<stats>::get(Skill<tag, sl...> &s) const
			{
				using boost::any_cast;

				if(_skills.find(typeid(s)) != _skills.end())
					s = any_cast<decltype(s)>(*_skills.find(typeid(s)));

				return s;
			}
		}
	}

#endif
