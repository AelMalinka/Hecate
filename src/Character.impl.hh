/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_CHARACTER_IMPL
#	define ENTROPY_HECATE_CHARACTER_IMPL

#	include "Character.hh"

#	include <typeindex>
#	include <type_traits>

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename stats>
			template<typename ...sl>
			Character<stats>::Character(const sl &... s)
				: _luck(ENTROPY_HECATE_DEFAULT_LUCK), _stats(s...)
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
			CostType Character<stats>::Cost() const
			{
				CostType ret = 0;

				detail::for_each(_stats, [&ret](auto &x) { ret += x.Cost(); });
				for(auto &i : _skills) {
					ret += boost::any_cast<Percent &>(i.second).Cost();
				}

				return ret;
			}

			template<typename stats>
			template<typename tag, CostType CostPer>
			Stat<tag, CostPer> &Character<stats>::get(Stat<tag, CostPer> &s)
			{
				using std::get;
				using std::remove_reference;

				s = get<typename remove_reference<decltype(s)>::type>(_stats);

				return s;
			}

			template<typename stats>
			template<typename tag, CostType CostPer>
			const Stat<tag, CostPer> &Character<stats>::get(Stat<tag, CostPer> &s) const
			{
				using std::get;
				using std::remove_reference;

				s = get<typename remove_reference<decltype(s)>::type>(_stats);

				return s;
			}

			template<typename stats>
			template<typename tag, CostType CostPer, typename ...sl>
			Skill<tag, CostPer, sl...> &Character<stats>::set(Skill<tag, CostPer, sl...> &s)
			{
				using boost::any_cast;

				_skills[typeid(s)] = s;

				return any_cast<decltype(s)>(_skills[typeid(s)]);
			}

			template<typename stats>
			template<typename tag, CostType CostPer, typename ...sl>
			Skill<tag, CostPer, sl...> &Character<stats>::get(Skill<tag, CostPer, sl...> &s)
			{
				using boost::any_cast;

				if(_skills.find(typeid(s)) != _skills.end())
					s = any_cast<decltype(s)>(_skills[typeid(s)]);
				else
					_skills[typeid(s)] = s;

				return any_cast<decltype(s)>(_skills[typeid(s)]);
			}

			template<typename stats>
			template<typename tag, CostType CostPer, typename ...sl>
			Skill<tag, CostPer, sl...> Character<stats>::get(Skill<tag, CostPer, sl...> &s) const
			{
				using boost::any_cast;

				if(_skills.find(typeid(s)) != _skills.end())
					s = any_cast<decltype(s)>(*_skills.find(typeid(s)));

				return s;
			}

			template<typename stats>
			template<typename ...Mods>
			Check Character<stats>::_check(Mods ...mods)
			{
				return Check(_luck, {mods...});
			}
		}
	}

#endif
